
#include "cpn_space_ops.h"

namespace cpn
{
namespace
{

TEMPLATE(typename Function,metric_space_type Im,set_type ... Dom,size_t Index, typename T)
REQUIRES(IS_CALLABLE(T))
inline Function custom_derivative(const T& i_callable,...)
{
	//TBD
	return {};
}

}

namespace detail
{

template<typename Function,metric_space_type Im,set_type ... Dom, size_t Index>
Function derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>::operator()(const ddk::detail::builtin_add_nary_functor<Im,dom_t>& i_function) const
{
	return visit(*this,i_function.get_lhs()) + ddk::visit(*this,i_function.get_rhs());
}
template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index>
Function derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>::operator()(const ddk::detail::builtin_prod_nary_functor<Im,dom_t>& i_function) const
{
	return visit(*this,i_function.get_lhs()) * i_function.get_rhs() + i_function.get_lhs() * ddk::visit(*this,i_function.get_rhs());
}
//template<set_type Im,set_type Dom>
//typename derivative_visitor_impl<Im,Dom>::return_type derivative_visitor_impl<Im,Dom>::operator()(const ddk::detail::div_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function)
//{
//	return (ddk::visit(*this,i_function.get_lhs().m_functionImpl) * i_function.get_rhs() - i_function.get_lhs() * ddk::visit(*this,i_function.get_rhs().m_functionImpl)) / (i_function.get_rhs() * i_function.get_rhs());
//}
template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index>
Function derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>::operator()(const ddk::detail::builtin_component_function<Im,dom_t>& i_function) const
{
	return ddk::detail::builtin_number_function<Im,dom_t>{ (Index == i_function.get_component())? Im::mult_operation::identity : Im::mult_operation::annihilator };
}
template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index>
Function derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>::operator()(const ddk::detail::builtin_number_function<Im,dom_t>& i_function) const
{
	return ddk::detail::builtin_number_function<Im,dom_t>{ ddk::constant_callable<Im>(Im::mult_operation::annihilator) };
}
template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index>
Function derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>::operator()(const ddk::detail::builtin_composed_function<Im,dom_t>& i_function) const
{
    static const derivative_visitor_impl<Function,Im,Im,Index,ddk::mpl::sequence<0>> s_composedVisitor;

	return return_type{ddk::detail::builtin_composed_function<Im,dom_t>{visit(s_composedVisitor,i_function.get_dest_function()),i_function.get_source_function()}} * visit(*this,i_function.get_source_function());
}
template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index>
template<typename T>
Function derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<0>>::operator()(const T& i_function,...) const
{
	return custom_derivative<Function,Im,dom_t,Index>(i_function);
}

template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index, size_t ... Indexs>
typename derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<Indexs...>>::return_type derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<Indexs...>>::operator()(const ddk::detail::builtin_fusioned_function<Im,dom_t>& i_function) const
{
    static const derivative_visitor_impl<Function,space_fundamental_type<Im>,dom_t,Index,ddk::mpl::sequence<0>> s_nestedVisitor;

	return { visit(s_nestedVisitor,i_function.template get_callable<Indexs>()) ...};
}
template<typename Function,metric_space_type Im,set_type ... Dom,size_t Index,size_t ... Indexs>
template<typename T>
typename derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<Indexs...>>::return_type derivative_visitor_impl<Function,Im,ddk::mpl::type_pack<Dom...>,Index,ddk::mpl::sequence<Indexs...>>::operator()(const T& i_function, ...) const
{
	return {};
}

}
}
