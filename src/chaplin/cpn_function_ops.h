#pragma once

#include "cpn_algebraic_concepts.h"
#include "ddk_high_order_array.h"

namespace cpn
{

template<function_type Func>
ddk::high_order_array<Func,Func::Im::rank,Func::Dom::rank> derivative(Func&& i_func);

TEMPLATE(function_type Func, typename ... T)
REQUIRES(IS_COORDINATE(T)...)
ddk::high_order_array<Func,Func::Im::rank,ddk::mpl::num_types<T...>> derivative(Func&& i_func, const T& ... i_coordinates);

}