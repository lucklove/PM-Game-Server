#pragma once
#include "battle/Round.hh"
#include "battle/Monster.hh"
#include "utils/Random.hh"
#include "crow/json.h"
#include <vector>

struct Debuff
{
    virtual void apply(crow::json::wvalue& result, Round& round, Monster& m) const = 0;
    virtual ~Debuff() = default;
};

template <size_t Id>
struct ConcretDebuff : Debuff           /**< 禁止构造实例 */
{
};

template <>
struct ConcretDebuff<1> : Debuff        /**< 麻痹 */
{
    void apply(crow::json::wvalue& result, Round& round, Monster& m) const override
    {
        if(Random::get(0, 100) <= 25)
        {
            result["sleep"] = true;
            round.skip();
        }
    }
};

template <>
struct ConcretDebuff<2> : Debuff        /**< 中毒 */
{
    void apply(crow::json::wvalue& result, Round& round, Monster& m) const override
    {
        int max_hp = m.level * m.bs_hp / 50 + m.ev_hp / 4 + 10 + m.level;
        result["debuff_harm"] = max_hp * 0.125;
        m.cur_hp -= max_hp * 0.125;
    }    
}; 

template <>
struct ConcretDebuff<3> : Debuff        /**< 睡眠 */
{
    void apply(crow::json::wvalue& result, Round& round, Monster& m) const override
    {
        round.skip();
    }
};

template <>
struct ConcretDebuff<4> : Debuff        /**< 冰冻 */
{
    void apply(crow::json::wvalue& result, Round& round, Monster& m) const override
    {
        round.skip();
    }
};

template <>
struct ConcretDebuff<5> : Debuff        /**< 烧伤 */
{
    void apply(crow::json::wvalue& result, Round& round, Monster& m) const override
    {
        int max_hp = m.level * m.bs_hp / 50 + m.ev_hp / 4 + 10 + m.level;
        result["debuff_harm"] = max_hp * 0.0625;
        m.cur_hp -= max_hp * 0.0625;
    }
};

template <>
struct ConcretDebuff<6> : Debuff        /**< 害怕 */
{
    void apply(crow::json::wvalue& result, Round& round, Monster& m) const override
    {
        round.skip();
    }
};
