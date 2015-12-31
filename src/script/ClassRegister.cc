#include "script/ClassRegister.hh"
#include "battle/Monster.hh"
#include "battle/Skill.hh"
#include "battle/Battle.hh"
#include "result/Result.hh"
#include "crow/json.h"

namespace
{
    void register_monster(nua::Context& ctx)
    {
        ctx.setClass<Monster>(
            "name", &Monster::name,
            "level", &Monster::level,
            "bs_hp", &Monster::bs_hp,
            "bs_atk", &Monster::bs_atk,
            "bs_def", &Monster::bs_def,
            "bs_satk", &Monster::bs_satk,
            "bs_sdef", &Monster::bs_sdef,
            "bs_spd", &Monster::bs_spd,
            "ev_hp", &Monster::ev_hp,
            "ev_atk", &Monster::ev_atk,
            "ev_def", &Monster::ev_def,
            "ev_satk", &Monster::ev_satk,
            "ev_sdef", &Monster::ev_sdef,
            "ev_spd", &Monster::ev_spd,
            "cur_hp", &Monster::cur_hp,
            "cur_atk", &Monster::cur_atk,
            "cur_def", &Monster::cur_def,
            "cur_satk", &Monster::cur_satk,
            "cur_sdef", &Monster::cur_sdef,
            "cur_spd", &Monster::cur_spd,
            "atk_lv", &Monster::atk_lv,
            "crit_lv", &Monster::crit_lv,
            "acc_lv", &Monster::acc_lv,
            "type1", &Monster::type1,
            "type2", &Monster::type2,
            "debuff_cur", &Monster::debuff_cur,
            "debuff_round", &Monster::debuff_round,
            "ability", &Monster::ability,
            "peekSkill", &Monster::peekSkill
        );
    }

    void register_skill(nua::Context& ctx)
    {
        ctx.setClass<Skill>(
            "name", &Skill::name,
            "skill_class", &Skill::skill_class,
            "type", &Skill::type,
            "acc", &Skill::acc,
            "power", &Skill::power,
            "attr", &Skill::attr,
            "lvl_attr", &Skill::lvl_attr,
            "rate_attr", &Skill::rate_attr,
            "role_attr", &Skill::role_attr,
            "debuff", &Skill::debuff,
            "role_debuff", &Skill::role_debuff,
            "rate_debuff", &Skill::rate_debuff,
            "last_order", &Skill::last_order,
            "round", &Skill::round,
            "fixdmg", &Skill::fixdmg
        );   
    }

    void register_result(nua::Context& ctx)
    {
        ctx.setClass<Result>(
            "get", &Result::get,
            "setb", &Result::set<bool>,
            "seti", &Result::set<int>,
            "setn", &Result::set<double>,
            "sets", &Result::set<std::string>
        );
    }

    void register_battle(nua::Context& ctx)
    {
        ctx.setClass<Battle>(
            "id", &Battle::id,
            "role_pm", &Battle::role_pm,
            "enemy_pm", &Battle::enemy_pm
        );
    }
}

void ClassRegister::register_all(nua::Context& ctx)
{
    ctx.setClass<crow::json::wvalue>();
    register_monster(ctx);   
    register_skill(ctx);
    register_result(ctx); 
    register_battle(ctx); 
}
