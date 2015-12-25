#include "crow/crow.h"
#include "script/Lua.hh"
#include "result/Result.hh"
#include "exception/StorageException.hh"

static auto handle_battle_initiate(int role_id, int enemy_id)
{
    crow::json::wvalue res;

    try
    {    
        Result result{res};
        Lua::context()["handleBattle"](result, role_id, enemy_id);
    }
    catch(StorageException& e)
    {
        res["error"] = e.what();
    }

    return res;
}

static auto handle_attack(const crow::request& req, int battle_id)
{
    auto x = crow::json::load(req.body);
    if(!x) return crow::response(400);
    crow::json::wvalue res;

    try
    {
        Result result{res};
        int skill_id = x["skill"].i();
        Lua::context()["handleAttack"](result, battle_id, skill_id);
    }
    catch(StorageException& e)
    {
        res["error"] = e.what();
    }

    return crow::response{res};
}

int main()
{
    /** 测试lua环境是否正常 */
    Lua::context().load("src/script/test.lua");

    crow::SimpleApp app;

    CROW_ROUTE(app, "/battle/<int>/<int>")(handle_battle_initiate);
    CROW_ROUTE(app, "/attack/<int>").methods("POST"_method)(handle_attack);
    app.port(8080).multithreaded().run();
}
