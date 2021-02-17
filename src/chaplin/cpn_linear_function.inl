
namespace cpn
{
namespace detail
{

template<free_module_type Im,free_module_type Dom,size_t ... Indexs>
TEMPLATE(typename T)
REQUIRED(IS_LINEAR_INSTANTIABLE_BY(T,Im,Dom))
linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>>::linear_function_impl(T&& i_callable)
{
}
template<free_module_type Im,free_module_type Dom, size_t ... Indexs>
auto linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>>::inline_eval(const Dom& i_value) const
{
    return function_base_t::inline_eval(i_value.get(Indexs) ...);
}
template<free_module_type Im,free_module_type Dom, size_t ... Indexs>
auto linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>>::operator()(const Dom& i_value) const
{
    return function_base_t::inline_eval(i_value.get(Indexs) ...);
}

}
}
