function monster_test(m)
    m:set_level(100);
end

function fib(n)
    if(n < 3) then
        return 1
    else
        return fib(n - 1) + fib(n - 2)
    end
end

m = get_monster(25)
print(m:type1())
