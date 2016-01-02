math.randomseed(os.time())

--计算monster的满血hp
function full_hp(m)
    return math.ceil(m:level() * m:bs_hp() / 50 + m:ev_hp() / 4 + 10 + m:level())
end

--初始化PM的HP
function init_monster_attr(m)
    m:set_cur_hp(full_hp(m))
    m:set_mod_dmg_ability(1)
    m:set_mod_acc_ability(1)
    m:set_mod_type_value(0.5)
    m:set_round_ability(0)
    m:set_crit_multi(1)
    m:set_mod_dodge(1)
end


--判断先攻后攻
function is_first(ma, mb, sa, sb)
    if((sa:last_order() == 0 and sb:last_order() == 0) or (sa:last_order() ~= 0 and sb:last_order() ~= 0)) then
        return ma:cur_spd() > mb:cur_spd()
    else
        if(sa:last_order() == 0) then
            return false
        end
        return true
    end
end

--初始化PM的各项属性
function update_monster_attr(m)
    m:set_cur_atk(math.ceil(m:level() * m:bs_atk() / 50 + m:ev_atk() / 4 + 5))
    m:set_cur_def(math.ceil(m:level() * m:bs_def() / 50 + m:ev_def() / 4 + 5))
    m:set_cur_satk(math.ceil(m:level() * m:bs_satk() / 50 + m:ev_satk() / 4 + 5))
    m:set_cur_sdef(math.ceil(m:level() * m:bs_sdef() / 50 + m:ev_sdef() / 4 + 5))
    m:set_cur_spd(math.ceil(m:level() * m:bs_spd() / 50 + m:ev_spd() / 4 + 5))
end

--计算暴击倍数
function calculate_crit_multi(m)
    local crit_rate = 0     --暴击率
    if(m:crit_lv() >= 5) then
        crit_rate = 10000
    elseif(m:crit_lv() < 0) then
        crit_rate = 0
    else
        local rate = { 625, 1250, 2500, 3333, 5000 }
        crit_rate = rate[m:crit_lv() + 1]
    end
    if(math.random(0, 10000) <= crit_rate) then
        return 1 * m:crit_multi()
    end
    return 0
end

--计算是否命中
function is_hit(m_a, m_b, s)
    if(s:acc() == 1000) then        --当acc为1000时必中
        return true
    end

    local mod_acc_lv = 0
    if(m_a:acc_lv() < 0) then
        mod_acc_lv = 2.0 / (2 - m_a:acc_lv())        
    else
        mod_acc_lv = (m_a:acc_lv() + 2) / 2.0
    end

    local acc_final = s:acc() * mod_acc_lv * m_a:mod_acc_ability() * m_b:mod_dodge()
    return math.random(0, 100) <= acc_final
end

--技能导致能力变化
function change_attr_by_skill(m, s)
    local limit = function(num)
        if(num > 6) then
            return 6
        end
        if(num < -6) then
            return -6
        end
        return num;
    end
    local attrs = {
        [1] = function() m:set_atk_lv(limit(m:atk_lv() + s:lvl_attr())) end,
        [2] = function() m:set_def_lv(limit(m:def_lv() + s:lvl_attr())) end,
        [3] = function() m:set_satk_lv(limit(m:satk_lv() + s:lvl_attr())) end,
        [4] = function() m:set_sdef_lv(limit(m:dsef_lv() + s:lvl_attr())) end,
        [5] = function() m:set_spd_lv(limit(m:spd_lv() + s:lvl_attr())) end,
        [6] = function() m:set_acc_lv(limit(m:acc_lv() + s:lvl_attr())) end,
        [7] = function() m:set_crit_lv(limit(m:crit_lv() + s:lvl_attr())) end,
    }
   
    if(s:attr() < 1 or s:attr() > 7) then
        throw("lua", "no such attr")
    end
 
    attrs[s:attr()]()
    update_monster_attr(m)
end

--计算一个PM通过特定技能攻击另一个PM时造成的伤害
function monster_attack(res_a, res_b, monster_a, monster_b, skill)
    if(not is_hit(monster_a, monster_b, skill)) then
        res_a:setb("hit", false)
        return
    end 

    --计算伤害
    local multi = calculate_crit_multi(monster_a)
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
    ) * math.random(217, 255) / 255.0 * (1 + multi) * (1 + is_same_type * monster_a:mod_type_value())
    * mod_type_aioi * monster_a:mod_dmg_ability() + skill:fixdmg();

    --执行实际的伤害
    res_a:setn("hurt", hurt)
    monster_b:set_cur_hp(math.ceil(monster_b:cur_hp() - hurt))
    res_b:setn("hp", monster_b:cur_hp())
    
    update_monster_attr(monster_a)
    update_monster_attr(monster_b)

    --技能导致能力变化
    if(math.random(0, 100) < skill:rate_attr()) then
        if(skill:role_attr() == 0) then
            local attr = res_a:get("attr")
            attr:seti("type", skill:attr());
            attr:seti("value", skill:lvl_attr());
            change_attr_by_skill(monster_a, skill)
        else
            local attr = res_b:get("attr")
            attr:seti("type", skill:attr())
            attr:seti("value", skill:lvl_attr())
            change_attr_by_skill(monster_b, skill)
        end
    end

    --技能导致异常
    local pm
    if(skill:role_debuff() == 0) then
        pm = monster_a
    else
        pm = monster_b
    end
    
    if(math.random(0, 100) < skill:rate_debuff() and pm:debuff_cur() == 0) then
        pm:set_debuff_cur(skill:debuff())    
        pm:set_debuff_round(skill:round() + pm:round_ability())    
    end
end

--debuff伤害逻辑
function tick_debuff(r, m)
    local cont = true
    local remove = false
    if(m:debuff_cur() ~= 0) then
        local d = get_debuff(m:debuff_cur())
        cont = d(r, m)
        m:set_debuff_round(m:debuff_round() - 1)
        if(m:debuff_round() == 0) then
            m:set_debuff_cur(0)
            r:setb("remove", true);
            return cond;
        end
        r:setb("remove", false)
    end
    return cont
end
