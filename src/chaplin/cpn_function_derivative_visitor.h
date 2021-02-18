#pragma once

#include "cpn_builtin_functions.h"
#include "ddk_dynamic_visitor.h"
#include "cpn_scalar_function.h"

namespace cpn
{

TEMPLATE(typename T)
REQUIRES(IS_CALLABLE(T))
inline function_impl<typename T::return_type(typename T::args_type)> custom_derivative(const T& i_callable, ...);

template<set_type Im, set_type Dom>
struct derivative_visitor : public ddk::dynamic_visitor<ddk::detail::function_impl_base<Im,mpl::terse_function_dominion<Dom>>>
{
	typedef function<Im(Dom)> return_type;

	inline return_type operator()(const ddk::detail::add_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::subs_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::prod_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_number_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_composed_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	//inline return_type operator()(const ddk::detail::div_binary_functor<Im,Dom>& i_function);

	template<typename T>
	inline return_type operator()(const T& i_lhs, ...) const;
};

}

#include "cpn_function_derivative_visitor.inl"