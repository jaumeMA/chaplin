#pragma once

#include "cpn_builtin_functions.h"
#include "cpn_scalar_function.h"
#include "ddk_high_order_array.h"

namespace cpn
{
namespace detail
{

template<typename,metric_space_type,metric_space_type,size_t,typename>
struct derivative_visitor_impl;

template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index>
struct derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>
{
    typedef ddk::mpl::type_pack<Dom...> dom_t;
	typedef Function return_type;

	derivative_visitor_impl() = default;
	inline return_type operator()(const ddk::detail::builtin_add_nary_functor<Im,dom_t>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_prod_nary_functor<Im,dom_t>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_component_function<Im,dom_t>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_number_function<Im,dom_t>& i_function) const;
	inline return_type operator()(const ddk::detail::builtin_composed_function<Im,dom_t>& i_function) const;
	//inline return_type operator()(const ddk::detail::div_binary_functor<Im,Dom>& i_function);
	template<typename T>
	inline return_type operator()(const T& i_lhs,...) const;
};

template<typename Function,metric_space_type Im,set_type ... Dom, size_t Index, size_t ... Indexs>
struct derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<Indexs...>>
{
    typedef ddk::mpl::type_pack<Dom...> dom_t;
	typedef ddk::high_order_array<Function,ddk::mpl::num_ranks<Indexs...>> return_type;

	derivative_visitor_impl() = default;
	inline return_type operator()(const ddk::detail::builtin_fusioned_function<Im,dom_t>& i_function) const;
	template<typename T>
	inline return_type operator()(const T& i_lhs, ...) const;
};

}

template<template<typename> typename Function,metric_space_type Im,metric_space_type Dom,size_t Index>
using derivative_visitor = detail::derivative_visitor_impl<Function<space_fundamental_type<Im>(Dom)>,Im,mpl::terse_function_dominion<Dom>,Index,typename ddk::mpl::make_sequence<0,get_rank<Im>()>::type>;

}

#include "cpn_function_derivative_visitor.inl"
