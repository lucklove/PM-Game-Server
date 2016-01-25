#pragma once
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>
#include <redox.hpp>
#include "dispatcher/Dispatcher.hh"
#include "utils/ThreadPool.hh"

struct RedisSession
{
    redox::Redox session;
 
    RedisSession(const std::string& host, short port)
    {   
        if(!session.connect(host, port))
            throw std::runtime_error{"connect to redis server failed"};
    }   

    ~RedisSession() noexcept(noexcept(session.disconnect()))
    {
        session.disconnect();
    }   
};

class DBAccess
{
private:
    static ThreadPool& worker()
    {
        static ThreadPool pool{std::thread::hardware_concurrency()};
        return pool;
    }

public:
    static void mysql_query(std::function<void(soci::session&)> func)
    {
        auto future = worker().enqueue([&func]
        {
            static soci::session session{soci::mysql, "db=pocket_monster_db user=root pass=lucklove"};
            func(session);
        });

        while(future.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
            Dispatcher::getInstance().yield();
    }

    static void redis_query(std::function<void(redox::Redox&)> func)
    {
        auto future = worker().enqueue([&func]
        {
            static RedisSession redox{"localhost", 6379};
            func(redox.session);
        });

        while(future.wait_for(std::chrono::milliseconds(0)) == std::future_status::timeout)
            Dispatcher::getInstance().yield();
    }
};
