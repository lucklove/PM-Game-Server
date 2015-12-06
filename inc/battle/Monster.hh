#pragma once
#include <memory>
#include <string>
#include <soci/soci.h>
#include "cereal/archives/json.hpp"

struct Monster
{
    int pm_ID;              /**< 精灵ID */
    std::string pm_Name;    /**< 精灵名称 */
    int pm_Level;           /**< 精灵等级 */
    int pm_Exp;             /**< 精灵经验 */
    int pm_Type;            /**< 精灵属性 */

    /** 区分不同PM的数值，主要读取配表数值 */
    int pm_BS_Hp;           /**< 生命种族值 */
    int pm_BS_Atk;          /**< 攻击种族值 */
    int pm_BS_Def;          /**< 防御种族值 */
    int pm_BS_Satk;         /**< 特攻种族值 */
    int pm_BS_Sdef;         /**< 特防种族值 */
    int pm_BS_Spd;          /**< 速度种族值 */

    /** 玩家可控的属性成长点，吃药提升每项最高255，所有努力值之和不超过510 */
    int pm_EV_Hp;           /**< 生命努力值 */
    int pm_EV_Atk;          /**< 攻击努力值 */
    int pm_EV_Def;          /**< 防御努力值 */
    int pm_EV_Satk;         /**< 特攻努力值 */
    int pm_EV_Sdef;         /**< 特防努力值 */
    int pm_EV_Spd;          /**< 速度努力值 */

    /** 战斗中影响属性变化的数据 */
    int pm_AtkLv;           /**< 攻击等级 */
    int pm_DefLv;           /**< 防御等级 */
    int pm_SatkLv;          /**< 特攻等级 */
    int pm_SdefLv;          /**< 特防等级 */
    int pm_SpdLv;           /**< 速度等级 */
    int pm_AccLv;           /**< 命中等级 */
    int pm_CritLv;          /**< 暴击等级 */

    /** 临时类属性，由技术评估 */
    int pm_CritRate;        /**< 暴击率 */
    int pm_CritMulti;       /**< 暴击倍数 */
    int pm_CurHp;           /**< 当前生命 */
    int pm_CurAtk;          /**< 最终攻击力 */
    int pm_CurDef;          /**< 最终防御 */
    int pm_CurSatk;         /**< 最终特攻 */
    int pm_CurSdef;         /**< 最终特防 */
    int pm_CurSpd;          /**< 最终速度 */
   
    int pm_Skill1; 
    int pm_Skill2; 
    int pm_Skill3; 
    int pm_Skill4; 

    int pm_Ability;         /**< 特性ID，影响计算参数 */
    
    template <typename Archive>
    void serialize(Archive & ar)
    {
        ar(
            pm_ID, pm_Name, pm_Level, pm_Exp, pm_Type, pm_BS_Hp, pm_BS_Atk, pm_BS_Def, pm_BS_Satk, pm_BS_Sdef, pm_BS_Spd,
            pm_EV_Hp, pm_EV_Atk, pm_EV_Def, pm_EV_Satk, pm_EV_Sdef, pm_EV_Spd, pm_AtkLv, pm_DefLv, pm_SatkLv, pm_SdefLv,
            pm_SpdLv, pm_AccLv, pm_CritLv, pm_CritRate, pm_CritMulti, pm_CurHp, pm_CurAtk, pm_CurDef, pm_CurSatk, 
            pm_CurSdef, pm_CurSpd, pm_Skill1, pm_Skill2, pm_Skill3, pm_Skill4, pm_Ability
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
                v.get<int>("ev_htk"), v.get<int>("ev_def"), v.get<int>("ev_satk"), v.get<int>("ev_sdef"),
                v.get<int>("ev_spd"), v.get<int>("atk_lv"), v.get<int>("def_lv"), v.get<int>("satk_lv"), 
                v.get<int>("sdef_lv"), v.get<int>("spd_lv"), v.get<int>("acc_lv"), v.get<int>("crit_lv"), 
                v.get<int>("skill1"), v.get<int>("skill2"), v.get<int>("skill3"), v.get<int>("skill4"), v.get<int>("ability")
            };
        }

        static void to_base(const Monster& m, values& v, indicator& ind)
        {
            v.set("id", m.pm_ID); 
            v.set("name", m.pm_Name); 
            v.set("level", m.pm_Level); 
            v.set("exp", m.pm_Exp);
            v.set("type", m.pm_Type); 
            v.set("bs_hp", m.pm_BS_Hp); 
            v.set("bs_atk", m.pm_BS_Atk); 
            v.set("bs_def", m.pm_BS_Def); 
            v.set("bs_satk", m.pm_BS_Satk); 
            v.set("bs_sdef", m.pm_BS_Sdef); 
            v.set("bs_spd", m.pm_BS_Spd); 
            v.set("ev_hp", m.pm_EV_Hp);
            v.set("ev_htk", m.pm_EV_Atk); 
            v.set("ev_def", m.pm_EV_Def); 
            v.set("ev_satk", m.pm_EV_Satk); 
            v.set("ev_sdef", m.pm_EV_Sdef); 
            v.set("ev_spd", m.pm_EV_Spd); 
            v.set("atk_lv", m.pm_AtkLv); 
            v.set("def_lv", m.pm_DefLv); 
            v.set("satk_lv", m.pm_SatkLv); 
            v.set("sdef_lv", m.pm_SdefLv); 
            v.set("spd_lv", m.pm_SpdLv); 
            v.set("acc_lv", m.pm_AccLv); 
            v.set("crit_lv", m.pm_CritLv); 
            v.set("skill1", m.pm_Skill1); 
            v.set("skill2", m.pm_Skill2); 
            v.set("skill3", m.pm_Skill3); 
            v.set("skill4", m.pm_Skill4); 
            v.set("ability", m.pm_Ability); 
            ind = i_ok;   
        }
    };
}       /**< namespace soci */
/*
    float attack(const Monster& enemy, int skill_Power, int mod_SkillPower, 
        int skillType, int isPhysicalSkill, int isCrit, int critMulti)
    {
        return (
            (property_.pm_Level * 0.4 + 2) * skill_Power * mod_SkillPower 
            * (property_.pm_CurAtk * isPhysicalSkill + property_.pm_CurSatk * (1 - isPhysicalSkill))
            / (enemy.property_.pm_CurDef * isPhysicalSkill + enemy.property_.pm_CurSdef * (1 - isPhysicalSkill))
            / 50 + 2
        ) * Random::get(217, 255) / 255 * (1 + isCrit * critMulti);
    }

    float damage(float hurt)
    {
        property_.pm_CurHp -= hurt;
        return property_.pm_CurHp;       
    }
*/
