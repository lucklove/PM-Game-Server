#pragma once
#include <functional>

/** 表示一个回合 */
class Round
{
private:
    std::array<std::function<void()>, 4> callbacks_;
    size_t cur_ = 0;

public:
    template <typename F, typename... Params>
    void onFirstDebuff(F&& f, Params&&... params)
    {
        callbacks_[0] = [&]{ f(std::forward<Params>(params)...); };
    }

    template <typename F, typename... Params>
    void onFirstAttack(F&& f, Params&&... params)
    {
        callbacks_[1] = [&]{ f(std::forward<Params>(params)...); };
    }

    template <typename F, typename... Params>
    void onLastDebuff(F&& f, Params&&... params)
    {
        callbacks_[2] = [&]{ f(std::forward<Params>(params)...); };
    }

    template <typename F, typename... Params>
    void onLastAttack(F&& f, Params&&... params)
    {
        callbacks_[3] = [&]{ f(std::forward<Params>(params)...); };
    }

    /** 跳过 */
    void skip(size_t n = 1)
    {
        cur_ += n;
    }

    void apply()
    {
        while(cur_ < callbacks_.size())
        {
            callbacks_[cur_]();
            ++cur_;
        }   
    } 
};
