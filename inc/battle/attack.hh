#pragma once
#include <tuple>
#include "utils/Random.hh"
#include "utils/combination.hh"
#include "Skill.hh"
#include "Monster.hh"
#include "Round.hh"
#include "storage/DebuffDB.hh"
#include "storage/AioiDB.hh"
#include "crow/json.h"
#include "script/Lua.hh"

struct AttackOrder
{
    /** 判断先后 */
    static bool is_first(const Monster& a, const Monster& b, const Skill& sa, const Skill& sb)
    {
        if(sa.last_order ^ sb.last_order)
        {
            if(sb.last_order)
                return true;
            return false;
        }
        else
        {
            return a.cur_spd > b.cur_spd;
        }
    }
};

struct Tick
{
    static void tick_debuff(crow::json::wvalue& res, Round& r, Monster& m)
    {
        if(m.debuff_cur != 0)
        {
            DebuffDB::get(m.debuff_cur)->apply(res, r, m);

            /** 移除判定 */
            if(--m.debuff_round == 0)
            {
                m.debuff_cur = 0;
                res["remove"] = true;
            }           
            res["remove"] = false;
        }
    }
};

struct Attack
{
private:
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

    /** 计算攻击，对对方的伤害 */
    /** 未处理技能威力修正 */
/*
    static float attack(const Monster& a, const Monster& b, const Skill& s, int multi)
    {
        int is_physical_skill = s.skill_class == 1;
        int is_same_type = a.type1 == s.type || a.type2 == s.type;
        float mod_type_aioi = 1;
        auto& lua_ctx = Lua::context();
        double mod_type_value = lua_ctx["mod_type_value"];
        double mod_weather_eff = lua_ctx["mod_weather_eff"];
        double mod_dmg_ability = lua_ctx["mod_dmg_ability"];
        double fix_dmg = lua_ctx["fix_dmg"];
        return 
        (
            (a.level * 0.4 + 2) * s.power 
                * (a.cur_atk * is_physical_skill + a.cur_satk * (1 - is_physical_skill))
                / (b.cur_def * is_physical_skill + b.cur_sdef * (1 - is_physical_skill))
                / 50 + 2
        ) * Random::get(217, 255) / 255.0 * (1 + multi) * (1 + is_same_type * mod_type_value) * mod_type_aioi
        * mod_weather_eff * mod_dmg_ability + fix_dmg;
    }
*/
    /** 改变PM属性 */
    static void change_attr(Monster& m, const Skill& s)
    {
        auto limit_attr = [](int& attr)
        {
            if(attr > 6) attr = 6;
            if(attr < -6) attr = -6;
        };

        switch(s.attr)
        {
            case 1: m.atk_lv += s.lvl_attr; limit_attr(m.atk_lv); break;
            case 2: m.def_lv += s.lvl_attr; limit_attr(m.def_lv); break;
            case 3: m.satk_lv += s.lvl_attr; limit_attr(m.satk_lv); break;
            case 4: m.def_lv += s.lvl_attr; limit_attr(m.sdef_lv); break;
            case 5: m.spd_lv += s.lvl_attr; limit_attr(m.spd_lv); break;
            case 6: m.acc_lv += s.lvl_attr; limit_attr(m.acc_lv); break;
            case 7: m.crit_lv += s.lvl_attr; limit_attr(m.crit_lv); break;
        }

        m.updateAttr();
    }

public:
    static void do_attack(crow::json::wvalue& res_a, crow::json::wvalue& res_b, Monster& m_a, Monster& m_b, const Skill& s_a)
    {
        if(!is_hit(m_a, s_a))
        {
            res_a["hurt"] = 0;
            return;
        }
        int crit = Attack::crit_multi(m_a);
        res_a["crit"] = crit;

        auto& lua_ctx = Lua::context();
        double dmg = lua_ctx["monsterAttack"](m_a, m_b, s_a, crit).get<double>();

        res_a["hurt"] = dmg;
        m_b.cur_hp -= dmg;
        res_b["hp"] = m_b.cur_hp;

        m_a.updateAttr();
        m_b.updateAttr();

        /** 技能导致能力变化 */
        if(Random::get(0, 100) < s_a.rate_attr)
        {
            if(s_a.role_attr == 0)
            {
                res_a["attr"]["type"] = s_a.attr;
                res_a["attr"]["value"] = s_a.lvl_attr;
                change_attr(m_a, s_a);
            }
            else
            {
                res_b["attr"]["type"] = s_a.attr;
                res_b["attr"]["value"] = s_a.lvl_attr;
                change_attr(m_b, s_a);
            }
        }

        /** 技能导致异常 */
        Monster *pm = nullptr;
        if(s_a.role_debuff == 0)
        {
            pm = &m_a;
        }
        else
        {
            pm = &m_b;
        }

        if(Random::get(0, 100) < s_a.rate_debuff && pm->debuff_cur == 0)
        {
            pm->debuff_cur = s_a.debuff;
            pm->debuff_round = s_a.round;
 //           DebuffDB::get(pm->debuff_cur)->on(res, r, *pm);
        }
    };
};
