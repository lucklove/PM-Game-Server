#pragma once
#include "battle/Battle.hh"
#include "Storage.hh"
#include "storage_factory.hh"
#include <unordered_map>

struct BattleMemoryStorage
{
public:
    static Optional<Battle> get(int id)
    {
        return MemoryStorage<Battle>::get(id);
    }

    static void set(int id, const Battle& bat)
    {
        MemoryStorage<Battle>::set(id, bat);
    }

    static void del(int id)
    {
        MemoryStorage<Battle>::del(id);
    }
};

using BattleDB = Storage<BattleMemoryStorage>;
