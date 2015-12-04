#pragma once
#include "common/Monster.hh"

class Battle
{
private:
    std::unordered_map<size_t, std::unique_ptr<Monster>> player_pms;
    std::unordered_map<size_t, std::unique_ptr<Monster>> server_pms;

public:
    Battle(std::initializer_list<size_t> ids)
    {
    }

    static void route(crow::SimpleApp& app)
    {
    }
};
