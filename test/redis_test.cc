#include "UnitTest.hh"
#include "ScopeGuard.hh"
#include "AsyncWrapper.hh"
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
