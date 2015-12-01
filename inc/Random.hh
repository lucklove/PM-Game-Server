#pragma once
#include <random>
#include <type_traits>

struct Random
{
    static std::default_random_engine& random_engine()
    {
        std::random_device rd;
        static std::default_random_engine eg{rd()};
        return eg;
    }

    template <typename IntegerT, typename = typename std::enable_if<std::is_integral<IntegerT>::value>::type, typename = void>
    static IntegerT get(IntegerT begin, IntegerT end)
    {
        std::uniform_int_distribution<IntegerT> dis{begin, end};
        return dis(random_engine());
    }

    template <typename FloatingT, typename = typename std::enable_if<std::is_floating_point<FloatingT>::value>::type>
    static FloatingT get(FloatingT begin, FloatingT end)
    {
        std::uniform_real_distribution<FloatingT> dis{begin, end};
        return dis(random_engine());
    }
};
