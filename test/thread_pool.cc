#include "UnitTest.hh"
#include "utils/ThreadPool.hh"

TEST_CASE(thread_pool_simple_test)
{
    ThreadPool tp(3);
    auto f1 = tp.enqueue([]
    {
        return 47;
    });
    auto f2 = tp.enqueue([]
    {
        return 48;
    });
    auto f3 = tp.enqueue([]
    {
        return 49;
    });
    TEST_CHECK(f1.get() == 47);
    TEST_CHECK(f2.get() == 48);
    TEST_CHECK(f3.get() == 49);
}

TEST_CASE(enter_exit)
{
    bool enter_flag = false;
    bool exit_flag = false;
    bool exec_flag = false;
    {
        ThreadPool pool(1, [&]
        {   
            enter_flag = true;
        }, [&]{ 
            exit_flag = true;
        }); 
        pool.enqueue([&]
        {   
            exec_flag = true;    
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }); 
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    TEST_CHECK(exec_flag);
    TEST_CHECK(enter_flag);
    TEST_CHECK(exit_flag);
}
