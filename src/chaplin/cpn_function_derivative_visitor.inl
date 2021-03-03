
#include "cpn_space_ops.h"

namespace cpn
{
namespace
{

TEMPLATE(typename T,size_t Index)
REQUIRES(IS_CALLABLE(T))
inline function<typename T::return_type(typename T::args_type)> custom_derivative(const T& i_callable,...)
{
	//TBD
	return {};
}
template<set_type Im,set_type Dom,size_t Index, typename T, size_t Component>
inline function<Im(Dom)> custom_derivative(const T& i_callable, const ddk::projection_callable<Component>&)
{
	return ddk::constant_callable<Im>((Index == Component)? Im::mult_operation::identity : Im::mult_operation::annihilator);
}
template<coordinate_type Im, set_type Dom, size_t Index, size_t ... Indexs>
inline ddk::high_order_array<function<mpl::component_wise_function_image<Im>(Dom)>,get_rank<Im>()> custom_derivative(const ddk::detail::builtin_fusioned_function<Im,mpl::terse_function_dominion<Dom>>& i_function, const ddk::mpl::sequence<Indexs...>&)
{
	static derivative_visitor_impl<typename Im::place_type,Dom,Index> nestedVisitor;
	
	return { ddk::visit(nestedVisitor,i_function.template get_callable<Indexs>())... };
}

}

namespace detail
{

template<set_type Im, set_type Dom, size_t Index>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const ddk::detail::add_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return ddk::visit(*this,i_function.get_lhs().m_functionImpl) + ddk::visit(*this,i_function.get_rhs().m_functionImpl);
}
template<set_type Im,set_type Dom,size_t Index>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const ddk::detail::subs_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return ddk::visit(*this,i_function.get_lhs().m_functionImpl) - ddk::visit(*this,i_function.get_rhs().m_functionImpl);
}
template<set_type Im,set_type Dom,size_t Index>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const ddk::detail::prod_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return ddk::visit(*this,i_function.get_lhs().m_functionImpl) * i_function.get_rhs() + i_function.get_lhs() * ddk::visit(*this,i_function.get_rhs().m_functionImpl);
}
//template<set_type Im,set_type Dom>
//typename derivative_visitor_impl<Im,Dom>::return_type derivative_visitor_impl<Im,Dom>::operator()(const ddk::detail::div_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function)
//{
//	return (ddk::visit(*this,i_function.get_lhs().m_functionImpl) * i_function.get_rhs() - i_function.get_lhs() * ddk::visit(*this,i_function.get_rhs().m_functionImpl)) / (i_function.get_rhs() * i_function.get_rhs());
//}
template<set_type Im,set_type Dom,size_t Index>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const ddk::detail::builtin_number_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return i_function.get_number();
}
template<set_type Im,set_type Dom,size_t Index>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const ddk::detail::builtin_composed_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	static const derivative_visitor_impl<Im,Im,Index> leftVisitor;

	return return_type{ddk::detail::builtin_composed_function<Im,mpl::terse_function_dominion<Dom>>{ddk::visit(leftVisitor,i_function.get_dest_function().m_functionImpl),i_function.get_source_function()}} * ddk::visit(*this,i_function.get_source_function().m_functionImpl);
}
template<set_type Im,set_type Dom,size_t Index>
TEMPLATE(typename T)
REQUIRED(IS_BUILTIN_FUNCTION(T))
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const T& i_function) const
{
	return custom_derivative<Im,Dom,Index>(i_function,typename T::function_t{});
}
template<set_type Im,set_type Dom,size_t Index>
template<typename T>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<1>>::operator()(const T& i_function,...) const
{
	return custom_derivative(i_function);
}

template<set_type Im,set_type Dom,size_t Index, size_t ... Indexs>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<Indexs...>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<Indexs...>>::operator()(const ddk::detail::builtin_fusioned_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return return_type{ visit<derivative_visitor_impl<space_funcdamental_type<Im>,Dom,Index,ddk::mpl::sequence<1>>>(i_function.template get_callable<Indexs>()) ...};
}
template<set_type Im,set_type Dom,size_t Index,size_t ... Indexs>
template<typename T>
typename derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<Indexs...>>::return_type derivative_visitor_impl<Im,Dom,Index,ddk::mpl::sequence<Indexs...>>::operator()(const T& i_function, ...) const
{
	return {};
}

}
}
