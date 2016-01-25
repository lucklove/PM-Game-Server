#pragma once
#include "Storage.hh"
#include "DBAccess.hh"
#include "utils/ScopeGuard.hh"
#include "dispatcher/Dispatcher.hh"
#include <unordered_map>
#include <atomic>

template <typename T>
struct MemoryStorage
{
private:
    static std::atomic_flag& storage_lock()
    {
        static std::atomic_flag lock = ATOMIC_FLAG_INIT;
        return lock;
    }

    struct LockGuard
    {
    public:
        LockGuard(std::atomic_flag& lock) : lock_{lock}
        {
            while(lock_.test_and_set())
                Dispatcher::getInstance().yield();
        }

        ~LockGuard()
        {
            lock_.clear();
        }

    private:
        std::atomic_flag& lock_;
    };

    static std::unordered_map<int, T>& static_storage()
    {
        static std::unordered_map<int, T> local_db;
        return local_db;
    }

public:
    static Optional<T> get(int id)
    {
        auto& db = static_storage();
        LockGuard lck(storage_lock());
        auto ptr = db.find(id);
        if(ptr == db.end())
            return {};
        return ptr->second;
    }

    static void set(int id, const T& item)
    {
        auto& db = static_storage();
        LockGuard lck(storage_lock());
        db.erase(id);
        db.insert({id, item});
    }

    static void del(int id)
    {
        auto& db = static_storage();
        LockGuard lck(storage_lock());
        db.erase(id);
    }
};

template <typename T>
struct CacheStorage
{
    static Optional<T> get(const std::string& filed, int id)
    {
        try
        {
            Optional<T> item_opt;
            std::string s;

            DBAccess::redis_query([&filed, &s, id](redox::Redox& session)
            {
                s = session.get(filed + ":" + std::to_string(id));
            });

            T item;
            std::stringstream ss{s};
            item.from_stream(ss);
            return item;
        }
        catch(std::runtime_error&)
        {
            return {};
        }
    }

    static void set(const std::string& filed, int id, const T& item)
    {
        std::stringstream ss;
        item.to_stream(ss);
        DBAccess::redis_query([&ss, &filed, id](redox::Redox& session)
        {
            session.set(filed + ":" + std::to_string(id), ss.str());
        });
    }

    static void del(const std::string& filed, int id)
    {
        DBAccess::redis_query([&filed, id](redox::Redox& session)
        {
            session.del(filed + ":" + std::to_string(id));
        });
    }
};
