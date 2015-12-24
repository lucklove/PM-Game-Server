-- 这个文件用于测试lua宿主提供的函数是否工作正常
-- 所有测试函数以test_xxx方式命名

function test_get_monster()
    print("测试get_monster...")
    local m = get_monster(25)
    assert(m:name() == "喷火龙")
    print("get_monster测试完成")
end

function test_get_skill()
    print("测试get_skill...")
    local s = get_skill(47)
    assert(s:name() == "唱歌")
    print("get_skill测试完成")
end

function test_get_aioi()
    print("测试get_aioi...")
    assert(get_aioi(0, 0) == 1)
    print("get_aioi测试完成")
end

function test_get_debuff()
    local debuff = get_debuff(1)
end

function test_random()
    print("测试random...")
    assert(randomi(11, 47) < 48)
    assert(randomi(11, 47) > 10)
    assert(randomf(11, 47) <= 47)
    assert(randomf(11, 47) >= 11)
    print("random测试完成")
end

function run_all_tests()
    print("测试lua环境...")
    test_get_monster()
    test_get_skill()
    test_get_aioi()
    test_get_debuff()
    test_random()
    print("lua环境测试完成")
end

run_all_tests()
