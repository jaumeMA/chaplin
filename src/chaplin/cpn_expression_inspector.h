#pragma once

#include "cpn_builtin_functions.h"

namespace cpn
{

template<typename>
struct linearity_inspector
{
    static const bool value = false;
};

template<typename Lhs, typename Rhs>
struct linearity_inspector<ddk::detail::add_binary_functor<Lhs,Rhs>>
{
    static const bool value = linearity_inspector<Lhs>::value && linearity_inspector<Rhs>::value;
};
template<typename Lhs, typename Rhs>
struct linearity_inspector<ddk::detail::prod_binary_functor<Lhs,Rhs>>
{
    static const bool value = linearity_inspector<Lhs>::value && linearity_inspector<Rhs>::value;
};
template<size_t T>
struct linearity_inspector<builtin_numeric_template_function<T>>
{
    static const bool value = true;
};

}
