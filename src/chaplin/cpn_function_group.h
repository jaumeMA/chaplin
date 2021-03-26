#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_set.h"
#include "cpn_builtin_functions.h"

namespace cpn
{

template<semi_group_type Im, set_type Dom>
struct function_addition
{
	PUBLISH_OPERATION_PROPERTIES(function_addition,add_operation,commutative,associative,distributive);

	friend inline function<Im(Dom)> operator+(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs)
	{
		return { ddk::detail::add_binary_functor(i_lhs,i_rhs) };
	}
};

template<semi_group_type Im,set_type Dom>
using function_semi_group = semi_group<function_set<Im,Dom>,function_addition<Im,Dom>>;

template<group_type Im,set_type Dom>
struct function_addition_inverse
{
	PUBLISH_OPERATION_PROPERTIES(function_addition_inverse,add_inverse_operation);

	friend inline function<Im(Dom)> operator-(const function<Im(Dom)>& i_rhs)
	{
		return { ddk::detail::neg_unary_functor(i_rhs) };
	}
	friend inline function<Im(Dom)> operator-(const function<Im(Dom)>& i_lhs, const function<Im(Dom)>& i_rhs)
	{
		return { ddk::detail::subs_binary_functor(i_lhs,i_rhs) };
	}
};

template<group_type Im,set_type Dom>
using function_group = typename function_semi_group<Im,Dom>::template equip_with<function_addition_inverse<Im,Dom>>;

}