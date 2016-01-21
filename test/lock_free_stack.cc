#include "UnitTest.hh"
#include "utils/LockFreeStack.hh"
#include <thread>

TEST_CASE(lock_free_stack_single_thread)
{
    LockFreeStack<int> s;
    s.push(1);
    s.push(2);

    auto x = s.pop();
    TEST_REQUIRE(x);
    TEST_CHECK(*x == 2);

    x = s.pop();
    TEST_REQUIRE(x);
    TEST_CHECK(*x == 1);

    x = s.pop();
    TEST_CHECK(!x);
}

TEST_CASE(multi_thread_sum)
{
    std::atomic<size_t> sum{0};
    LockFreeStack<size_t> stk;
    std::vector<std::thread> input_p;
    std::vector<std::thread> output_p;

    for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        input_p.push_back(std::thread([&]
        {
            for(size_t i = 0; i < 10000; ++i)
                stk.push(i);
        }));
    }

    for(auto& t : input_p)
        t.join();

    for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        output_p.push_back(std::thread([&]
        {
            for(size_t i = 0; i < 10000; ++i)
            {
                auto opt = stk.pop();
                TEST_REQUIRE(opt);
                sum += *opt;
            }
        }));
    }

    for(auto& t : output_p)
        t.join();

    auto x = stk.pop();
    TEST_CHECK(!x);

    TEST_CHECK(sum == 49995000 * std::thread::hardware_concurrency());
}
