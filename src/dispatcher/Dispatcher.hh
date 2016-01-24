#pragma once
#include <thread>
#include <functional>
#include <cassert>
#include <boost/coroutine/all.hpp>
#include "utils/LockFreeQueue.hh"
#include "utils/LockFreeStack.hh"

template <size_t thread_num, size_t coro_num>
class Dispatcher
{
    static_assert(thread_num <= coro_num, "worker threads can not be more than coroutines number.");
private:
    typedef boost::coroutines::asymmetric_coroutine<bool>::pull_type pull_coro_t;
    typedef boost::coroutines::asymmetric_coroutine<bool>::push_type push_coro_t;

    LockFreeQueue<std::function<void()>> task_queue_;
    LockFreeQueue<pull_coro_t> work_coros_;
    LockFreeStack<pull_coro_t> suspend_coros_;
    std::vector<std::thread> workers_;
    bool stopped_;

public:

    Dispatcher() : stopped_{false}
    {
        for(size_t i = 0; i < coro_num; ++i)
        {
            suspend_coros_.push(pull_coro_t([&](push_coro_t& sink)
            {
                pusher(&sink);
                Optional<std::function<void()>> tsk;
                while(!stopped_)
                {
                    try
                    {
                        while(!(tsk = task_queue_.pop()))
                            yield(true);
                        (*tsk)();
                    }
                    catch(...)
                    {
                    }
                }
            }));
        }
        
        for(size_t i = 0; i < thread_num; ++i)
        {
            workers_.push_back(std::thread([this]
            {
                try
                {
                    while(!stopped_)
                    {
                        Optional<pull_coro_t> co;
                        if(!task_queue_.empty() && !suspend_coros_.empty())
                            co = suspend_coros_.pop();
                        if(!co) co = work_coros_.pop();
                        if(!co)
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                            continue;
                        }

                        (*co)();

                        if(co->get())
                        {
                            suspend_coros_.push(std::move(*co));
                        }
                        else
                        {
                            work_coros_.push(std::move(*co));
                        }
                    }
                }
                catch(...)
                {
                    assert(false && "unexpected exception");
                }
            }));
        }
    }
  
    ~Dispatcher()
    {
        stopped_ = true;

        for(auto& worker : workers_)
            worker.join();
    }
 
    void yield(bool suspend = false)
    {
        push_coro_t* saved_pusher = pusher();
        ScopeGuard pusher_guard([&]
        {
            pusher(saved_pusher);
        });

        (*saved_pusher)(suspend);
    }

    push_coro_t* pusher(push_coro_t* p = nullptr)
    {
        thread_local push_coro_t* saved_pusher = nullptr;
        if(p) saved_pusher = p;
        assert(saved_pusher && "no specificed pusher");
        return saved_pusher;
    }

    void enqueue(std::function<void()> tsk)
    {
        task_queue_.push(tsk);
    }
};
