#include "crow/crow.h"
#include "script/Lua.hh"
#include "result/Result.hh"
#include "exception/LuaException.hh"
#include "dispatcher/Dispatcher.hh"

static void handle_battle_initiate(const crow::request& req, crow::response& res, int role_id, int enemy_id)
{
    Dispatcher::getInstance().enqueue([req, &res, role_id, enemy_id]
    {
        crow::json::wvalue r;

        try
        {    
            Result result{r};
            (*Lua::context())["handleBattle"](result, role_id, enemy_id);
        }
        catch(LuaException& e)
        {
            r["error"] = e.what();
        }
        catch(std::exception& e)
        {
            res = crow::response(500);
            res.write(e.what());
            res.end();
            return;
        }

        res.write(crow::json::dump(r));
        res.end();
    });
}

static void handle_attack(const crow::request& req, crow::response& res, int battle_id)
{
    Dispatcher::getInstance().enqueue([req, &res, battle_id]
    {
        crow::json::wvalue r;

        try
        {
            auto x = crow::json::load(req.body);
            if(!x)
            {
                res = crow::response(400);
                return;
            }

            Result result{r};
            int skill_id = x["skill"].i();
            (*Lua::context())["handleAttack"](result, battle_id, skill_id);
        }
        catch(LuaException& e)
        {
            r["error"] = e.what();
        }
        catch(std::exception& e)
        {
            res = crow::response(500);
            res.write(e.what());
            res.end();
            return;
        }

        res.write(crow::json::dump(r));
        res.end();
    });
}
int main()
{
    /** 测试lua环境是否正常 */
    Lua::context()->load("src/script/test.lua");

    crow::SimpleApp app;

    CROW_ROUTE(app, "/battle/<int>/<int>")(handle_battle_initiate);
    CROW_ROUTE(app, "/attack/<int>").methods("POST"_method)(handle_attack);
    app.port(8080).multithreaded().run();
}
