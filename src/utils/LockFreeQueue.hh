#pragma once
#include <atomic>
#include "Optional.hh"
#include "ScopeGuard.hh"

template <typename DataT>
class LockFreeQueue
{
private:
    struct Node;

    struct TaggedStateReference
    {
        Node* node;
        size_t version;                 /**< avoid ABA */
        
        bool operator==(const TaggedStateReference& r)
        {
            return node == r.node && version == r.version;
        }

        bool operator!=(const TaggedStateReference& r)
        {
            return !operator==(r);
        }
    };

    struct Node
    {
        DataT* data;
        std::atomic<TaggedStateReference> next;
    };

    std::atomic<TaggedStateReference> head_;
    std::atomic<TaggedStateReference> tail_;
    std::atomic<TaggedStateReference> trash_head_;
    std::atomic<TaggedStateReference> trash_tail_;

    void push_tail(std::atomic<TaggedStateReference>& tail, Node* node)
    {
        node->next.store({nullptr, node->next.load(std::memory_order_relaxed).version}, std::memory_order_relaxed);
        while(true)
        {
            TaggedStateReference old_tail = tail.load(std::memory_order_acquire);
            TaggedStateReference tail_next = old_tail.node->next.load(std::memory_order_acquire);
            if(old_tail != tail.load(std::memory_order_acquire))    /**< 保证在取next时tail没有改变 */
                continue;
 
            if(tail_next.node)
            {
                TaggedStateReference new_tail{tail_next.node, old_tail.version + 1};
                tail.compare_exchange_strong(old_tail, new_tail);
                continue;
            }
            else
            {
                TaggedStateReference new_tail_next{node, tail_next.version + 1};
                if(old_tail.node->next.compare_exchange_weak(tail_next, new_tail_next))
                {
                    TaggedStateReference new_tail{node, old_tail.version + 1};
                    tail.compare_exchange_strong(old_tail, new_tail);
                    return;
                }
            }
        }
    }

    Node* pop_head(std::atomic<TaggedStateReference>& head, std::atomic<TaggedStateReference>& tail)
    {
        while(true)
        {
            TaggedStateReference old_head = head.load(std::memory_order_acquire);
            TaggedStateReference old_tail = tail.load(std::memory_order_acquire);
            TaggedStateReference head_next = old_head.node->next.load(std::memory_order_acquire);
            if(old_head != head.load(std::memory_order_acquire))    /**< 保证取head_next时head没有改变 */
                continue;

            if(head_next.node == nullptr)
                return nullptr;                 /**< 空 */

            if(old_head.node == old_tail.node)
            {
                TaggedStateReference new_tail{head_next.node, old_tail.version + 1};
                tail.compare_exchange_strong(old_tail, new_tail);
                continue;
            }

            DataT* data = head_next.node->data;
            TaggedStateReference new_head{head_next.node, old_head.version + 1};
            if(head.compare_exchange_weak(old_head, new_head))
            {
                old_head.node->data = data;
//                old_head.node->next = {nullptr, old_head.node->next.load().version};
                return old_head.node;
            }
        }
    }
  
  
    void throw_trash(Node* node)
    {
        push_tail(trash_tail_, node);
    }

    Node* pick_trash()
    {
        return pop_head(trash_head_, trash_tail_);
    }

    void release(std::atomic<TaggedStateReference>& head)
    {
        TaggedStateReference tag_ref = head.load(std::memory_order_relaxed);
        Node* node = tag_ref.node;
        tag_ref = node->next.load(std::memory_order_relaxed);
        delete node;

        while(tag_ref.node)
        {
            node = tag_ref.node;
            tag_ref = node->next.load(std::memory_order_relaxed);
            delete node->data;
            delete node;
        }
    }

    template <typename T>
    void do_push(T&& data)
    {
        Node* node = pick_trash();
        if(node)
        {
            *node->data = std::forward<T>(data);
        }
        else
        {
            node = new Node{new DataT{std::forward<T>(data)}};
        }
        push_tail(tail_, node);
    }

public:
    LockFreeQueue()
    {
        Node* dummy = new Node{nullptr};
        head_.store({dummy, 0}, std::memory_order_release);
        tail_.store({dummy, 0}, std::memory_order_release);

        dummy = new Node{nullptr};
        trash_head_.store({dummy, 0}, std::memory_order_release);
        trash_tail_.store({dummy, 0}, std::memory_order_release);
    }

    ~LockFreeQueue() noexcept(noexcept(std::declval<DataT>().~DataT()))
    {
        release(head_);
        release(trash_head_);
    }

    void push(const DataT& data)
    {
        do_push(data);
    }

    void push(DataT&& data)
    {
        do_push(std::move(data));
    }

    Optional<DataT> pop()
    {
        Node* node = pop_head(head_, tail_);
        if(node)
        {
            ScopeGuard trash_guard([node, this]
            {
                throw_trash(node);
            });
        
            return Optional<DataT>{std::move(*node->data)};
        }
        else
        {
            return {};
        }
    } 

    bool empty()
    {
        while(true)
        {
            TaggedStateReference old_head = head_.load(std::memory_order_acquire);
            TaggedStateReference head_next = old_head.node->next.load(std::memory_order_acquire);
            if(old_head != head_.load(std::memory_order_acquire))    /**< 保证取head_next时head没有改变 */
                continue;

            return head_next.node == nullptr;
        }
    } 
};
