
namespace cpn
{
namespace detail
{

template<free_module_type Im,free_module_type Dom,size_t ... Indexs>
TEMPLATE(typename ... Callables)
REQUIRED(IS_LINEAR_INSTANTIABLE(Callables)...)
linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>>::linear_function_impl(Callables&& ... i_callables)
: function_base_t(std::forward<Callables>(i_callables)...)
{
}
template<free_module_type Im,free_module_type Dom, size_t ... Indexs>
auto linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>>::inline_eval(const Dom& i_value) const
{
    return function_base_t::inline_eval(i_value.at(Indexs) ...);
}
template<free_module_type Im,free_module_type Dom, size_t ... Indexs>
auto linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>>::operator()(const Dom& i_value) const
{
    return function_base_t::inline_eval(i_value.at(Indexs) ...);
}

}
}
