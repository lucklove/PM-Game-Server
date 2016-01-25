#pragma once
#include <atomic>
#include "Optional.hh"
#include "ScopeGuard.hh"

template <typename DataT>
class LockFreeStack
{
private:
    struct Node
    {
        DataT data;
        Node* next;
    };

    struct TaggedStateReference
    {
        Node* node;
        size_t version;                 /**< avoid ABA */
    };

    std::atomic<TaggedStateReference> top_;
    std::atomic<TaggedStateReference> trash_;

    void push_top(std::atomic<TaggedStateReference>& top, Node* node)
    {
        while(true)
        {
            TaggedStateReference old_top = top.load(std::memory_order_acquire); 
            node->next = old_top.node;
            TaggedStateReference new_top{node, old_top.version + 1};
            if(top.compare_exchange_weak(old_top, new_top))
                return;
        }
    }

    Node* pop_top(std::atomic<TaggedStateReference>& top)
    {
        while(true)
        {
            TaggedStateReference old_top = top.load(std::memory_order_acquire);

            if(old_top.node == nullptr)
                return nullptr;
            
            TaggedStateReference new_top = {old_top.node->next, old_top.version + 1};
            if(top.compare_exchange_weak(old_top, new_top))
                return old_top.node;
        }
    }

    void throw_trash(Node* node)
    {
        push_top(trash_, node);
    }

    Node* pick_trash()
    {
        return pop_top(trash_);
    }

    void release(std::atomic<TaggedStateReference>& top)
    {
        Node* node = top.load(std::memory_order_acquire).node;
        while(node)
        {
            Node* prev = node;
            node = node->next;
            delete prev;
        }
    }

    template <typename T>
    void do_push(T&& data)
    {
        Node* node = pick_trash();
        if(node)
        {
            node->data = std::forward<T>(data);
        }
        else
        {
            node = new Node{std::forward<T>(data), nullptr};
        }
        push_top(top_, node);
    }


public:
    LockFreeStack() 
    {
        top_ = {nullptr, 0};
        trash_ = {nullptr, 0};
    }

    ~LockFreeStack() noexcept(noexcept(std::declval<DataT>().~DataT()))
    {
        release(top_);
        release(trash_);
    }

    LockFreeStack(const LockFreeStack&) = delete;
    LockFreeStack(LockFreeStack&&) = delete;
    LockFreeStack& operator=(const LockFreeStack&) = delete;
    LockFreeStack& operator=(LockFreeStack&&) = delete;

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
        Node* node = pop_top(top_);
        if(node)
        {
            ScopeGuard trash_guard([node, this]
            {
                throw_trash(node);
            });

           return Optional<DataT>{std::move(node->data)};
        }
        else
        {
            return {};
        }
    }

    bool empty()
    {
        return top_.load(std::memory_order_acquire).node == nullptr;
    }
};
