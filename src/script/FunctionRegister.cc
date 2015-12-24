#include "script/FunctionRegister.hh"
#include "storage/MonsterDB.hh"
#include "storage/SkillDB.hh"
#include "storage/AioiDB.hh"
#include "storage/DebuffDB.hh"

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
            {
                static std::string err_msg;
                err_msg = "try to fetch a " + item_name + "(" + std::to_string(id) + ") which is not exist in database";
                throw std::logic_error{err_msg.c_str()};
            }
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

    void register_debuff_db(nua::Context& ctx)
    {
        ctx["get_debuff"] = [](int id) -> Debuff&
        {
            return *DebuffDB::get(id);
        };
    }
}

void FunctionRegister::register_all(nua::Context& ctx)
{
    register_db<MonsterDB>(ctx, "monster");
    register_db<SkillDB>(ctx, "skill");
    register_aioi_db(ctx);
    register_debuff_db(ctx);
}
