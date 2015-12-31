function get_debuff(n)
    if(n < 1 or n > 6) then
        throw("lua", "no such debuff");
    end
    
    local table = 
    {
        function(r)                                             --麻痹
            if(math.random(0, 100) <= 25) then
                r:setb("sleep", true)
                return false
            end
            return true
        end,

        function(r, m)                                          --中毒
            local max_hp = m:level() * m:bs_hp() / 50 + m:ev_hp() / 4 + 10 + m:level()
            r:setn("debuff_harm", max_hp * 0.125)
            m:set_cur_hp(m:cur_hp() - max_hp * 0.125)
            return true
        end,
        
        function()                                              --睡眠
            return false
        end,

        function()                                              --冰冻
            return false
        end,

        function(r, m)                                          --烧伤
            local max_hp = m:level() * m:bs_hp() / 50 + m:ev_hp() / 4 + 10 + m:level()
            r:setn("debuff_harm", max_hp * 0.0625);
            m:set_cur_hp(m:cur_hp() - max_hp * 0.0625)
            return true
        end,

        function()                                              --害怕
            return false
        end
    }

    return table[n]
end
