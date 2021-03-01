#pragma once

#include "cpn_function_group.h"

namespace cpn
{

template<ring_type Im, typename Dom>
struct function_module_operation
{
	PUBLISH_OPERATION_PROPERTIES(function_module_operation,mod_operation,commutative,associative,distributive);

	typedef integer_ring ring_t;

	static constexpr ring_t identity = ring_t(ring_t::mult_operation::identity);

	friend inline integer_set operator^(const Im& i_lhs,const Dom& i_rhs)
	{
		return ddk::detail::prod_binary_functor(ddk::detail::builtin_numeric_template_function<Im>(i_lhs),i_rhs);
	}
};

template<ring_type Im, set_type Dom>
using function_module = function_group<Im,Dom>::template equip_with<function_module_operation<Im,Dom>>;

}