#pragma once
#include <memory>
#include <string>

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
};
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
