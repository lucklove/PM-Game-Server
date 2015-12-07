#pragma once
#include <atomic>
#include "storage/MonsterDB.hh"
#include "utils/Optional.hh"

struct Battle
{
    int id;                     /**< 战场id */
    int round;                  /**< 回合计数 */
    Monster player_pm;
    Monster server_pm;

    static int genUniqueBattleID()
    {
        static std::atomic<int> id_counter_{ 0 };
        return atomic_fetch_add(&id_counter_, 1);
    }

    static Optional<Battle> launch(int player_id, int server_id)
    {
        auto player_pm_opt = MonsterDB::get(player_id);
        auto server_pm_opt = MonsterDB::get(server_id);
        if(player_pm_opt && server_pm_opt)
            return Battle{genUniqueBattleID(), 1, *player_pm_opt, *server_pm_opt};
        return {}; 
    }
};
