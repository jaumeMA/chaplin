
namespace cpn
{

TEMPLATE(typename T)
REQUIRED(IS_CALLABLE(T))
function_impl<typename T::return_type(typename T::args_type)> custom_derivative(const T& i_callable,...)
{
	//TBD
	return {};
}
template<set_type Im, set_type Dom>
typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const ddk::detail::add_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return ddk::visit(*this,i_function.get_lhs().m_functionImpl) + ddk::visit(*this,i_function.get_rhs().m_functionImpl);
}
template<set_type Im,set_type Dom>
typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const ddk::detail::subs_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return ddk::visit(*this,i_function.get_lhs().m_functionImpl) - ddk::visit(*this,i_function.get_rhs().m_functionImpl);
}
template<set_type Im,set_type Dom>
typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const ddk::detail::prod_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return ddk::visit(*this,i_function.get_lhs().m_functionImpl) * i_function.get_rhs() + i_function.get_lhs() * ddk::visit(*this,i_function.get_rhs().m_functionImpl);
}
//template<set_type Im,set_type Dom>
//typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const ddk::detail::div_binary_functor<Im,mpl::terse_function_dominion<Dom>>& i_function)
//{
//	return (ddk::visit(*this,i_function.get_lhs().m_functionImpl) * i_function.get_rhs() - i_function.get_lhs() * ddk::visit(*this,i_function.get_rhs().m_functionImpl)) / (i_function.get_rhs() * i_function.get_rhs());
//}
template<set_type Im,set_type Dom>
typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const ddk::detail::builtin_number_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	return i_function.get_number();
}
template<set_type Im,set_type Dom>
typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const ddk::detail::builtin_composed_function<Im,mpl::terse_function_dominion<Dom>>& i_function) const
{
	if constexpr (std::is_same<Im,Dom>::value)
	{
		return ddk::visit(*this,i_function.get_dest_function().m_functionImpl) * ddk::visit(*this,i_function.get_source_function().m_functionImpl);
	}
	else
	{
		static const derivative_visitor<Im,Im> leftVisitor;

		return return_type{ddk::detail::builtin_composed_function<Im,mpl::terse_function_dominion<Dom>>{ddk::visit(leftVisitor,i_function.get_dest_function().m_functionImpl),i_function.get_source_function()}} * ddk::visit(*this,i_function.get_source_function().m_functionImpl);
	}
}
template<set_type Im,set_type Dom>
template<typename T>
typename derivative_visitor<Im,Dom>::return_type derivative_visitor<Im,Dom>::operator()(const T& i_function, ...) const
{
	return custom_derivative(i_function);
}

}
