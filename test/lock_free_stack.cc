#include "UnitTest.hh"
#include "utils/LockFreeStack.hh"
#include <thread>

TEST_CASE(store_uncopyable)
{
    LockFreeStack<std::unique_ptr<int>> s;
    s.push(nullptr);
    auto v = s.pop();
    TEST_REQUIRE(v);
    TEST_CHECK(*v == nullptr);
}

TEST_CASE(lock_free_stack_single_thread)
{
    LockFreeStack<std::string> s;
    s.push("hello");
    s.push("world");

    auto x = s.pop();
    TEST_REQUIRE(x);
    TEST_CHECK(*x == "world");

    x = s.pop();
    TEST_REQUIRE(x);
    TEST_CHECK(*x == "hello");

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

TEST_CASE(poll)
{
    std::atomic<size_t> sum{0};
    LockFreeStack<size_t> stk;
    std::vector<std::thread> consumers;
    std::vector<std::thread> productors;
        
    std::cout << "poll lock free stack, if blocked, interrupt test please" << std::endl;

    for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        consumers.push_back(std::thread([&]
        {
            while(sum.load(std::memory_order_acquire) != 49995000 * std::thread::hardware_concurrency())
            {
                auto v = stk.pop();
                if(v) sum += *v; 
            }   
        }));
    
        productors.push_back(std::thread([&]
        {
            for(size_t i = 0; i < 10000; ++i)
                stk.push(i);
        }));
    }

    for(auto& t : consumers)
        t.join();

    for(auto& t : productors)
        t.join();

    std::cout << "poll test end" << std::endl;
}

TEST_CASE(leak_check)
{
    static std::atomic<size_t> count{0};

    struct T
    {
        T()
        {
            count += 1;
        }

        T(const T&)
        {
            count += 1;
        }

        ~T()
        {
            count -= 1;
        }
    };

    {
        LockFreeStack<T> stk;
        std::vector<std::thread> consumers;
        std::vector<std::thread> productors;

        for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
        {   
            productors.push_back(std::thread([&]
            {
                for(size_t i = 0; i < 5; ++i)
                    stk.push(T{});
            }));
        }

        for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
        {
            consumers.push_back(std::thread([&]
            {
                Optional<T> opt;
                while((opt = stk.pop()))
                {
                }
            }));
        }

        for(auto& t : consumers)
            t.join();

        for(auto& t : productors)
            t.join();
    }

    TEST_CHECK(count == 0);    
}
