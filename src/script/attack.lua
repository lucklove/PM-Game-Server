function handleAttack(result, battle_id, skill_id)
    local battle = get_battle(battle_id)
    local role_pm = battle:role_pm()
    local enemy_pm = battle:enemy_pm()
    local role_skill = get_skill(skill_id)
    local enemy_skill = get_skill(enemy_pm:peekSkill())
    local role_res = result:get("role")
    local enemy_res = result:get("enemy")

    if(is_first(role_pm, enemy_pm, role_skill, enemy_skill)) then
        result:sets("firstMove", "role")
        if(tick_debuff(role_res, role_pm)) then
            before_skill(role_pm, role_skill)
            monster_attack(role_res, enemy_res, role_pm, enemy_pm, role_skill)     
        end
        if(tick_debuff(enemy_res, enemy_pm)) then
            before_skill(enemy_pm, enemy_skill)
            monster_attack(enemy_res, role_res, enemy_pm, role_pm, enemy_skill)     
        end
    else
        result:sets("firstMove", "enemy")
        if(tick_debuff(enemy_res, enemy_pm)) then
            before_skill(enemy_pm, enemy_skill)
            monster_attack(enemy_res, role_res, enemy_pm, role_pm, enemy_skill)     
        end
        if(tick_debuff(role_res, role_pm)) then
            before_skill(role_pm, role_skill)
            monster_attack(role_res, enemy_res, role_pm, enemy_pm, role_skill)     
        end
    end

    if(role_pm:cur_hp() > 0 and enemy_pm:cur_hp() > 0) then
        role_res:setn("hp", role_pm:cur_hp())
        enemy_res:setn("hp", enemy_pm:cur_hp())
        battle:set_role_pm(role_pm)
        battle:set_enemy_pm(enemy_pm)
        set_battle(battle_id, battle)
    else
        if(role_pm:cur_hp() <= 0) then
            role_res:setb("dead", true)
        elseif(enemy_pm:cur_hp() <= 0) then
            enemy_res:setb("dead", true)
        end
        del_battle(battle_id)
    end
end
