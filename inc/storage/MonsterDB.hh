#pragma once
#include "Storage.hh"
#include "storage_factory.hh"
#include "battle/Monster.hh"
#include <soci/soci.h>
#include <soci/mysql/soci-mysql.h>

struct MonsterMemoryStorage
{
    static Optional<Monster> get(int id)
    {
        return MemoryStorage<Monster>::get(id);
    }

    static void set(int id, const Monster& m)
    {
        MemoryStorage<Monster>::set(id, m);
    }

    static void del(int id)
    {
        MemoryStorage<Monster>::del(id);
    } 
};

struct MonsterCacheStorage
{
    static Optional<Monster> get(int id)
    {
        return CacheStorage<Monster>::get("monster", id);
    }

    static void set(int id, const Monster& m)
    {
        CacheStorage<Monster>::set("monster", id, m);
    }

    static void del(int id)
    {
        return CacheStorage<Monster>::del("monster", id);
    }
};

struct MonsterPersistentStorage
{
    static Optional<Monster> get(int id)
    {
        Monster m = { 0 };

        soci::session sql(soci::mysql, "db=pocket_monster_db user=root pass=lucklove");
        sql << "select * from monster where ID=:ID", soci::into(m), soci::use(id);

        if(m.id != 0)
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
                    "name, level, exp, type1, type2, bs_hp, bs_atk, bs_def, bs_satk, bs_sdef, bs_spd, "
                    "ev_hp, ev_atk, ev_def, ev_satk, ev_sdef, ev_spd, atk_lv, def_lv, satk_lv, "
                    "sdef_lv, spd_lv, acc_lv, crit_lv, skill1, skill2, skill3, skill4, ability"
                ") values("
                    ":name, :level, :exp, :type1, :type2, :bs_hp, :bs_atk, :bs_def,:bs_satk, :bs_sdef, :bs_spd, "
                    ":ev_hp, :ev_atk, :ev_def, :ev_satk, :ev_sdef, :ev_spd, :atk_lv, :def_lv, :satk_lv, "
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
