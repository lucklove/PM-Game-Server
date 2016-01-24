#pragma once
#include <memory>
#include "nua/nua.hh"
#include "ClassRegister.hh"
#include "FunctionRegister.hh"
#include "utils/LockFreeStack.hh"
#include "dispatcher/Dispatcher.hh"

struct Lua
{
    struct LuaImpl
    {
    private:
        LockFreeStack<nua::Context*> ctx_ptrs_;

        struct ContextDeleter
        { 
        private:
            LockFreeStack<nua::Context*>& pool_;
    
        public:
            ContextDeleter(LockFreeStack<nua::Context*>& pool) : pool_{pool} {}
 
            void operator()(nua::Context* ctx_ptr)
            {
                pool_.push(ctx_ptr);
            }    
        };  

    public:
        LuaImpl(size_t size)
        {
            for(size_t i = 0; i < size; ++i)
            {
                nua::Context* ctx_ptr = new nua::Context;

                ClassRegister::register_all(*ctx_ptr);   
                FunctionRegister::register_all(*ctx_ptr);   
                ctx_ptr->load("src/script/script.lua"); 
                ctx_ptr->load("src/script/battle.lua"); 
                ctx_ptr->load("src/script/attack.lua"); 
                ctx_ptr->load("src/script/debuff.lua"); 
                ctx_ptr->load("src/script/ability.lua");

                ctx_ptrs_.push(ctx_ptr);
            }
        }

        std::unique_ptr<nua::Context, ContextDeleter> getContext()
        {
            Optional<nua::Context*> ctx_ptr_opt;
            while(!(ctx_ptr_opt = ctx_ptrs_.pop()))
                Dispatcher::getInstance().yield();
            return std::unique_ptr<nua::Context, ContextDeleter>(*ctx_ptr_opt, ContextDeleter{ctx_ptrs_});
        }
    };

    static auto context()
    {
        static LuaImpl lua_ctx_pool{std::thread::hardware_concurrency()};
        return lua_ctx_pool.getContext();
    }
};
