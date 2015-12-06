#pragma once
#include "Storage.hh"
#include "common/Monster.hh"
#include "utils/ScopeGuard.hh"
#include <unordered_map>
#include <redox.hpp>

struct PrimaryMonsterStorage
{
private:
    static std::unordered_map<int, Monster>& static_storage()
    {
        static std::unordered_map<int, Monster> local_db;
        return local_db;
    }

public:
    static Optional<Monster> get(int id)
    {
        auto& db = static_storage();
        auto ptr = db.find(id);
        if(ptr == db.end())
            return {};
        return ptr->second;
    }

    static void set(int id, const Monster& m)
    {
        auto& db = static_storage();
        db.erase(id);
        db.insert({id, m});
    }

    static void del(int id)
    {
        auto& db = static_storage();
        db.erase(id);
    } 
};

struct SecondaryMonsterStorage
{
    static Optional<Monster> get(int id)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return {};
        ScopeGuard on_exit([&]{ rdx.disconnect(); });

        Optional<Monster> m_opt;
        rdx.command<std::vector<std::string>>({"HMGET", "monster:" + std::to_string(id),
            "id", "name", "level", "exp", "type", "bs_hp", "bs_atk", "bs_def", "bs_satk", "bs_sdef",
            "bs_spd", "ev_hp", "ev_atk", "ev_def", "ev_satk", "ev_sdef", "ev_spd", "atk_lv",
            "def_lv", "satk_lv", "sdef_lv", "spd_lv", "acc_lv", "crit_lv", "skill1", "skill2",
            "skill3", "skill4", "ability"}, [&](redox::Command<std::vector<std::string>>& c)
        {
            ScopeGuard on_return([&]{ rdx.stop(); });
            if(!c.ok() || c.reply()[0].size() == 0) 
                return;
            const auto& r = c.reply();
            m_opt = Monster{ 
                id, r[1], atoi(r[2].c_str()), atoi(r[3].c_str()), atoi(r[4].c_str()), atoi(r[5].c_str()), 
                atoi(r[6].c_str()), atoi(r[7].c_str()), atoi(r[8].c_str()), atoi(r[9].c_str()), atoi(r[10].c_str()), 
                atoi(r[11].c_str()), atoi(r[12].c_str()), atoi(r[13].c_str()), atoi(r[14].c_str()), 
                atoi(r[15].c_str()), atoi(r[16].c_str()), atoi(r[17].c_str()), atoi(r[18].c_str()), 
                atoi(r[19].c_str()), atoi(r[20].c_str()), atoi(r[21].c_str()), atoi(r[22].c_str()), 
                atoi(r[23].c_str()), atoi(r[24].c_str()), atoi(r[25].c_str()), atoi(r[26].c_str()), 
                atoi(r[27].c_str()), atoi(r[28].c_str())
            };
        });
        rdx.wait();
        return m_opt;
    }

    static void set(int id, const Monster& m)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return;
        ScopeGuard on_exit([&]{ rdx.disconnect(); });

        rdx.command<std::string>({"HMSET", "monster:" + std::to_string(id),
            "id", std::to_string(id), "name", m.pm_Name, "level", std::to_string(m.pm_Level), "exp", std::to_string(m.pm_Exp), 
            "type", std::to_string(m.pm_Type),"bs_hp", std::to_string(m.pm_BS_Hp), "bs_atk", std::to_string(m.pm_BS_Atk),
            "bs_def", std::to_string(m.pm_BS_Def), "bs_satk", std::to_string(m.pm_BS_Satk), "bs_sdef", 
            std::to_string(m.pm_BS_Sdef), "bs_spd", std::to_string(m.pm_BS_Spd), "ev_hp", std::to_string(m.pm_EV_Hp), 
            "ev_atk", std::to_string(m.pm_EV_Atk), "ev_def", std::to_string(m.pm_EV_Def), "ev_satk", 
            std::to_string(m.pm_EV_Satk), "ev_sdef", std::to_string(m.pm_EV_Sdef), "ev_spd", std::to_string(m.pm_EV_Spd),
            "atk_lv", std::to_string(m.pm_AtkLv), "def_lv", std::to_string(m.pm_DefLv), "satk_lv", 
            std::to_string(m.pm_SatkLv), "sdef_lv", std::to_string(m.pm_SdefLv), "spd_lv", std::to_string(m.pm_SpdLv), 
            "acc_lv", std::to_string(m.pm_AccLv), "crit_lv", std::to_string(m.pm_CritLv), "skill1", 
            std::to_string(m.pm_Skill1), "skill2", std::to_string(m.pm_Skill2), "skill3", std::to_string(m.pm_Skill3),
            "skill4", std::to_string(m.pm_Skill4), "ability", std::to_string(m.pm_Ability)},
            [&](redox::Command<std::string>& c) 
        {
            if(!c.ok())
                std::cout << "set monster " << id << " failed, status: " << c.status() << std::endl;
            rdx.stop();
        });

        rdx.wait();
    }

    static void del(int id)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return;
        ScopeGuard on_exit([&]{ rdx.disconnect(); });
    
        rdx.command<int>({"DEL", "monster:" + std::to_string(id)}, [&](redox::Command<int>&)
        {
            rdx.stop();
        });
           
        rdx.wait();
    }
};

using MonsterDB = Storage<PrimaryMonsterStorage, SecondaryMonsterStorage>;
