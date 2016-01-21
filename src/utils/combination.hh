#pragma once

template <typename CL, typename CR, typename FuncT>
void combinat(const CL& container_l, const CR& container_r, const FuncT& func)
{
    for(const auto& item_l : container_l)
    {
        for(const auto& item_r : container_r)
            func(item_l, item_r);
    }
}

template <typename TupleLT, typename TupleRT, typename FuncT, size_t... LIs, size_t... RIs>
void combinat_tuple(const TupleLT& tl, const TupleRT& tr, const FuncT& func, std::index_sequence<LIs...>, std::index_sequence<RIs...>)
{
    auto swallow = [](auto&&...){};

    auto expander = [&func, &swallow](auto&& v, auto&&... vs)
    {
        swallow((func(std::forward<decltype(v)>(v), std::forward<decltype(vs)>(vs)), 0)...);  
    };

    swallow((expander(std::get<LIs>(tl), std::get<RIs>(tr)...), 0)...);
}

template <typename... TupleLTs, typename... TupleRTs, typename FuncT>
void combinat(const std::tuple<TupleLTs...>& tl, const std::tuple<TupleRTs...>& tr, const FuncT& func)
{
    combinat_tuple(tl, tr, func, std::make_index_sequence<sizeof...(TupleLTs)>(), std::make_index_sequence<sizeof...(TupleRTs)>()); 
}
