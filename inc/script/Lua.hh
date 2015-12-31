#pragma once
#include <atomic>
#include "nua/nua.hh"
#include "ClassRegister.hh"
#include "FunctionRegister.hh"

struct Lua
{
    struct LuaImpl
    {
    private:
        nua::Context ctx_;        

    public:
        LuaImpl()
        {
            ClassRegister::register_all(ctx_);   
            FunctionRegister::register_all(ctx_);   
            ctx_.load("src/script/script.lua"); 
            ctx_.load("src/script/battle.lua"); 
            ctx_.load("src/script/attack.lua"); 
            ctx_.load("src/script/debuff.lua"); 
        }

        nua::Context& getContext()
        {
            return ctx_;
        }
    };

    static nua::Context& context()
    {
        thread_local LuaImpl lua_ctx;
        return lua_ctx.getContext();
    }
};
