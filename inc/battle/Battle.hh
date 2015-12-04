#pragma once
#include <atomic>
#include "common/Monster.hh"

class Battle
{
private:
    int id_;                    /**< 战场id */
    int round_ = 1;             /**< 回合计数 */
    std::unordered_map<int, std::unique_ptr<Monster>> player_pms_;
    std::unordered_map<int, std::unique_ptr<Monster>> server_pms_;

    static int genUniqueBattleID()
    {
        static std::atomic<int> id_counter_{ 0 };
        return atomic_fetch_add(&id_counter_, 1);
    }

    void add_player_pm(std::unique_ptr<Monster> pm_ptr)
    {
        player_pms_[pm_ptr->id()] = std::move(pm_ptr);
    }
    
    void add_server_pm(std::unique_ptr<Monster> pm_ptr)
    {
        server_pms_[pm_ptr->id()] = std::move(pm_ptr);
    }
public:
    Battle() 
        : id_{genUniqueBattleID()}
    {}

    static std::unique_ptr<Battle> launch(std::vector<int> ids)
    {
        std::unique_ptr<Battle> bat = std::make_unique<Battle>();

        for(size_t i = 0; i < ids.size(); ++i)
        {
            auto ptr = MonsterFactory::take(ids[i]);

            if(ptr == nullptr)
                return nullptr;

            if(i < ids.size() / 2)
            {
                /** 添加玩家的PM */
                bat->add_player_pm(std::move(ptr));
            }
            else
            {
                /** 添加服务器控制的PM */
                bat->add_server_pm(std::move(ptr));
            }
        }
    
        return bat;
    }

    int id()
    {
        return id_;
    }
};
