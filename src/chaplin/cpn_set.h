#pragma once

#include "cpn_algebraic_structure.h"
#include "ddkFramework/ddk_tuple.h"
#include "ddkFramework/ddk_high_order_array.h"
#include "ddkFramework/ddk_variant.h"

namespace cpn
{

template<set_type ... T>
using prod_set = ddk::tuple<T...>;

template<set_type T, size_t ... Dims>
struct pow_comparison_operation
{
	PUBLISH_OPERATION_PROPERTIES(pow_comparison_operation,comp_operation);

	typedef ddk::high_order_array<T,Dims...> set_t;

	friend inline bool operator==(const set_t& i_lhs,const set_t& i_rhs)
	{
		return i_lhs == i_rhs;
	}
	friend inline bool operator!=(const set_t& i_lhs,const set_t& i_rhs)
	{
		return (i_lhs == i_rhs) == false;
	}
};

template<set_type T, size_t ... Dims>
using pow_set = typename algebraic_structure<ddk::high_order_array<T,Dims...>>::template equip_with<pow_comparison_operation<T,Dims...>>;

template<set_type ... T>
struct sum_comparison_operation
{
	PUBLISH_OPERATION_PROPERTIES(sum_comparison_operation,comp_operation);

	typedef ddk::variant<T...> set_t;

	friend inline bool operator==(const set_t& i_lhs,const set_t& i_rhs)
	{
		return i_lhs == i_rhs;
	}
	friend inline bool operator!=(const set_t& i_lhs,const set_t& i_rhs)
	{
		return (i_lhs == i_rhs) == false;
	}
};

template<set_type ... T>
using sum_set = typename algebraic_structure<ddk::variant<T...>>::template equip_with<sum_comparison_operation<T...>>;

}
