#pragma once

#include "cpn_linear_function.h"
#include "cpn_algebraic_structure.h"

namespace cpn
{

template<typename Function, set_type Im, set_type Dom>
struct function_comparison_operation
{
	static_assert(IS_CALLABLE_COND(Function,Dom),"You shall provide a callable type as function type.");

	PUBLISH_OPERATION_PROPERTIES(function_comparison_operation,comp_operation);

	friend inline bool operator==(const Function& i_lhs,const Function& i_rhs)
	{
		return i_lhs == i_rhs;
	}
	friend inline bool operator!=(const Function& i_lhs,const Function& i_rhs)
	{
		return i_lhs != i_rhs;
	}
};

template<set_type Im,set_type Dom>
using function_set = typename algebraic_structure<function<Im(Dom)>>::template equip_with<function_comparison_operation<function<Im(Dom)>,Im,Dom>>;

template<free_module_type Im,free_module_type Dom>
using linear_function_set = typename algebraic_structure<linear_function<Im(Dom)>>::template equip_with<function_comparison_operation<linear_function<Im(Dom)>,Im,Dom>>;

}