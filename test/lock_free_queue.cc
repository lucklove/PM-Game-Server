#include "UnitTest.hh"
#include "utils/LockFreeQueue.hh"
#include <thread>

TEST_CASE(lock_free_queue_single_thread)
{
    LockFreeQueue<std::string> q;
    q.push("hello");
    q.push("world");
    
    auto x = q.pop();
    TEST_REQUIRE(x);
    TEST_CHECK(*x == "hello"); 

    x = q.pop();
    TEST_REQUIRE(x);
    TEST_CHECK(*x == "world"); 

    x = q.pop();
    TEST_CHECK(!x);
}

TEST_CASE(multi_thread_sum)
{
    std::atomic<size_t> sum{0};
    LockFreeQueue<size_t> que;
    std::vector<std::thread> input_p;
    std::vector<std::thread> output_p;

    for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        input_p.push_back(std::thread([&]
        {
            for(size_t i = 0; i < 10000; ++i)
                que.push(i);
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
                auto opt = que.pop();
                TEST_REQUIRE(opt, sum);
                sum += *opt;
            }
        }));
    }

    for(auto& t : output_p)
        t.join();

    auto x = que.pop();
    TEST_CHECK(!x);

    TEST_CHECK(sum == 49995000 * std::thread::hardware_concurrency());
}

TEST_CASE(poll)
{
    std::atomic<size_t> sum{0};
    LockFreeQueue<size_t> que;
    std::vector<std::thread> consumers;
    std::vector<std::thread> productors;
   
    std::cout << "poll lock free queue, if blocked, interrupt test please" << std::endl;

    for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {
        consumers.push_back(std::thread([&]
        {
            while(sum.load(std::memory_order_acquire) < 49995000 * std::thread::hardware_concurrency())
            {
                auto v = que.pop();
                if(v) 
                    sum += *v;
            }
        }));
    }

    for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
    {   
        productors.push_back(std::thread([&]
        {
            for(size_t i = 0; i < 10000; ++i)
                que.push(i);
        }));
    }

    for(auto& t : consumers)
        t.join();

    for(auto& t : productors)
        t.join();

    TEST_CHECK(sum == 49995000 * std::thread::hardware_concurrency());

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
        LockFreeQueue<T> que;
        std::vector<std::thread> consumers;
        std::vector<std::thread> productors;

        for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
        {   
            productors.push_back(std::thread([&]
            {
                for(size_t i = 0; i < 5; ++i)
                    que.push(T{});
            }));
        }

        for(size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
        {
            consumers.push_back(std::thread([&]
            {
                Optional<T> opt;
                while((opt = que.pop()))
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
