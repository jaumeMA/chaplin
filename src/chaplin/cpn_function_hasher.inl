
#include "ddk_rtti_defs.h"

namespace cpn
{

template<typename Im,typename ... Dom>
size_t function_hasher<Im,Dom...>::operator()(const ddk::detail::builtin_number_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const
{
	return ddk::hash_combine(ddk::rtti::type_info<ddk::detail::builtin_number_function<Im,ddk::mpl::type_pack<Dom...>>,type_interface>(),i_function.get_number());
}
template<typename Im,typename ... Dom>
size_t function_hasher<Im,Dom...>::operator()(const ddk::detail::builtin_component_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const
{
	return ddk::hash_combine(ddk::rtti::type_info<ddk::detail::builtin_component_function<Im,ddk::mpl::type_pack<Dom...>>,type_interface>(),i_function.get_component());
}
template<typename Im,typename ... Dom>
size_t function_hasher<Im,Dom...>::operator()(const ddk::detail::builtin_composed_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const
{
	static const function_hasher<Im,Im> s_destVisitor;

	return ddk::hash_combine(ddk::rtti::type_info<ddk::detail::builtin_composed_function<Im,ddk::mpl::type_pack<Dom...>>,type_interface>(),visit(*this,i_function.get_source_function()),visit(s_destVisitor,i_function.get_dest_function()));
}
template<typename Im,typename ... Dom>
size_t function_hasher<Im,Dom...>::operator()(const ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function) const
{
	const ddk::commutative_builtin_hasher hasher(ddk::rtti::type_info<ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>,type_interface>());

	for(size_t index=0;index<i_function.size();++index)
	{
		hasher(visit(*this,i_function.get_operand(index)));
	}

	return hasher.get();
}
template<typename Im,typename ... Dom>
size_t function_hasher<Im,Dom...>::operator()(const ddk::detail::builtin_prod_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function) const
{
	const ddk::commutative_builtin_hasher hasher(ddk::rtti::type_info<ddk::detail::builtin_prod_nary_functor<Im,ddk::mpl::type_pack<Dom...>>,type_interface>());

	for(size_t index = 0; index < i_function.size(); ++index)
	{
		hasher(visit(*this,i_function.get_operand(index)));
	}

	return hasher.get();
}
template<typename Im,typename ... Dom>
size_t function_hasher<Im,Dom...>::operator()(const ddk::detail::builtin_inverted_function<Im,ddk::mpl::type_pack<Dom...>>& i_function) const
{
	return ~visit(*this,i_function.get_expresion());
}

}