
namespace cpn
{
namespace detail
{

template<set_type ImSet,set_type ... DomSet>
scalar_function<ImSet,ddk::mpl::type_pack<DomSet...>>::scalar_function(const function_base_t& i_function)
: function_base_t(i_function)
{
}
template<set_type ImSet,set_type ... DomSet>
TEMPLATE(typename Callable)
REQUIRED(IS_INSTANTIABLE_BY(Callable,ImSet,ddk::mpl::type_pack<DomSet...>))
scalar_function<ImSet,ddk::mpl::type_pack<DomSet...>>::scalar_function(const Callable& i_callable)
: function_base_t(ddk::detail::instantiate_template_callable<ImSet>(i_callable,ddk::mpl::type_pack<DomSet...>{}))
{
}

template<coordinate_type ImSet,set_type ... DomSet>
vector_function<ImSet,ddk::mpl::type_pack<DomSet...>>::vector_function(const function_base_t& i_function)
: function_base_t(i_function)
{
}
template<coordinate_type ImSet,set_type ... DomSet>
TEMPLATE(typename ... Callables)
REQUIRED(IS_INSTANTIABLE_BY(Callables,ImSet,ddk::mpl::type_pack<DomSet...>)...)
vector_function<ImSet,ddk::mpl::type_pack<DomSet...>>::vector_function(const Callables& ... i_callables)
: function_base_t(ddk::detail::builtin_fusioned_function<ImSet,ddk::mpl::type_pack<DomSet...>>(ddk::fusion(ddk::detail::instantiate_template_callable<typename ImSet::place_type>(i_callables,ddk::mpl::type_pack<DomSet...>{})...)))
{
}

}

}
