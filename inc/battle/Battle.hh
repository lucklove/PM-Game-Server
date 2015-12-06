#pragma once
#include <atomic>
#include "storage/MonsterDB.hh"
#include "utils/Optional.hh"

struct Battle
{
    int id;                     /**< 战场id */
    int round;                  /**< 回合计数 */
    Monster player_pm_;
    Monster server_pm_;

    static int genUniqueBattleID()
    {
        static std::atomic<int> id_counter_{ 0 };
        return atomic_fetch_add(&id_counter_, 1);
    }

    static Optional<Battle> launch(int player_pm, int server_pm)
    {
        auto player_pm_opt = MonsterDB::get(player_pm);
        auto server_pm_opt = MonsterDB::get(server_pm);
        if(player_pm_opt && server_pm_opt)
            return Battle{genUniqueBattleID(), 1, *player_pm_opt, *server_pm_opt};
        return {}; 
    }
};
