#pragma once

#include "cpn_algebraic_concepts.h"
#include "ddk_high_order_array.h"
#include "cpn_space_ops.h"

namespace cpn
{

template<function_type Func>
inline ddk::high_order_array<Func,get_rank<typename Func::im_t>(),get_rank<typename Func::dom_t>()> derivative(const Func& i_func);

}

#include "cpn_function_ops.inl"