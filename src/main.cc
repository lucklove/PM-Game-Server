#include "crow/crow.h"
#include "storage/BattleDB.hh"

static auto handle_battle_initiate(int p_pm_id, int s_pm_id)
{
    crow::json::wvalue result;
    auto battle_opt = Battle::launch(p_pm_id, s_pm_id);
    if(!battle_opt)
    {
        result["result"] = "false";
        result["error"] = "invalid pm id";
    }
    else
    {
        const Battle& b = *battle_opt;
        result["result"] = "true";
        result["battle_id"] = std::to_string(b.id);
        BattleDB::set(b.id, b);
    }
    return result;
}

static auto handle_attack(const crow::request& req, int battle_id)
{
    auto x = crow::json::load(req.body);
    if(!x) return crow::response(400);

    crow::json::wvalue result;
    auto battle_opt = BattleDB::get(battle_id);
    if(!battle_opt)
    {
        result["result"] = "false";
        result["error"] = "invalid battle id";
    }
    else
    {
                                    
    }

    return crow::response{result};
}

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/battle/<int>/<int>")(handle_battle_initiate);
    CROW_ROUTE(app, "/attack/<int>").methods("POST"_method)(handle_attack);

    app.port(8080).multithreaded().run();
}
