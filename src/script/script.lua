mod_skill_power = 1.0

mod_type_value = 0.5

mod_weather_eff = 1.0

mod_dmg_ability = 1.0

fix_dmg = 0.0

math.randomseed(os.time())

function initMonsterHP(m)
    m:set_cur_hp(math.ceil(m:level() * m:bs_hp() / 50 + m:ev_hp() / 4 + 10 + m:level()))
end

function updateMonsterAttr(m)
    m:set_cur_atk(math.ceil(m:level() * m:bs_atk() / 50 + m:ev_atk() / 4 + 5))
    m:set_cur_def(math.ceil(m:level() * m:bs_def() / 50 + m:ev_def() / 4 + 5))
    m:set_cur_satk(math.ceil(m:level() * m:bs_satk() / 50 + m:ev_satk() / 4 + 5))
    m:set_cur_sdef(math.ceil(m:level() * m:bs_sdef() / 50 + m:ev_sdef() / 4 + 5))
    m:set_cur_spd(math.ceil(m:level() * m:bs_spd() / 50 + m:ev_spd() / 4 + 5))
end

function monsterAttack(monster_a, monster_b, skill, multi)
    local is_physical_skill = 0
    if(skill:skill_class() == 1) then
        is_physical_skill = 1
    end
    
    local is_same_type = 0
    if(monster_a:type1() == skill:type() or monster_a:type2() == skill:type()) then
        is_same_type = 1
    end

    local mod_type_aioi = get_aioi(monster_a:type1(), monster_b:type1())
        * get_aioi(monster_a:type1(), monster_b:type2())
        * get_aioi(monster_a:type2(), monster_b:type1())
        * get_aioi(monster_a:type2(), monster_b:type2())

    local hurt =
    (
        (monster_a:level() * 0.4 + 2) * skill:power()
        * (monster_a:cur_atk() * is_physical_skill + monster_a:cur_satk() * (1 - is_physical_skill))
        / (monster_b:cur_def() * is_physical_skill + monster_b:cur_sdef() * (1 - is_physical_skill))
        / 50 + 2
    ) * math.random(217, 255) / 255.0 * (1 + multi) * (1 + is_same_type * mod_type_value) * mod_type_aioi
    * mod_weather_eff * mod_dmg_ability + fix_dmg;
    return hurt
end
