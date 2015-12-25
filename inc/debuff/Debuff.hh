#pragma once
#include "battle/Monster.hh"
#include "utils/Random.hh"
#include "result/Result.hh"
#include <vector>

struct Debuff
{
    virtual bool apply(Result result, Monster& m) const = 0;
    virtual ~Debuff() = default;
};

template <size_t Id>
struct ConcretDebuff : Debuff           /**< 禁止构造实例 */
{
};

template <>
struct ConcretDebuff<1> : Debuff        /**< 麻痹 */
{
    bool apply(Result result, Monster& m) const override
    {
        if(Random::get(0, 100) <= 25)
        {
            result.set("sleep", true);
            return false;
        }
        return true;
    }
};

template <>
struct ConcretDebuff<2> : Debuff        /**< 中毒 */
{
    bool apply(Result result, Monster& m) const override
    {
        int max_hp = m.level * m.bs_hp / 50 + m.ev_hp / 4 + 10 + m.level;
        result.set("debuff_harm", max_hp * 0.125);
        m.cur_hp -= max_hp * 0.125;
        return true;
    }    
}; 

template <>
struct ConcretDebuff<3> : Debuff        /**< 睡眠 */
{
    bool apply(Result result, Monster& m) const override
    {
        return false;
    }
};

template <>
struct ConcretDebuff<4> : Debuff        /**< 冰冻 */
{
    bool apply(Result result, Monster& m) const override
    {
        return false;
    }
};

template <>
struct ConcretDebuff<5> : Debuff        /**< 烧伤 */
{
    bool apply(Result result, Monster& m) const override
    {
        int max_hp = m.level * m.bs_hp / 50 + m.ev_hp / 4 + 10 + m.level;
        result.set("debuff_harm", max_hp * 0.0625);
        m.cur_hp -= max_hp * 0.0625;
        return true;
    }
};

template <>
struct ConcretDebuff<6> : Debuff        /**< 害怕 */
{
    bool apply(Result result, Monster& m) const override
    {
        return false;
    }
};
