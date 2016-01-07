function get_debuff(n)
    if(n < 1 or n > 6) then
        throw("lua", "no such debuff");
    end
    
    local table = 
    {
        function(r, m)                                          --麻痹
            if(m:ability() == 2003) then    --柔软(免疫麻痹)
                return true
            end
            if(math.random(0, 100) <= 25) then
                r:setb("sleep", true)
                return false
            end
            return true
        end,

        function(r, m)                                          --中毒
            if(m:ability() == 2002) then    --毒疗(免疫中毒)
                return true
            end
            local max_hp = m:level() * m:bs_hp() / 50 + m:ev_hp() / 4 + 10 + m:level()
            r:setn("debuff_harm", max_hp * 0.125)
            m:set_cur_hp(m:cur_hp() - max_hp * 0.125)
            return true
        end,
        
        function(r, m)                                          --睡眠
            if(m:ability() == 2001) then    --不眠(免疫睡眠)
                return true
            end
            return false
        end,

        function(r, m)                                          --冰冻
            if(m:ability() == 2005) then    --冰盾(免疫冰冻)
                return true
            end
            return false
        end,

        function(r, m)                                          --烧伤
            if(m:ability() == 2006) then    --引火(免疫烧伤)
                return true
            end
            local max_hp = m:level() * m:bs_hp() / 50 + m:ev_hp() / 4 + 10 + m:level()
            r:setn("debuff_harm", max_hp * 0.0625);
            m:set_cur_hp(m:cur_hp() - max_hp * 0.0625)
            return true
        end,

        function(r, m)                                          --害怕
            if(m:ability() == 2004) then    --勇气(免疫害怕)
                return true
            end
            return false
        end
    }

    return table[n]
end
