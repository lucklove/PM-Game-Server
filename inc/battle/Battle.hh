#pragma once
#include <atomic>
#include "storage/MonsterDB.hh"
#include "utils/Optional.hh"

struct Battle
{
    int id;                     /**< 战场id */
    int round;                  /**< 回合计数 */
    Monster role_pm;
    Monster enemy_pm;

    static int genUniqueBattleID()
    {
        static std::atomic<int> id_counter_{ 0 };
        return atomic_fetch_add(&id_counter_, 1);
    }

    static Optional<Battle> launch(int role_id, int enemy_id)
    {
        auto role_pm_opt = MonsterDB::get(role_id);
        auto enemy_pm_opt = MonsterDB::get(enemy_id);
        if(role_pm_opt && enemy_pm_opt)
        {
            role_pm_opt->init();
            enemy_pm_opt->init();
            return Battle{genUniqueBattleID(), 1, *role_pm_opt, *enemy_pm_opt};
        }
        return {}; 
    }
};
