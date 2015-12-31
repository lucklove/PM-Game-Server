#include "script/FunctionRegister.hh"
#include "storage/MonsterDB.hh"
#include "storage/SkillDB.hh"
#include "storage/AioiDB.hh"
#include "storage/BattleDB.hh"
#include "exception/LuaException.hh"

namespace
{
    template <typename DB>
    void register_db(nua::Context& ctx, const std::string& item_name)
    {
        std::string func_name = "get_" + item_name;
        ctx[func_name.c_str()] = [&item_name](int id)
        {
            auto opt = DB::get(id);
            if(!opt)
                throw StorageException{item_name + "(" + std::to_string(id) + ") not exist in database"};
            return *opt;
        };
    }

    void register_aioi_db(nua::Context& ctx)
    {
        ctx["get_aioi"] = [](int ta, int tb) -> double
        {
            return AioiDB::get(ta, tb);
        };
    }

    void register_battle_db(nua::Context& ctx)
    {
        ctx["get_battle"] = [](int id) -> Battle
        {
            auto b = BattleDB::get(id);
            if(!b)
                throw StorageException{"battle(" + std::to_string(id) + ") not exist in database"};
            return *b;
        };

        ctx["set_battle"] = [](int id, Battle b)
        {
            BattleDB::set(id, b);
        };

        ctx["del_battle"] = [](int id)
        {
            BattleDB::del(id);
        };

        ctx["launch_battle"] = &Battle::launch;
    }

    void register_throw(nua::Context& ctx)
    {
        ctx["throw"] = [](std::string exception_name, std::string what)
        {
            if(exception_name == "lua")
            {
                throw LuaException(what);
            }
            else
            {
                throw UnknownLuaException(what);                
            }
        };
    }
}

void FunctionRegister::register_all(nua::Context& ctx)
{
    register_throw(ctx);
    register_db<MonsterDB>(ctx, "monster");
    register_db<SkillDB>(ctx, "skill");
    register_aioi_db(ctx);
    register_battle_db(ctx);
}
