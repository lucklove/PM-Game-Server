#pragma once
#include <string>
#include <soci/soci.h>
#include "cereal/archives/json.hpp"

struct Monster
{
    int id;              /**< 精灵ID */
    std::string name;    /**< 精灵名称 */
    int level;           /**< 精灵等级 */
    int exp;             /**< 精灵经验 */
    int type;            /**< 精灵属性 */

    /** 区分不同PM的数值，主要读取配表数值 */
    int bs_hp;           /**< 生命种族值 */
    int bs_atk;          /**< 攻击种族值 */
    int bs_def;          /**< 防御种族值 */
    int bs_satk;         /**< 特攻种族值 */
    int bs_sdef;         /**< 特防种族值 */
    int bs_spd;          /**< 速度种族值 */

    /** 玩家可控的属性成长点，吃药提升每项最高255，所有努力值之和不超过510 */
    int ev_hp;           /**< 生命努力值 */
    int ev_atk;          /**< 攻击努力值 */
    int ev_def;          /**< 防御努力值 */
    int ev_satk;         /**< 特攻努力值 */
    int ev_sdef;         /**< 特防努力值 */
    int ev_spd;          /**< 速度努力值 */

    /** 战斗中影响属性变化的数据 */
    int atk_lv;           /**< 攻击等级 */
    int def_lv;           /**< 防御等级 */
    int satk_lv;          /**< 特攻等级 */
    int sdef_lv;          /**< 特防等级 */
    int spd_lv;           /**< 速度等级 */
    int acc_lv;           /**< 命中等级 */
    int crit_lv;          /**< 暴击等级 */

    /** 临时类属性，由技术评估 */
    int crit_rate;        /**< 暴击率 */
    int crit_multi;       /**< 暴击倍数 */
    int cur_hp;           /**< 当前生命 */
    int cur_atk;          /**< 最终攻击力 */
    int cur_def;          /**< 最终防御 */
    int cur_satk;         /**< 最终特攻 */
    int cur_sdef;         /**< 最终特防 */
    int cur_spd;          /**< 最终速度 */
   
    int skill1; 
    int skill2; 
    int skill3; 
    int skill4; 

    int ability;         /**< 特性ID，影响计算参数 */
    
    template <typename Archive>
    void serialize(Archive & ar)
    {
        ar(
            id, name, level, exp, type, bs_hp, bs_atk, bs_def, bs_satk, bs_sdef, bs_spd,
            ev_hp, ev_atk, ev_def, ev_satk, ev_sdef, ev_spd, atk_lv, def_lv, satk_lv, sdef_lv,
            spd_lv, acc_lv, crit_lv, skill1, skill2, skill3, skill4, ability
        );
    }

    void to_stream(std::ostream& os) const
    {
        cereal::JSONOutputArchive oarchive(os);
        oarchive(*this);   
    }

    void from_stream(std::istream& is)
    {
       cereal::JSONInputArchive iarchive(is);
       iarchive(*this); 
    }
};

namespace soci
{
    template<>
    struct type_conversion<Monster>
    {
        typedef values base_type;

        static void from_base(const values& v, indicator /* ind */, Monster& m)
        {
            m = { 
                v.get<int>("id"), v.get<std::string>("name"), v.get<int>("level"), v.get<int>("exp"),
                v.get<int>("type"), v.get<int>("bs_hp"), v.get<int>("bs_atk"), v.get<int>("bs_def"),
                v.get<int>("bs_satk"), v.get<int>("bs_sdef"), v.get<int>("bs_spd"), v.get<int>("ev_hp"),
                v.get<int>("ev_atk"), v.get<int>("ev_def"), v.get<int>("ev_satk"), v.get<int>("ev_sdef"),
                v.get<int>("ev_spd"), v.get<int>("atk_lv"), v.get<int>("def_lv"), v.get<int>("satk_lv"), 
                v.get<int>("sdef_lv"), v.get<int>("spd_lv"), v.get<int>("acc_lv"), v.get<int>("crit_lv"), 
                0, 0, 0, 0, 0, 0, 0, 0,
                v.get<int>("skill1"), v.get<int>("skill2"), v.get<int>("skill3"), v.get<int>("skill4"), v.get<int>("ability")
            };
        }

        static void to_base(const Monster& m, values& v, indicator& ind)
        {
            v.set("id", m.id); 
            v.set("name", m.name); 
            v.set("level", m.level); 
            v.set("exp", m.exp);
            v.set("type", m.type); 
            v.set("bs_hp", m.bs_hp); 
            v.set("bs_atk", m.bs_atk); 
            v.set("bs_def", m.bs_def); 
            v.set("bs_satk", m.bs_satk); 
            v.set("bs_sdef", m.bs_sdef); 
            v.set("bs_spd", m.bs_spd); 
            v.set("ev_hp", m.ev_hp);
            v.set("ev_atk", m.ev_atk); 
            v.set("ev_def", m.ev_def); 
            v.set("ev_satk", m.ev_satk); 
            v.set("ev_sdef", m.ev_sdef); 
            v.set("ev_spd", m.ev_spd); 
            v.set("atk_lv", m.atk_lv); 
            v.set("def_lv", m.def_lv); 
            v.set("satk_lv", m.satk_lv); 
            v.set("sdef_lv", m.sdef_lv); 
            v.set("spd_lv", m.spd_lv); 
            v.set("acc_lv", m.acc_lv); 
            v.set("crit_lv", m.crit_lv); 
            v.set("skill1", m.skill1); 
            v.set("skill2", m.skill2); 
            v.set("skill3", m.skill3); 
            v.set("skill4", m.skill4); 
            v.set("ability", m.ability); 
            ind = i_ok;   
        }
    };
}       /**< namespace soci */
