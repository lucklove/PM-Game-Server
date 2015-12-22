#pragma once
#include <atomic>
#include "nua/nua.hh"
#include "ClassRegister.hh"
#include "FunctionRegister.hh"

struct Lua
{
    static nua::Context& context()
    {
        /** 之所以不用std::once_flag是因为可能抛出异常 */
        thread_local std::atomic_flag once_flag = ATOMIC_FLAG_INIT;
        thread_local nua::Context ctx{true};
        if(!once_flag.test_and_set())
        {
            ClassRegister::register_all(ctx);   
            FunctionRegister::register_all(ctx);   
            ctx.load("src/script/script.lua"); 
        }
        return ctx;
    }
};
