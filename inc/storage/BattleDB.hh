#pragma once
#include "battle/Battle.hh"
#include "Storage.hh"
#include <unordered_map>

struct BattleMemoryStorage
{
private:
    static std::unordered_map<int, Battle>& static_storage()
    {
        static std::unordered_map<int, Battle> local_db;
        return local_db;
    }

public:
    static Optional<Battle> get(int id)
    {
        auto& db = static_storage();
        auto ptr = db.find(id);
        if(ptr == db.end())
            return {};
        return ptr->second;
    }

    static void set(int id, const Battle& bat)
    {
        auto& db = static_storage();
        db.erase(id);
        db.insert({id, bat});
    }

    static void del(int id)
    {
        auto& db = static_storage();
        db.erase(id);
    }
};

using BattleDB = Storage<BattleMemoryStorage>;
