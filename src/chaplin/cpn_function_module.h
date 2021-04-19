#pragma once

#include "cpn_function_group.h"

namespace cpn
{

template<typename Function, module_type Im, set_type Dom>
struct function_module_operation
{
	static_assert(IS_CALLABLE_COND(Function,Dom), "You shall provide a callable type as function type.");

	PUBLISH_OPERATION_PROPERTIES(function_module_operation,mod_operation,commutative,associative,distributive);

	typedef typename Im::mod_operation::ring_t ring_t;

	friend inline Function operator^(const ring_t& i_lhs,const Function& i_rhs)
	{
		return ddk::detail::builtin_prod_nary_functor(ddk::detail::builtin_number_function<Im,Dom>(i_lhs),i_rhs);
	}
};

template<module_type Im, set_type Dom>
using function_module = typename function_group<Im,Dom>::template equip_with<function_module_operation<function_set<Im,Dom>,Im,Dom>>;

template<module_type Im,set_type Dom>
using linear_function_module = typename linear_function_group<Im,Dom>::template equip_with<function_module_operation<linear_function_set<Im,Dom>,Im,Dom>>;

}