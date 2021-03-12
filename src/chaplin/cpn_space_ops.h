#pragma once

#include "cpn_algebraic_concepts.h"

namespace cpn
{
namespace detail
{

template<typename T>
T resolve_fundamental_type(const T&);
template<coordinate_type T>
typename T::place_type resolve_fundamental_type(const T&);

}

template<set_type T>
inline constexpr size_t get_rank();

template<free_module_type T>
inline constexpr size_t get_rank();

template<set_type T>
using space_funcdamental_type = decltype(detail::resolve_fundamental_type(std::declval<T>()));

}

#include "cpn_space_ops.inl"