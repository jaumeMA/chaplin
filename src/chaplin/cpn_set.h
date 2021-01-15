#pragma once

#include "ddkFramework/ddk_tuple.h"
#include "ddkFramework/ddk_high_order_array.h"
#include "ddkFramework/ddk_variant.h"

namespace cpn
{

template<typename ... sets>
using prod_set = ddk::tuple<sets...>;

template<typename set, size_t ... dims>
using pow_set = ddk::high_order_array<set,dims...>;

template<typename ... sets>
using sum_set = ddk::variant<sets...>;

}
