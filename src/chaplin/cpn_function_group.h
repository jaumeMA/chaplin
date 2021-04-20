#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_set.h"
#include "cpn_builtin_functions.h"

namespace cpn
{

template<typename Function, semi_group_type Im, set_type Dom>
struct function_addition
{
	static_assert(IS_CALLABLE_COND(Function,Dom),"You shall provide a callable type as function type.");

	PUBLISH_OPERATION_PROPERTIES(function_addition,add_operation,commutative,associative,distributive);

	friend inline Function operator+(const Function& i_lhs,const Function& i_rhs)
	{
		return static_cast<const typename Function::set_traits&>(i_lhs) + static_cast<const typename Function::set_traits&>(i_rhs);
	}
};

template<semi_group_type Im,set_type Dom>
using function_semi_group = semi_group<function_set<Im,Dom>,function_addition<function_set<Im,Dom>,Im,Dom>>;

template<semi_group_type Im,set_type Dom>
using linear_function_semi_group = semi_group<linear_function_set<Im,Dom>,function_addition<linear_function_set<Im,Dom>,Im,Dom>>;

template<typename Function, semi_group_type Im, set_type Dom>
struct function_addition_inverse
{
	static_assert(IS_CALLABLE_COND(Function,Dom),"You shall provide a callable type as function type.");

	PUBLISH_OPERATION_PROPERTIES(function_addition_inverse,add_inverse_operation);

	friend inline Function operator-(const Function& i_rhs)
	{
		return -i_rhs;
	}
	friend inline Function operator-(const Function& i_lhs, const Function& i_rhs)
	{
		return i_lhs + (-i_rhs);
	}
};

template<group_type Im,set_type Dom>
using function_group = typename function_semi_group<Im,Dom>::template equip_with<function_addition_inverse<function_set<Im,Dom>,Im,Dom>>;

template<group_type Im,set_type Dom>
using linear_function_group = typename linear_function_semi_group<Im,Dom>::template equip_with<function_addition_inverse<linear_function_set<Im,Dom>,Im,Dom>>;

}