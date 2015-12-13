#include "crow/crow.h"
#include "storage/BattleDB.hh"
#include "storage/SkillDB.hh"
#include "storage/LevelDB.hh"
#include "battle/attack.hh"
#include "battle/Round.hh"
#include "storage/DebuffDB.hh"

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
    Monster& role_pm = battle_opt->role_pm;
    Monster& enemy_pm = battle_opt->enemy_pm;
    
    auto role_s_opt = SkillDB::get(x["skill"].i());
    auto enemy_s_opt = enemy_pm.peekSkill();
    if(!role_s_opt || !enemy_s_opt)
    {
        result["result"] = false;
        result["error"] = "selected skill not exist(role or enemy)";
        return crow::response{result};
    }
    Skill& role_skill = *role_s_opt;
    Skill& enemy_skill = *enemy_s_opt;

    auto& role_res = result["role"]; 
    auto& enemy_res = result["enemy"]; 

    Round round;
    if(AttackOrder::is_first(role_pm, enemy_pm, role_skill, enemy_skill))
    {
        result["firstMove"] = "role";
        round.onFirstDebuff(Tick::tick_debuff, role_res, round, role_pm);
        round.onFirstAttack(Attack::do_attack, role_res, enemy_res, role_pm, enemy_pm, role_skill);
        round.onLastDebuff(Tick::tick_debuff, enemy_res, round, enemy_pm);
        round.onLastAttack(Attack::do_attack, enemy_res, role_res, enemy_pm, role_pm, enemy_skill);
    }
    else
    {
        result["firstMove"] = "enemy";
        round.onFirstDebuff(Tick::tick_debuff, enemy_res, round, enemy_pm);
        round.onFirstAttack(Attack::do_attack, enemy_res, role_res, enemy_pm, role_pm, enemy_skill);
        round.onLastDebuff(Tick::tick_debuff, role_res, round, role_pm);
        round.onLastAttack(Attack::do_attack, role_res, enemy_res, role_pm, enemy_pm, role_skill);
    }
    round.apply();

    result["result"] = true;

    if(role_pm.cur_hp > 0 && enemy_pm.cur_hp > 0)
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
