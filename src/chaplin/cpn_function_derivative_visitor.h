#pragma once

#include "cpn_builtin_functions.h"
#include "ddk_dynamic_visitor.h"
#include "cpn_scalar_function.h"

namespace cpn
{

template<set_type Im, set_type Dom>
struct derivative_visitor : public ddk::dynamic_visitor<ddk::detail::function_impl_base<Im,mpl::terse_function_dominion<Dom>>>
{
	typedef int return_type;

	template<typename T1>
	return_type operator()(const T1& i_lhs)
	{
		auto& kk = i_lhs;
		return 0;
	}
};

}