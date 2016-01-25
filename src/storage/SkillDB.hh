#pragma once
#include "Storage.hh"
#include "storage_factory.hh"
#include "DBAccess.hh"
#include "battle/Skill.hh"

struct SkillMemoryStorage
{
    static Optional<Skill> get(int id)
    {
        return MemoryStorage<Skill>::get(id);
    }

    static void set(int id, const Skill& s)
    {
        MemoryStorage<Skill>::set(id, s);
    }

    static void del(int id)
    {
        MemoryStorage<Skill>::del(id);
    } 
};

struct SkillCacheStorage
{
    static Optional<Skill> get(int id)
    {
        return CacheStorage<Skill>::get("skill", id);
    }

    static void set(int id, const Skill& s)
    {
        CacheStorage<Skill>::set("skill", id, s);
    }

    static void del(int id)
    {
        return CacheStorage<Skill>::del("skill", id);
    }
};

struct SkillPersistentStorage
{
    static Optional<Skill> get(int id)
    {
        Skill s = { 0 };

        DBAccess::mysql_query([&s, id](soci::session& session)
        {
            session << "select * from skill where id=:ID", soci::into(s), soci::use(id);
        });

        if(s.id != 0)
        { 
            return s;
        }
        else
        {
            return {};
        }
    }

    static void set(int id, const Skill& m)
    {
        /**< nop */
    }

    static void del(int id)
    {
        /**< nop */
    }
};

using SkillDB = Storage<SkillMemoryStorage, SkillCacheStorage, SkillPersistentStorage>;
