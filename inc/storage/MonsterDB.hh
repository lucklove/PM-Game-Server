#pragma once
#include "Storage.hh"
#include "common/Monster.hh"
#include <unordered_map>

struct PrimaryMonsterStorage
{
private:
    static std::unordered_map<int, Monster>& static_storage()
    {
        static std::unordered_map<int, Monster> local_db;
        return local_db;
    }

public:
    static Optional<Monster> get(int id)
    {
        auto& db = static_storage();
        auto ptr = db.find(id);
        if(ptr == db.end())
            return {};
        return ptr->second;
    }

    static void set(int id, const Monster& m)
    {
        auto& db = static_storage();
        db.erase(id);
        db.insert({id, m});
    }

    static void del(int id)
    {
        auto& db = static_storage();
        db.erase(id);
    } 
};

using MonsterDB = Storage<PrimaryMonsterStorage>;
