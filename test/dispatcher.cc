#include "UnitTest.hh"
#include "dispatcher/Dispatcher.hh"

TEST_CASE(dispatcher)
{
    Dispatcher& dispatcher = Dispatcher::getInstance();

    bool tsk1_ok = false;
    bool tsk2_ok = false;

    dispatcher.enqueue([&]
    {
        for(size_t i = 0; i < 1000; i += 2)
        {
            std::cout << i << std::endl;
                dispatcher.yield();
        }
        tsk1_ok = true;
    });

    dispatcher.enqueue([&]
    {
        for(size_t i = 1; i < 1000; i += 2)
        {
            std::cout << i << std::endl;
                dispatcher.yield();
        }
        tsk2_ok = true;
    });
    
    while(!(tsk1_ok && tsk2_ok))
        std::this_thread::sleep_for(std::chrono::milliseconds(0));
}
