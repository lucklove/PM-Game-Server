#pragma once
#include "Storage.hh"
#include "utils/ScopeGuard.hh"
#include <redox.hpp>
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
        std::lock_guard<std::mutex> lck(storage_lock());
        auto& db = static_storage();
        auto ptr = db.find(id);
        if(ptr == db.end())
            return {};
        return ptr->second;
    }

    static void set(int id, const T& item)
    {
        std::lock_guard<std::mutex> lck(storage_lock());
        auto& db = static_storage();
        db.erase(id);
        db.insert({id, item});
    }

    static void del(int id)
    {
        std::lock_guard<std::mutex> lck(storage_lock());
        auto& db = static_storage();
        db.erase(id);
    }
};

template <typename T>
struct CacheStorage
{
    static Optional<T> get(const std::string& filed, int id)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return {};
        ScopeGuard on_exit([&]{ rdx.disconnect(); });
        
        try
        {
            Optional<T> item_opt;
            std::string s = rdx.get(filed + ":" + std::to_string(id));
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
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return;
        ScopeGuard on_exit([&]{ rdx.disconnect(); });
        
        std::stringstream ss;
        item.to_stream(ss);
        rdx.set(filed + ":" + std::to_string(id), ss.str());
    }

    static void del(const std::string& filed, int id)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return;
        ScopeGuard on_exit([&]{ rdx.disconnect(); });

        rdx.del(filed + ":" + std::to_string(id));
    }
};
