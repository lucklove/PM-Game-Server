#pragma once
#include <tuple>
#include "utils/Random.hh"
#include "Skill.hh"
#include "Monster.hh"

struct Attack
{
    /** 判断是否命中，暂未处理道具，特性和敌方闪避 */
    static bool is_hit(const Monster& a, const Skill& s)
    {
        if(s.acc == 1000) return true;          /**< 必中 */

        float mod_acc_lv = a.acc_lv < 0 ? (2.0 / (2 - a.acc_lv)) : (a.acc_lv + 2) / 2.0;
        float acc_final = s.acc * mod_acc_lv;
    
        return Random::get(0, 100) <= acc_final;
    }

    /** 暴击倍数 */
    static int crit_multi(const Monster& a)
    {
        int crit_rate = 0;

        if(a.crit_lv >= 5)
        {
            crit_rate = 10000;
        }
        else if(a.crit_lv < 0)
        {
            crit_rate = 0;
        }
        else
        {
            constexpr int rate[] = { 625, 1250, 2500, 3333, 5000 };
            crit_rate = rate[a.crit_lv];
        }
        if(Random::get(0, 10000) <= crit_rate)
            return 1;
        return 0;    
    }

    /** 判断先后 */
    static bool is_first(const Monster& a, const Monster& b)
    {
        return a.cur_spd > b.cur_spd;
    }

    /** 计算攻击，对对方的伤害 */
    /** 未处理技能威力修正 */
    static float attack(const Monster& a, const Monster& b, const Skill& s, int multi)
    {
        int is_physical_skill = s.skill_class == 1;
        return 
        (
            (a.level * 0.4 + 2) * s.power 
                * (a.cur_atk * is_physical_skill + a.cur_satk * (1 - is_physical_skill))
                / (b.cur_def * is_physical_skill + b.cur_sdef * (1 - is_physical_skill))
                / 50 + 2
        ) * Random::get(217, 255) / 255.0 * (1 + multi);
    }
};
