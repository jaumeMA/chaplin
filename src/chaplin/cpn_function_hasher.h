#pragma once

#include "ddk_dynamic_visitor.h"
#include "ddk_function_impl.h"

namespace cpn
{

template<typename Im, typename ... Dom>
class function_hasher : public ddk::dynamic_visitor<ddk::detail::function_base<Im,Dom...>>
{
public:
	using typename ddk::dynamic_visitor<ddk::detail::function_base<Im,Dom...>>::type_interface;
	typedef size_t return_type;

	function_hasher() = default;

	inline size_t operator()(const ddk::detail::builtin_number_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const;
	inline size_t operator()(const ddk::detail::builtin_component_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const;
	inline size_t operator()(const ddk::detail::builtin_composed_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const;
	inline size_t operator()(const ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function) const;
	inline size_t operator()(const ddk::detail::builtin_prod_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function) const;
	inline size_t operator()(const ddk::detail::builtin_inverted_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const;
};

}

#include "cpn_function_hasher.inl"