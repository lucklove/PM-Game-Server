#pragma once
#include "Storage.hh"
#include "DBConnectionPool.hh"
#include "utils/ScopeGuard.hh"
#include <unordered_map>
#include <mutex>

template <typename T>
struct MemoryStorage
{
private:
    static std::mutex& storage_lock()
    {
        static std::mutex lock;
        return lock;
    }

    static std::unordered_map<int, T>& static_storage()
    {
        static std::unordered_map<int, T> local_db;
        return local_db;
    }

public:
    static Optional<T> get(int id)
    {
        auto& db = static_storage();
        std::lock_guard<std::mutex> lck(storage_lock());
        auto ptr = db.find(id);
        if(ptr == db.end())
            return {};
        return ptr->second;
    }

    static void set(int id, const T& item)
    {
        auto& db = static_storage();
        std::lock_guard<std::mutex> lck(storage_lock());
        db.erase(id);
        db.insert({id, item});
    }

    static void del(int id)
    {
        auto& db = static_storage();
        std::lock_guard<std::mutex> lck(storage_lock());
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
            std::string s = get_redis_connection()->session.get(filed + ":" + std::to_string(id));
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
        get_redis_connection()->session.set(filed + ":" + std::to_string(id), ss.str());
    }

    static void del(const std::string& filed, int id)
    {
        get_redis_connection()->session.del(filed + ":" + std::to_string(id));
    }
};
