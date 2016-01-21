#pragma once
#include "utils/Optional.hh"
#include "utils/function_traits.hh"

template <typename OptionalT, size_t = 0>
struct NopStorage
{
    template <typename... Args>
    static OptionalT get(Args&&...)
    {
        return {};
    }

    template <typename... Args>
    static void set(Args&&...)
    {
    }

    template <typename... Args>
    static void del(Args&&...)
    {
    }
};

template <typename Primary, 
    typename Secondary = NopStorage<typename function_traits<decltype(Primary::get)>::return_type, 1>,
    typename Tertiary = NopStorage<typename function_traits<decltype(Primary::get)>::return_type, 2>
>
struct Storage : Primary, Secondary, Tertiary
{
    using primary_storage = Primary;
    using secondary_storage = Secondary;
    using tertiary_storage = Tertiary;

    template <typename... Args>
    static auto get(Args&&... args)
    {
        /** 查找一级缓存 */
        auto res = Primary::get(std::forward<Args>(args)...);
        if(res) 
            return res;

        /** 查找二级缓存 */
        res = Secondary::get(std::forward<Args>(args)...);
        if(res)
        {
            /** 写一级缓存 */
            Primary::set(std::forward<Args>(args)..., *res);
            return res;
        }

        /** 查找三级缓存 */
        res = Tertiary::get(std::forward<Args>(args)...);
        if(res)
        {
            /** 写二级缓存 */
            Secondary::set(std::forward<Args>(args)..., *res);
            /** 写一级缓存 */
            Primary::set(std::forward<Args>(args)..., *res);
            return res;
        }
        return res;
    }

    template <typename... Args>
    static void set(Args&&... args)
    {
        Tertiary::set(std::forward<Args>(args)...);
        Secondary::set(std::forward<Args>(args)...);
        Primary::set(std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void del(Args&&... args)
    {
        Tertiary::del(std::forward<Args>(args)...);
        Secondary::del(std::forward<Args>(args)...);
        Primary::del(std::forward<Args>(args)...);
    }
};
