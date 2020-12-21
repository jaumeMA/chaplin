#pragma once

#include "ddkFramework/ddk_tuple.h"
#include "ddkFramework/ddk_high_order_array.h"
#include "ddkFramework/ddk_variant.h"

namespace cpn
{

template<typename ... Sets>
using prod_set = ddk::tuple<Sets...>;

template<typename Set, size_t ... Dims>
using pow_set = ddk::high_order_array<Set,Dims...>;

template<typename ... Sets>
using sum_set = ddk::variant<Sets...>;

}