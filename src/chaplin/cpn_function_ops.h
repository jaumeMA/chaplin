#pragma once

#include "cpn_algebraic_concepts.h"
#include "ddk_high_order_array.h"
#include "cpn_space_ops.h"

namespace cpn
{

template<function_type Func>
inline auto derivative(const Func& i_func);

}

#include "cpn_function_ops.inl"