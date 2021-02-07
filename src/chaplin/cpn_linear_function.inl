
namespace cpn
{
namespace detail
{

template<typename ImFreeModule,typename DomFreeModule,size_t ... Indexs>
linear_function_impl<ImFreeModule,DomFreeModule,ddk::mpl::sequence<Indexs...>>::linear_function_impl(const ddk::constant_callable<ImFreeModule>& i_constValue)
{
}
template<typename ImFreeModule,typename DomFreeModule,size_t ... Indexs>
template<size_t Component>
linear_function_impl<ImFreeModule,DomFreeModule,ddk::mpl::sequence<Indexs...>>::linear_function_impl(const ddk::projection_callable<Component>& i_component)
{
}
template<typename ImFreeModule, typename DomFreeModule, size_t ... Indexs>
auto linear_function_impl<ImFreeModule,DomFreeModule,ddk::mpl::sequence<Indexs...>>::inline_eval(const DomFreeModule& i_value) const
{
    return function_base_t::inline_eval(i_val.get(Indexs) ...);
}
template<typename ImFreeModule, typename DomFreeModule, size_t ... Indexs>
auto linear_function_impl<ImFreeModule,DomFreeModule,ddk::mpl::sequence<Indexs...>>::operator()(const DomFreeModule& i_value) const
{
    return function_base_t::inline_eval(i_val.get(Indexs) ...);
}

}
}
