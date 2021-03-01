#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_set.h"
#include "cpn_builtin_functions.h"

namespace cpn
{

template<set_type Im, set_type Dom>
struct function_addition
{
	PUBLISH_OPERATION_PROPERTIES(function_addition,add_operation,commutative,associative,distributive);

	static constexpr integer_set identity = integer_set(0);

	friend inline function_set<Im,Dom> operator+(const function_set<Im,Dom>& i_lhs,const function_set<Im,Dom>& i_rhs)
	{
		return ddk::detail::add_binary_functor(i_lhs,i_rhs)
	}
};

template<set_type Im,set_type Dom>
using function_semi_group = semi_group<function_set<Im,Dom>,function_addition<Im,Dom>>;

template<set_type Im,set_type Dom>
struct function_addition_inverse
{
	PUBLISH_OPERATION_PROPERTIES(function_addition_inverse,add_inverse_operation);

	friend inline function_set<Im,Dom> operator-(const function_set<Im,Dom>& i_rhs)
	{
		return ddk::detail::neg_binary_functor(i_rhs)
	}
};

template<set_type Im,set_type Dom>
using function_group = function_semi_group<Im,Dom>::template equip_with<function_addition_inverse<Im,Dom>>;

}