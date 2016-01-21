#pragma once
#include <atomic>
#include "storage/MonsterDB.hh"

struct Battle
{
    int id;                     /**< 战场id */
    Monster role_pm;
    Monster enemy_pm;

    static int genUniqueBattleID()
    {
        static std::atomic<int> id_counter_{ 0 };
        return atomic_fetch_add(&id_counter_, 1);
    }

    static Battle launch(Monster role, Monster enemy)
    {
        return Battle{genUniqueBattleID(), role, enemy};
    }
};
