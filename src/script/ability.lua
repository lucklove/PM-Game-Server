--施加战前特性效果
function apply_battle_prefix_ability(pm_a, pm_b)
    --先判定是否禁用对方特性
    if(pm_a:ability() == 1016) then         --破格
        pm_b:set_ability(0)                 --禁用对方特性
        return
    end 

    --判断是否复制对方特性
    if(pm_a:ability() == 1012) then         --复制
        pm_a:set_ability(pm_b:ability())
    end

    func_tb = {}
    func_tb[1001] = function() pm_a:set_atk_lv(pm_a:atk_lv() + 1)  end          --奋斗
    func_tb[1002] = function() pm_a:set_def_lv(pm_a:def_lv() + 1)  end          --坚硬
    func_tb[1003] = function() pm_a:set_satk_lv(pm_a:satk_lv() + 1)  end        --发光
    func_tb[1004] = function() pm_a:set_sdef_lv(pm_a:sdef_lv() + 1)  end        --魔甲
    func_tb[1005] = function() pm_a:set_spd_lv(pm_a:spd_lv() + 1)  end          --加速
    func_tb[1006] = function() pm_a:set_acc_lv(pm_a:acc_lv() + 1)  end          --复眼
    func_tb[1007] = function() pm_a:set_crit_lv(pm_a:crit_lv() + 1)  end        --强运
    func_tb[1008] = function() pm_b:set_atk_lv(pm_b:atk_lv() - 1)  end          --恐吓
    func_tb[1009] = function() pm_b:set_satk_lv(pm_b:satk_lv() - 1)  end        --压力
    func_tb[1010] = function() pm_b:set_spd_lv(pm_b:spd_lv() - 1)  end          --粘稠
    func_tb[1011] = function() pm_b:set_acc_lv(pm_b:acc_lv() - 1)  end          --预知梦
    func_tb[1013] = function() pm_a:set_mod_dmg_ability(1.15) end               --瑜伽之力
    func_tb[1014] = function() pm_a:set_spd_lv(pm_a:spd_lv() - 2) end           --懒惰
    func_tb[1015] = function()                                                  --下载
        if(pm_b:def_lv() > pm_a:def_lv()) then
            pm_a:set_atk_lv(pm_a:atk_lv() + 1)
        end
        if(pm_b:sdef_lv() > pm_a:sdef_lv()) then
            pm_a:set_satk_lv(pm_a:satk_lv() + 1)
        end
    end           
    func_tb[1017] = function() pm_a:set_mod_acc_ability(1.15) end               --胜利之星
    func_tb[1018] = function() pm_b:set_round_ability(1) end                    --恶臭
    func_tb[1019] = function() pm_a:set_crit_multi(1.5) end                     --狙击手
    func_tb[1020] = function() pm_a:set_mod_type_value(1) end                   --适应力

    local a_func = func_tb[pm_a:ability()]
    if(a_func ~= nil) then
        a_func()
    end
end

--战前特性判定
function before_battle(pm_a, pm_b)
    apply_battle_prefix_ability(pm_a, pm_b);
    apply_battle_prefix_ability(pm_b, pm_a);
end


--技能前触发类特性
function before_skill(m, s)
    func_tb = {}
    func_tb[3001] = function()                                                  --贝壳盔甲
        if(m:cur_hp() == full_hp(m)) then
            return
        end 
        if(m:def_lv() < 1) then
            m:set_def_lv(1)
        end
        if(m:sdef_lv() < 1) then
            m:set_sdef_lv(1)
        end
    end
    func_tb[3002] = function()                                                  --轻身
        if(m:cur_hp() < full_hp(m) / 3) then
            if(m:spd_lv() < 4) then
                m:set_spd_lv(4)
            end
        end
    end
    func_tb[3003] = function()                                                  --不屈之心
        if(m:debuff_cur() ~= 0) then
            m:set_mod_dmg_ability(1.3)
        end
    end
    func_tb[3004] = function()                                                  --怒穴
        if(m:cur_hp() < full_hp(m) / 3) then
            if(m:atk_lv() < 3) then
                m:set_atk_lv(3)
            end
        end
    end
    func_tb[3005] = function()                                                  --拼命
        if(m:cur_hp() < full_hp(m) / 2) then
            if(m:crit_lv() < 4) then
                m:set_crit_lv(4)
            end
        end
    end
    --麻痹:1 中毒:2 睡眠:3 冰冻:4 烧伤:5 害怕:6
    func_tb[3006] = function()                                                  --胆小
        if(m:debuff_cur() == 6) then     --害怕
            if(m:def_lv() < 2) then
                m:set_def_lv(2)
            end
            if(m:sdef_lv() < 2) then
                m:set_sdef_lv(2)
            end
        end 
    end
    func_tb[3007] = function()                                                  --点穴
        if(m:debuff_cur() == 1) then     --麻痹
            if(m:crit_lv() < 2) then
                m:set_crit_lv(2)
            end
        end
    end
    func_tb[3008] = function()                                                  --点爆
        if(m:debuff_cur() == 4) then     --烧伤
            if(m:spd_lv() < 2) then
                m:set_spd_lv(2)
            end
        end
    end
    func_tb[3009] = function()                                                  --毒刺
        if(m:debuff_cur() == 2) then     --中毒
            if(m:atk_lv() < 1) then
                m:set_atk_lv(1)
            end
            if(m:satk_lv() < 1) then
                m:set_satk_lv(1)
            end
        end
    end
    func_tb[3010] = function()                                                  --吃货
        if(m:cur_hp() == full_hp(m)) then
            if(m:spd_lv() < 2) then
                m:set_spd_lv(2)
            end
        end
    end
    func_tb[3011] = function()                                                  --大力士
        if(s:power() >= 100) then
            m:set_mod_acc_ability(1.2)
        end
    end
    func_tb[3012] = function()                                                  --技师
        if(s:power() <= 60) then
            m:set_mod_dmg_ability(1.5)
        end
    end

    local a_func = func_tb[m:ability()]
    if(a_func ~= nil) then
        a_func()
    end
end
