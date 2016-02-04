#include "UnitTest.hh"
#include "dispatcher/Dispatcher.hh"

TEST_CASE(dispatcher)
{
    Dispatcher& dispatcher = Dispatcher::getInstance();

    bool tsk1_ok = false;
    bool tsk2_ok = false;
    size_t odd_count = 0;
    size_t even_count = 0;

    dispatcher.enqueue([&]
    {
        for(size_t i = 0; i < 1000; i += 2)
        {
            ++even_count;
            dispatcher.yield();
        }
        tsk1_ok = true;
    });

    dispatcher.enqueue([&]
    {
        for(size_t i = 1; i < 1000; i += 2)
        {
            ++odd_count;
            dispatcher.yield();
        }
        tsk2_ok = true;
    });
    
    while(!(tsk1_ok && tsk2_ok))
        std::this_thread::sleep_for(std::chrono::milliseconds(0));
    
    TEST_CHECK(odd_count == 500);
    TEST_CHECK(even_count == 500);
}
