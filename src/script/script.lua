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
    m:set_debuff_cur(0)
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

--属性等级范围限制
function lv_limit(num)
    if(num > 6) then
        return 6
    end
    if(num < -6) then
        return -6
    end
    return num;
end
    
--技能导致能力变化
function change_attr_by_skill(m, s)
    local attrs = {
        [1] = function() 
            if(m:ability() == 2025 and s:lvl_attr() < 0) then return end    --怪力钳    攻击等级不会被降低  
            m:set_atk_lv(lv_limit(m:atk_lv() + s:lvl_attr())) 
        end,
        [2] = function() 
            if(m:ability() == 2023 and s:lvl_attr() < 0) then return end    --胸甲  防御等级不会被降低  
            m:set_def_lv(lv_limit(m:def_lv() + s:lvl_attr())) 
        end,
        [3] = function() 
            if(m:ability() == 2026 and s:lvl_attr() < 0) then return end    --念力  特攻等级不会降低    
            m:set_satk_lv(lv_limit(m:satk_lv() + s:lvl_attr())) 
        end,
        [4] = function() 
            if(m:ability() == 2027 and s:lvl_attr() < 0) then return end    --顽固  特防等级不会降低    
            m:set_sdef_lv(lv_limit(m:dsef_lv() + s:lvl_attr())) 
        end,
        [5] = function() 
            m:set_spd_lv(lv_limit(m:spd_lv() + s:lvl_attr())) 
        end,
        [6] = function() 
            if(m:ability() == 2024 and s:lvl_attr() < 0) then return end    --锐利目光  命中等级不会被降低  
            m:set_acc_lv(lv_limit(m:acc_lv() + s:lvl_attr())) 
        end,
        [7] = function() 
            m:set_crit_lv(lv_limit(m:crit_lv() + s:lvl_attr())) 
        end,
    }
   
    if(s:attr() < 1 or s:attr() > 7) then
        throw("lua", "no such attr")
    end
 
    attrs[s:attr()]()
    update_monster_attr(m)
end

function before_attack(m, s)
    if(m:ability() == 2007 and s:type() == 5) then      --蓄电  电系技能威力提升15% 
        m:set_mod_dmg_ability(1.15)
    elseif(m:ability() == 2008 and s:type() == 3) then  --贮水  水系技能威力提升15% 
        m:set_mod_dmg_ability(1.15)
    elseif(m:ability() == 2009 and s:type() == 2) then  --赤焰  火系技能威力提升15% 
        m:set_mod_dmg_ability(1.15)
    elseif(m:ability() == 2010 and s:type() == 4) then  --叶绿素    草系技能威力提升20% 
        m:set_mod_dmg_ability(1.2)
    elseif(m:ability() == 2011 and s:type() == 1) then  --单纯  普系技能威力提升15% 
        m:set_mod_dmg_ability(1.15)
    elseif(m:ability() == 2012 and s:type() == 8) then  --毒气  毒系技能威力提升20% 
        m:set_mod_dmg_ability(1.2)
    elseif(m:ability() == 2013 and s:type() == 10) then --强羽  飞系技能威力提升15% 
        m:set_mod_dmg_ability(1.15)
    elseif(m:ability() == 2014 and s:type() == 12) then --虫之力    虫系技能威力提升20% 
        m:set_mod_dmg_ability(1.2)
    elseif(m:ability() == 2015 and s:type() == 13) then --坚岩  岩系技能威力提升15% 
        m:set_mod_dmg_ability(1.15)
    else 
        m:set_mod_dmg_ability(1)
    end
end

function after_attack(m, s, h)
    if(m:ability() == 2016 and s:type() == 9) then      --浮游  受到地面系伤害减少50%
        return h * 0.5
    elseif(m:ability() == 2017 and s:type() == 5) then  --避雷针    受到电系伤害减少50% 
        return h * 0.5
    elseif(m:ability() == 2018 and s:type() == 6) then  --厚脂肪    受到的冰系伤害减少50%   
        return h * 0.5
    elseif(m:ability() == 2019 and s:type() == 2) then  --耐热  受到的火系伤害减少50%   
        return h * 0.5
    elseif(m:ability() == 2020 and s:type() == 3) then  --吸水  受到的水系伤害减少50%   
        return h * 0.5
    elseif(m:ability() == 2021 and s:type() == 16) then --正义之心  受到恶系技能攻击时，攻击等级提高1级
        m:set_atk_lv(lv_limit(m:atk_lv() + 1))
        return h 
    elseif(m:ability() == 2022 and s:type() == 11) then --呆滞  受到超系技能攻击时，防御与特防提升1级 
        m:set_def_lv(lv_limit(m:def_lv() + 1))
        m:set_sdef_lv(lv_limit(m:sdef_lv() + 1))
        return h
    else
        return h
    end 
end

--计算一个PM通过特定技能攻击另一个PM时造成的伤害
function monster_attack(res_a, res_b, monster_a, monster_b, skill)
    --伤害前技能判定
    before_attack(monster_a, skill)

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

    --伤害公式后技能特性判定
    hurt = after_attack(monster_b, skill, hurt)
    
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
 
        --异常判定后的特性判定
        if(pm:ability() == 2028) then                       --根性  处于异常状态时暴击等级+2    
            pm:set_crit_lv(lv_limit(pm:crit_lv() + 2))
        elseif(pm:ability() == 2029) then                   --神秘鳞片  处于异常状态时防御与特防等级+1  
            pm:set_def_lv(lv_limit(pm:def_lv() + 1))
            pm:set_sdef_lv(lv_limit(pm:sdef_lv() + 1))
        elseif(pm:ability() == 2030) then                   --蹒跚    异常状态下命中等级+2    
            pm:set_acc_lv(lv_limit(m:acc_lv() + 2))
        elseif(pm:ability() == 2031) then                   --电引擎    异常状态下速度等级+2    
            pm:set_spd_lv(lv_limit(m:spd_lv() + 2))
        end
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
