#pragma once

#include "cpn_builtin_functions.h"
#include "ddk_dynamic_visitor.h"
#include "cpn_scalar_function.h"

namespace cpn
{
namespace detail
{

template<set_type,set_type,size_t,typename>
struct derivative_visitor_impl;
	
template<set_type Im,set_type Dom,size_t Index>
struct derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>: public ddk::dynamic_visitor<ddk::detail::function_impl_base<Im,mpl::terse_function_dominion<Dom>>>
{
	typedef function<Im(Dom)> return_type;

	inline return_type operator()(const ddk::detail::add_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::subs_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::prod_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_number_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_composed_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const;
	TEMPLATE(typename T)
	REQUIRES(IS_BUILTIN_FUNCTION(T))
	inline return_type operator()(const T& i_function) const;
	//inline return_type operator()(const ddk::detail::div_binary_functor<Im,Dom>& i_function);

	template<typename T>
	inline return_type operator()(const T& i_lhs,...) const;
};

template<set_type Im, set_type Dom, size_t Index, size_t ... Indexs>
struct derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<Indexs...>> : public ddk::dynamic_visitor<ddk::detail::function_impl_base<Im,mpl::terse_function_dominion<Dom>>>
{
	typedef ddk::high_order_array<function<space_funcdamental_type<Im>(Dom)>,ddk::mpl::num_ranks<Indexs...>> return_type;

	inline return_type operator()(const ddk::detail::builtin_fusioned_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const;

	template<typename T>
	inline return_type operator()(const T& i_lhs, ...) const;
};

}

template<set_type Im,set_type Dom,size_t Index>
using derivative_visitor = detail::derivative_visitor_impl<Im,Dom,Index,typename ddk::mpl::make_sequence<0,get_rank<Im>()>::type>;

}

#include "cpn_function_derivative_visitor.inl"
