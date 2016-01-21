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
            TaggedStateReference old_top = top.load(); 
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
            TaggedStateReference old_top = top.load();

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

    void release(Node* node)
    {
        while(node)
        {
            Node* prev = node;
            node = node->next;
            delete prev;
        }
    }

public:
    LockFreeStack() 
    {
        top_ = {nullptr, 0};
        trash_ = {nullptr, 0};
    }

    LockFreeStack(const LockFreeStack&) = delete;

    ~LockFreeStack() noexcept(noexcept(std::declval<DataT>().~DataT()))
    {
        TaggedStateReference tagged_top_ref = top_;
        TaggedStateReference tagged_trash_ref = trash_;
        release(tagged_top_ref.node);
        release(tagged_trash_ref.node);
    }

    void push(const DataT& data)
    {
        Node* node = pick_trash();
        if(node)
        {
            node->data = data;
        }
        else
        {
            node = new Node{data, nullptr};
        }
        push_top(top_, node);
    }

    void push(DataT&& data)
    {
        Node* node = pick_trash();
        if(node)
        {
            node->data = std::move(data);
        }
        else
        {
            node = new Node{std::move(data), nullptr};
        }
        push_top(top_, node);
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
};
