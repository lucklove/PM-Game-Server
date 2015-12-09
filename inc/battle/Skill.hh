#pragma once
#include <string>
#include <soci/soci.h>
#include "cereal/archives/json.hpp"

struct Skill
{
    int id;              
    std::string name;       /**< 技能名 */
    int type;               /**< 技能类型 */
    int skill_class;        /**< 技能分类 */
    int power;              /**< 技能威力 */
    int acc;                /**< 技能命中 */
    int is_melee;           /**< 近战远程 */
    int damage_hurt;        /**< 技能反伤值 */
    int weather_eff;        /**< 技能追加的天气 */
    int rate_attr;          /**< 技能追加能力概率 */
    int attr;               /**< 技能追加能力属性 */
    int lvl_attr;           /**< 技能追加能力等级 */
    int role_attr;          /**< 能力变化对象 */
    int rate_debuff;        /**< 技能追加异常概率 */
    int debuff;             /**< 技能追加异常类型 */
    int role_debuff;        /**< 异常对象 */
    int round;              /**< 异常回合数 */
    int last_order;         /**< 技能后攻 */

    template <typename Archive>
    void serialize(Archive & ar)
    {
        ar(
            id, name, type, skill_class, power, acc, is_melee, damage_hurt, weather_eff, rate_attr, 
            attr, lvl_attr, role_attr, rate_debuff, debuff, role_debuff, round, last_order
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
    struct type_conversion<Skill>
    {
        typedef values base_type;

        static void from_base(const values& v, indicator /* ind */, Skill& s)
        {
            s = { 
                v.get<int>("id"), v.get<std::string>("name"), v.get<int>("type"), v.get<int>("class"), 
                v.get<int>("power"), v.get<int>("acc"), v.get<int>("is_melee"), v.get<int>("damage_hurt"), 
                v.get<int>("weather_eff"), v.get<int>("rate_attr"), v.get<int>("attr"), v.get<int>("lvl_attr"), 
                v.get<int>("role_attr"), v.get<int>("rate_debuff"), v.get<int>("debuff"), v.get<int>("role_debuff"),
                v.get<int>("round"), v.get<int>("last_order") 
            };
        }
    };
}       /**< namespace soci */
