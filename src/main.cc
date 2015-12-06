#include "crow/crow.h"
#include "storage/BattleDB.hh"

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/battle/<int>/<int>")([](int p_pm_id, int s_pm_id)
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
    });

    app.port(8080).multithreaded().run();
}
