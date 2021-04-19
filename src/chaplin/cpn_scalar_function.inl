

namespace cpn
{
namespace detail
{

template<set_type Im,set_type ... Dom>
scalar_function<Im,ddk::mpl::type_pack<Dom...>>::scalar_function(const function_base_t& i_function)
: function_base_t(i_function)
{
}
template<set_type Im,set_type ... Dom>
TEMPLATE(typename Callable)
REQUIRED(IS_INSTANTIABLE_BY(Callable,Im,ddk::mpl::type_pack<Dom...>))
scalar_function<Im,ddk::mpl::type_pack<Dom...>>::scalar_function(const Callable& i_callable)
: function_base_t(instance_as_function<Im,ddk::mpl::type_pack<Dom...>>(i_callable))
{
}

template<coordinate_type Im,set_type ... Dom>
vector_function<Im,ddk::mpl::type_pack<Dom...>>::vector_function(const function_base_t& i_function)
: function_base_t(i_function)
{
}
template<coordinate_type Im,set_type ... Dom>
TEMPLATE(typename ... Callables)
REQUIRED(IS_INSTANTIABLE_BY(Callables,Im,ddk::mpl::type_pack<Dom...>)...)
vector_function<Im,ddk::mpl::type_pack<Dom...>>::vector_function(const Callables& ... i_callables)
: function_base_t(ddk::detail::builtin_fusioned_function<Im,ddk::mpl::type_pack<Dom...>>(ddk::fusion(cpn::function_impl<typename Im::place_type(ddk::mpl::type_pack<Dom...>)>{instance_as_function<typename Im::place_type,ddk::mpl::type_pack<Dom...>>(i_callables)}...)))
{
}

}

}
