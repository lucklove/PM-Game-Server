#pragma once
#include "LockFreeQueue.hh"
#include <vector>
#include <future>
#include <thread>
#include <cassert>

class ThreadPool
{
private:
    std::vector<std::thread> workers_;
    LockFreeQueue<std::function<void()>> tasks_;
    bool stopped_;

public:
    ThreadPool(size_t size, std::function<void()> on_enter = {}, std::function<void()> on_exit = {})
    {
        for(size_t i = 0; i < size; ++i)
        {
            workers_.push_back(std::thread([=]
            {
                if(on_enter) on_enter();
                while(true)
                {
                    auto task_opt = tasks_.pop();
                    if(!task_opt)
                    {
                        if(stopped_)
                        { 
                            break;
                        }
                        else
                        {
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }
                    }
                    else
                    {
                        try
                        {
                            (*task_opt)();
                        }
                        catch(std::future_error&)
                        {
                            assert(false);
                        } 
                    }
                }
                if(on_exit) on_exit();
            }));
        }
    }

    ~ThreadPool() noexcept
    {
        try
        {
            stopped_ = true;
            for(auto& worker : workers_)
            {
                try
                {
                    worker.join();
                }
                catch(std::system_error&)
                {
                }
            }
        }
        catch(...)
        {
            assert(false);
        }
    }

    template<typename F, typename... Params>
    std::future<typename std::result_of<F(Params...)>::type>
    enqueue(F&& func, Params&&... params)
    {
        auto tsk = std::make_shared<std::packaged_task<typename std::result_of<F(Params...)>::type()>>(
            std::bind(std::forward<F>(func), std::forward<Params>(params)...));
        auto res = tsk->get_future();

        tasks_.push([tsk]
        {
            (*tsk)();
        });

        return std::move(res);
    }
};
