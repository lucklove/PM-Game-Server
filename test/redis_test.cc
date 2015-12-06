#include "UnitTest.hh"
#include "utils/ScopeGuard.hh"
#include "utils/AsyncWrapper.hh"
#include <redox.hpp>

TEST_CASE(redis_sync_read_write)
{
    redox::Redox rdx;
    TEST_REQUIRE(rdx.connect("localhost", 6379));
    ScopeGuard on_exit([&]{ rdx.disconnect(); });
    rdx.set("hello", "world");
    TEST_CHECK(rdx.get("hello") == "world");
}

TEST_CASE(redis_async_read)
{
    redox::Redox rdx;
    TEST_REQUIRE(rdx.connect("localhost", 6379));
    ScopeGuard on_exit([&]{ rdx.disconnect(); });

    rdx.set("hello", "world");

    wrapAsync([&](auto callback)
    {
        rdx.command<std::string>({"GET", "hello"}, callback);    
    }).then([&](redox::Command<std::string>& c)
    {
        TEST_CHECK(c.ok());
        rdx.stop();
    }).apply();

    rdx.wait(); // Block until shut down complete
}
/*
TEST_CASE(reply_test)
{
    redox::Redox rdx;
    TEST_REQUIRE(rdx.connect("localhost", 6379));
    ScopeGuard on_exit([&]{ rdx.disconnect(); });
 
    rdx.commandSync<int>({"HSET", "user:1", "name", "namevar"}).free();    
    rdx.commandSync<int>({"HSET", "user:1", "age", "13"}).free();
   
    rdx.command<std::vector<std::string>>({"HMGET", "user:1", "name", "nn"}, [&](redox::Command<std::vector<std::string>>& c)
    {
        std::cout << c.reply().size() << std::endl;
        std::cout << c.reply()[0] << std::endl;
        std::cout << c.reply()[1] << std::endl;
        rdx.stop();
//        std::cout << c.reply()[1] << std::endl;
    });
    rdx.wait();
};
*/
