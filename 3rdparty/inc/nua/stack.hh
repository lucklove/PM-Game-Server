#pragma once
#include <lua.hpp>
#include <iostream>
#include "primitives.hh"
#include "MetatableRegistry.hh"
#include "types.hh"
#include "ScopeGuard.hh"

namespace nua
{
namespace stack
{
    class StackGuard
    {
    private:
        ScopeGuard guard_;

    public:
        StackGuard(lua_State* l) :
        guard_{[l, saved_top_index = lua_gettop(l)]
        {
            lua_settop(l, saved_top_index);
        }}
        {}
    };

    template <typename T>
    typename std::enable_if<std::is_copy_constructible<T>::value, void>::type 
    push(lua_State* l, const T& t)
    {
        T* ptr = (T*)lua_newuserdata(l, sizeof(T));
        MetatableRegistry::set_metatable<T>(l);
        new(ptr) T{t};
    }

    template <typename T>
    void push(lua_State* l, std::reference_wrapper<T> t)
    {
        static_assert(!std::is_const<T>::value, "not support const reference, use value instead");
        T** ptr = (T **)lua_newuserdata(l, sizeof(T *));
        MetatableRegistry::set_metatable<std::reference_wrapper<T>>(l);
        *ptr = &t.get();    
    }

    inline void push(lua_State* l, bool v)
    {
        lua_pushboolean(l, v);
    }

    inline void push(lua_State* l, int v)
    {
        lua_pushinteger(l, v);
    }

    inline void push(lua_State* l, lua_Number v)
    {
        lua_pushnumber(l, v);
    }

    inline void push(lua_State* l, const std::string& v)
    {
        lua_pushlstring(l, v.c_str(), v.size());   
    }

    inline void push(lua_State* l, const char* v)
    {
        lua_pushstring(l, v);   
    }

    inline void push(lua_State* l, std::nullptr_t)
    {
        lua_pushnil(l);    
    }

    template <typename T>
    void set(lua_State* l, int index, T&& v)
    {
        push(l, std::forward<T>(v));
        lua_replace(l, index);   
    }

    template <typename T>
    typename std::enable_if<!std::is_rvalue_reference<T>::value, T>::type
    get(lua_State* l, int index)
    {
        using value_t = typename std::decay<T>::type;
        static_assert(!is_primitive<value_t>::value, "not implemented primitive for get");
        if(std::is_lvalue_reference<T>::value && !check::is_type<std::reference_wrapper<value_t>>(l, index))
        {
            std::cout << "can not get reference of type " << typeid(value_t).name() << ", type mismatch" << std::endl;
            throw std::bad_cast{};
        }

        if(check::is_type<value_t>(l, index))
        {
            value_t* ptr = (value_t*)lua_touserdata(l, index);
            if(ptr == nullptr) throw std::runtime_error{"get userdata failed"};
            return *ptr;   
        }
        else if(check::is_type<std::reference_wrapper<value_t>>(l, index))
        {
            value_t** ptr = (value_t**)lua_touserdata(l, index);
            if(ptr == nullptr) throw std::runtime_error{"get userdata failed"};
            return **ptr;   
        }

        std::cout << "can not get user type " << typeid(value_t).name() << ", type mismatch" << std::endl;
        throw std::bad_cast{};
    }

    template <>
    inline bool get<bool>(lua_State* l, int index)
    {
        if(!lua_isboolean(l, index))
        {
            std::cout << "can not get boolean at index " << index << std::endl;
            throw std::bad_cast{};
        }
        return lua_toboolean(l, index);
    }

    template <>
    inline int get<int>(lua_State* l, int index)
    {
        if(!lua_isinteger(l, index))
        {
            std::cout << "can not get integer at index " << index << std::endl;
            throw std::bad_cast{};
        }

        return lua_tointeger(l, index);
    }

    template <>
    inline lua_Number get<lua_Number>(lua_State* l, int index)
    {
        if(!lua_isnumber(l, index))
        {
            std::cout << "can not get number at index " << index << std::endl;
            throw std::bad_cast{};
        }
        return lua_tonumber(l, index);
    }

    template <>
    inline std::string get<std::string>(lua_State* l, int index)
    {
        if(!lua_isstring(l, index))
        {
            std::cout << "can not get string at index " << index << std::endl;
            throw std::bad_cast{};
        }
        return lua_tostring(l, index);
    }

    template <>
    inline std::nullptr_t get<std::nullptr_t>(lua_State* l, int index)
    {
        if(!lua_isnil(l, index))
        {
            std::cout << "can not get nil at index " << index << std::endl;
            throw std::bad_cast{};
        }

        return nullptr;
    }

    template <typename T>
    T pop(lua_State* l)
    {
        ScopeGuard pop_on_exit([l]
        {
            lua_pop(l, 1);
        });

        return get<T>(l, -1);
    } 
}       /**< stack */
}       /**< nua */
