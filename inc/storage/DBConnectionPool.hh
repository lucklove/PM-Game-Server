#pragma once
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <memory>
#include <atomic>
#include <thread>
#include <cassert>

class DBConnectionPool
{
private:
    struct Node
    {
        Node(const std::string& db_config) : session(soci::mysql, db_config), next{nullptr} {}
        soci::session session;
        Node* next;
    };

    struct TaggedStateReference
    {
        Node* node;
        size_t version;                 /**< avoid ABA */
    };

    class ConnectionDeleter
    {
    private:
        DBConnectionPool* pool_;

    public:
        ConnectionDeleter(DBConnectionPool* p) : pool_{p} {}

        void operator()(Node *node)
        {
            while(true)
            {
                TaggedStateReference old_tagged_top = pool_->top_;
                node->next = old_tagged_top.node;
                TaggedStateReference new_tagged_top{node, old_tagged_top.version + 1};
                if(pool_->top_.compare_exchange_weak(old_tagged_top, new_tagged_top))
                    break; 
            }                       
        } 
    };
   
    std::atomic<TaggedStateReference> top_;  

    DBConnectionPool(size_t size, const std::string& db_config)
    {
        if(!size) return;
       
        Node* top = nullptr;

        for(size_t i = 0; i < size; ++i)
        {
            Node* prev_top = top;
            top = new Node{db_config};
            top->next = prev_top;
        }

        top_ = {top, 0};
    }

    ~DBConnectionPool() noexcept
    {
        try
        {
            TaggedStateReference tagged_top_ref = top_;
            Node* top = tagged_top_ref.node;

            while(top)
            {
                Node* prev_top = top;
                top = top->next;
                delete prev_top;
            }
        }
        catch(...)
        {
            assert(false && "unexpected exception while close database connection");
        }
    }

    std::unique_ptr<Node, ConnectionDeleter> get(bool strong)
    {
        while(true)
        {
            TaggedStateReference old_tagged_top = top_;

            if(old_tagged_top.node == nullptr)
            {
                if(strong)
                {
                    std::this_thread::yield();
                    continue;
                }
                return std::unique_ptr<Node, ConnectionDeleter>(nullptr, ConnectionDeleter{this});
            }

            TaggedStateReference new_tagged_top = {old_tagged_top.node->next, old_tagged_top.version + 1};
            if(top_.compare_exchange_weak(old_tagged_top, new_tagged_top))
                return std::unique_ptr<Node, ConnectionDeleter>(old_tagged_top.node, ConnectionDeleter{this});
        }
    }

public:
    static std::unique_ptr<Node, ConnectionDeleter> get_connection(bool strong = true)
    {
        static DBConnectionPool pool{std::thread::hardware_concurrency(), "db=pocket_monster_db user=root pass=lucklove"};
        return pool.get(strong);    
    }
};
