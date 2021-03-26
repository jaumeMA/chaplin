#pragma once

#include "cpn_linear_function.h"
#include "cpn_algebraic_structure.h"

namespace cpn
{

template<typename Function>
struct function_comparison_operation
{
	PUBLISH_OPERATION_PROPERTIES(function_comparison_operation,comp_operation);

	friend inline bool operator==(const Function& i_lhs,const Function& i_rhs)
	{
		//TBD

		return false;
	}
	friend inline bool operator!=(const Function& i_lhs,const Function& i_rhs)
	{
		//TBD

		return true;
	}
};

template<set_type Im,set_type Dom>
using function_set = typename algebraic_structure<function<Im(Dom)>>::template equip_with<function_comparison_operation<function<Im(Dom)>>>;

template<free_module_type Im,free_module_type Dom>
using linear_function_set = typename algebraic_structure<linear_function<Im(Dom)>>::template equip_with<function_comparison_operation<linear_function<Im(Dom)>>>;

}