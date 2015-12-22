#include "script/ClassRegister.hh"
#include "battle/Monster.hh"
#include "battle/Skill.hh"

namespace
{
    void register_monster(nua::Context& ctx)
    {
        ctx.setClass<Monster>(
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
            "type1", &Monster::type1,
            "type2", &Monster::type2
        );
    }

    void register_skill(nua::Context& ctx)
    {
        ctx.setClass<Skill>(
            "skill_class", &Skill::skill_class,
            "type", &Skill::type,
            "power", &Skill::power
        );   
    }
}

void ClassRegister::register_all(nua::Context& ctx)
{
    register_monster(ctx);   
    register_skill(ctx);   
}
