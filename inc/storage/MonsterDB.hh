#pragma once
#include "Storage.hh"
#include "battle/Monster.hh"
#include "utils/ScopeGuard.hh"
#include <redox.hpp>
#include <unordered_map>
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

struct MonsterMemoryStorage
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

struct MonsterCacheStorage
{
    static Optional<Monster> get(int id)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return {};
        ScopeGuard on_exit([&]{ rdx.disconnect(); });
        try
        {
            Optional<Monster> m_opt;
            std::string s = rdx.get("monster:" + std::to_string(id));
            Monster m;
            std::stringstream ss{s};
            m.from_stream(ss);
            return m;
        }
        catch(std::runtime_error&)
        {
            return {};
        }
    }

    static void set(int id, const Monster& m)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return;
        ScopeGuard on_exit([&]{ rdx.disconnect(); });

        std::stringstream ss;
        m.to_stream(ss);
        rdx.set("monster:" + std::to_string(id), ss.str());  
    }

    static void del(int id)
    {
        redox::Redox rdx;
        if(!rdx.connect("localhost", 6379))
            return;
        ScopeGuard on_exit([&]{ rdx.disconnect(); });
   
        rdx.del("monster:" + std::to_string(id)); 
    }
};

struct MonsterPersistentStorage
{
    static Optional<Monster> get(int id)
    {
        Monster m = { 0 };
        try
        {
            soci::session sql(soci::mysql, "db=pocket_monster_db user=root pass=lucklove");
            sql << "select * from monster where ID=:ID", soci::into(m), soci::use(id);
        }
        catch(soci::soci_error&) 
        { 
            return {}; 
        }
        if(m.pm_ID != 0)
        { 
            return m;
        }
        else
        {
            return {};
        }
    }

    static void set(int id, const Monster& m)
    {
        /**< nop */
    }

    static void del(int id)
    {
        /**< nop */
    }

    static void delete_persistent(int id)
    {
        soci::session sql(soci::mysql, "db=pocket_monster_db user=root pass=lucklove");
        sql << "delete from monster where id=:ID", soci::use(id);
    }

    static int insert(const Monster& m)
    {
        soci::session sql(soci::mysql, "db=pocket_monster_db user=root pass=lucklove");
        sql << "insert into monster("
                    "name, level, exp, type, bs_hp, bs_atk, bs_def, bs_satk, bs_sdef, bs_spd, "
                    "ev_hp, ev_htk, ev_def, ev_satk, ev_sdef, ev_spd, atk_lv, def_lv, satk_lv, "
                    "sdef_lv, spd_lv, acc_lv, crit_lv, skill1, skill2, skill3, skill4, ability"
                ") values("
                    ":name, :level, :exp, :type, :bs_hp, :bs_atk, :bs_def,:bs_satk, :bs_sdef, :bs_spd, "
                    ":ev_hp, :ev_htk, :ev_def, :ev_satk, :ev_sdef, :ev_spd, :atk_lv, :def_lv, :satk_lv, "
                    ":sdef_lv, :spd_lv, :acc_lv, :crit_lv, :skill1, :skill2, :skill3, :skill4, :ability)", 
                soci::use(m);
        int id = 0;
        sql << "select @@IDENTITY", soci::into(id);
        return id;
    }

    template <typename T>
    static void update(int id, const std::string& filed, T value)
    {
        soci::session sql(soci::mysql, "db=pocket_monster_db user=root pass=lucklove");
        sql << "update monster set " + filed + "=:VALUE where id=:ID", soci::use(value), soci::use(id);
    }
};

using MonsterDB = Storage<MonsterMemoryStorage, MonsterCacheStorage, MonsterPersistentStorage>;
