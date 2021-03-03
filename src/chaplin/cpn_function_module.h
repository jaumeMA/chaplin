#pragma once

#include "cpn_function_group.h"

namespace cpn
{

template<module_type Im,set_type Dom>
struct function_module_operation
{
	PUBLISH_OPERATION_PROPERTIES(function_module_operation,mod_operation,commutative,associative,distributive);

	typedef typename Im::mod_operation::ring_t ring_t;

	friend inline function_set<Im,Dom> operator^(const ring_t& i_lhs,const function_set<Im,Dom>& i_rhs)
	{
		return ddk::detail::prod_binary_functor(ddk::detail::builtin_numeric_template_function<Im>(i_lhs),i_rhs);
	}
};

template<module_type Im, set_type Dom>
using function_module = typename function_group<Im,Dom>::template equip_with<function_module_operation<Im,Dom>>;

}