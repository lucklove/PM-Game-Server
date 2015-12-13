#pragma once
#include "selene/selene.h"
#include "battle/Battle.hh"

struct Lua
{
    static sel::State& context()
    {
        thread_local std::once_flag flag;
        thread_local sel::State ctx{true};
        std::call_once(flag, []
        {
            ctx.Load("src/script/script.lua"); 
        });
        return ctx;
    }
};
