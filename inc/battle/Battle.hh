#pragma once
#include <atomic>
#include "storage/MonsterDB.hh"
#include "utils/Optional.hh"

class Battle
{
private:
    int id_;                    /**< 战场id */
    int round_ = 1;             /**< 回合计数 */
    Monster player_pm_;
    Monster server_pm_;

    static int genUniqueBattleID()
    {
        static std::atomic<int> id_counter_{ 0 };
        return atomic_fetch_add(&id_counter_, 1);
    }

    Battle(const Monster& player_pm, const Monster& server_pm) 
        : id_{genUniqueBattleID()}, player_pm_{player_pm}, server_pm_{server_pm}
    {}

public:
    static Optional<Battle> launch(int player_pm, int server_pm)
    {
        auto player_pm_opt = MonsterDB::get(player_pm);
        auto server_pm_opt = MonsterDB::get(server_pm);
        if(player_pm_opt && server_pm_opt)
            return Battle{*player_pm_opt, *server_pm_opt};
        return {}; 
    }

    int id() const
    {
        return id_;
    }
};
