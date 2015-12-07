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
        {
            Monster& p = *player_pm_opt;
            Monster& s = *server_pm_opt;
            p.cur_hp = p.level * p.bs_hp / 50 + p.ev_hp / 4 + 10 + p.level;
            p.cur_atk = p.level * p.bs_atk / 50 + p.ev_atk / 4 + 5;
            p.cur_def = p.level * p.bs_def / 50 + p.ev_def / 4 + 5;
            p.cur_satk = p.level * p.bs_satk / 50 + p.ev_satk / 4 + 5;
            p.cur_sdef = p.level * p.bs_sdef / 50 + p.ev_sdef / 4 + 5;
            p.cur_spd = p.level * p.bs_spd / 50 + p.ev_spd / 4 + 5;
            s.cur_hp = s.level * s.bs_hp / 50 + s.ev_hp / 4 + 10 + s.level;
            s.cur_atk = s.level * s.bs_atk / 50 + s.ev_atk / 4 + 5;
            s.cur_def = s.level * s.bs_def / 50 + s.ev_def / 4 + 5;
            s.cur_satk = s.level * s.bs_satk / 50 + s.ev_satk / 4 + 5;
            s.cur_sdef = s.level * s.bs_sdef / 50 + s.ev_sdef / 4 + 5;
            s.cur_spd = s.level * s.bs_spd / 50 + s.ev_spd / 4 + 5;
            return Battle{genUniqueBattleID(), 1, p, s};
        }
        return {}; 
    }
};
