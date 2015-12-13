#pragma once
#include "debuff/Debuff.hh"
#include <memory>

struct DebuffDB
{
private:
    template <size_t... Is>
    static std::array<std::unique_ptr<Debuff>, sizeof...(Is)> gen_array(std::index_sequence<Is...>)
    {
        return {std::make_unique<ConcretDebuff<Is + 1>>()...};
    }

public:
    static const Debuff *get(int id)
    {
        static std::array<std::unique_ptr<Debuff>, 6> local_db = gen_array(std::make_index_sequence<6>()); 
        if(id < 1 || id > 6)
            throw std::logic_error{"debuff not exist"};
        return local_db[id].get();
    }
};
