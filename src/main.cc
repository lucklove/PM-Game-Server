#include "crow/crow.h"
#include "storage/BattleDB.hh"
#include "storage/SkillDB.hh"
#include "storage/LevelDB.hh"
#include "battle/Attack.hh"

static auto handle_battle_initiate(int p_pm_id, int s_pm_id)
{
    crow::json::wvalue result;
    auto battle_opt = Battle::launch(p_pm_id, s_pm_id);
    if(!battle_opt)
    {
        result["result"] = false;
        result["error"] = "invalid pm id";
    }
    else
    {
        const Battle& b = *battle_opt;
        result["result"] = true;
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
        result["result"] = false;
        result["error"] = "invalid battle id";
        return crow::response{result};;
    }
    auto s_opt = SkillDB::get(x["skill"].i());
    if(!s_opt)
    {
        result["result"] = false;
        result["error"] = "no such skill";
        return crow::response{result};
    }
    auto& player = result["player"]; 
    auto& server = result["server"]; 

    auto do_attack = [](auto& res, Monster& m_a, Monster& m_b, Skill& s)
    {
        res["hit"] = true;
        int crit = Attack::crit_multi(m_a);
        res["crit"] = crit;
        float dmg = Attack::attack(m_a, m_b, s, crit);
        res["hurt"] = dmg;
        m_b.cur_hp -= dmg;
        res["hp"] = m_b.cur_hp;
    };

    if(Attack::is_first(battle_opt->player_pm, battle_opt->server_pm))
    {
        player["first"] = true;
        server["first"] = false;

        if(Attack::is_hit(battle_opt->player_pm, *s_opt))
        {
            do_attack(server, battle_opt->player_pm, battle_opt->server_pm, *s_opt);
        }
        else
        {
            server["hit"] = false;
        }

        if(Attack::is_hit(battle_opt->server_pm, *s_opt))
        {
            do_attack(player, battle_opt->server_pm, battle_opt->player_pm, *s_opt);
        }
        else
        {
            player["hit"] = false;
        }
    }
    else
    {
        player["first"] = false;
        server["first"] = true;

        if(Attack::is_hit(battle_opt->server_pm, *s_opt))
        {
            do_attack(player, battle_opt->server_pm, battle_opt->player_pm, *s_opt);
        }
        else
        {
            player["hit"] = false;
        }

        if(Attack::is_hit(battle_opt->player_pm, *s_opt))
        {
            do_attack(server, battle_opt->player_pm, battle_opt->server_pm, *s_opt);
        }
        else
        {
            server["hit"] = false;
        }
    }
    result["result"] = true;

    if(battle_opt->player_pm.cur_hp > 0 && battle_opt->server_pm.cur_hp > 0)
    {
        BattleDB::set(battle_opt->id, *battle_opt);
    }
    else
    {
        BattleDB::del(battle_opt->id);
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
