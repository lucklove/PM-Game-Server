#pragma once
#include <memory>

class Monster
{
private:
    int id_;

public:
    Monster(int id) : id_{id} {}
    
    int id() { return id_; } 
};

struct MonsterFactory
{
    static std::unique_ptr<Monster> take(int id)
    {
        return nullptr;
    }
};
