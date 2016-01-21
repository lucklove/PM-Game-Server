#pragma once
#include "crow/json.h"

class Result
{
private:
    crow::json::wvalue& result_;
    
public:
    Result(crow::json::wvalue& result) : result_{result} {}
    
    Result get(std::string filed)
    {
        return Result{result_[filed]};   
    }

    template <typename T>
    void set(std::string f, T v)
    {
        result_[f] = v;
    }
};
