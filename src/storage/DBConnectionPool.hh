#pragma once
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <redox.hpp>
#include <memory>
#include <atomic>
#include <thread>
#include <cassert>

template <typename Session>
class DBConnectionPool
{
private:
    struct Node
    {
        template <typename... SessionArgs>
        Node(SessionArgs&&... args) : session(std::forward<SessionArgs>(args)...), next{nullptr} {}
        Session session;
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

public:
    template <typename... NodeArgs>
    DBConnectionPool(size_t size, NodeArgs&&... args) //const std::string& db_config)
    {
        if(!size) return;
       
        Node* top = nullptr;

        for(size_t i = 0; i < size; ++i)
        {
            Node* prev_top = top;
            top = new Node{std::forward<NodeArgs>(args)...};
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
};

inline auto get_mysql_connection(bool strong = true)
{
    static DBConnectionPool<soci::session> pool{std::thread::hardware_concurrency(), 
        soci::mysql,
        "db=pocket_monster_db user=root pass=lucklove"};
    return pool.get(strong);    
}

struct RedisSession
{
private:
    redox::Redox rdx_; 

public:
    RedisSession(const std::string& host, short port)
    {
        if(!rdx_.connect(host, port))
            throw std::runtime_error{"connect to redis server failed"};
    }

    ~RedisSession() noexcept(noexcept(rdx_.disconnect()))
    {
        rdx_.disconnect();
    }

    template <typename... Args>
    auto get(Args&&... args) -> decltype(rdx_.get(std::forward<Args>(args)...))
    {
        return rdx_.get(std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto set(Args&&... args) -> decltype(rdx_.set(std::forward<Args>(args)...))
    {
        return rdx_.set(std::forward<Args>(args)...);
    }

    template <typename... Args>
    auto del(Args&&... args) -> decltype(rdx_.del(std::forward<Args>(args)...))
    {
        return rdx_.del(std::forward<Args>(args)...);
    }
};

inline auto get_redis_connection(bool strong = true)
{
    static DBConnectionPool<RedisSession> pool{std::thread::hardware_concurrency(), "localhost", 6379};

    return pool.get(strong);
}
