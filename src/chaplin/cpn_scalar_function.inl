
namespace cpn
{

template<set_type ImSet,set_type DomSet>
template<size_t ... Indexs, typename ... Callables>
function<ImSet(DomSet)>::function(const ddk::mpl::sequence<Indexs...>&, const Callables& ... i_callables)
: function_base_t(ddk::detail::builtin_fusioned_function<ImSet,mpl::terse_function_dominion<DomSet>>(ddk::fusion(ddk::detail::instantiate_template_callable<nth_coordinate_type<Indexs>>(i_callables,mpl::terse_function_dominion<DomSet>{})...)))
{
}
template<set_type ImSet,set_type DomSet>
TEMPLATE(typename T)
REQUIRED(IS_INSTANTIABLE_BY(T,ImSet,mpl::terse_function_dominion<DomSet>))
function<ImSet(DomSet)>::function(const T& i_templateCallable)
: function_base_t(ddk::detail::instantiate_template_callable<ImSet>(i_templateCallable,mpl::terse_function_dominion<DomSet>{}))
{
}
template<set_type ImSet,set_type DomSet>
TEMPLATE(typename ... Callables)
REQUIRED(IS_COORDINATE(ImSet),IS_INSTANTIABLE(Callables)...)
function<ImSet(DomSet)>::function(const Callables& ... i_templateCallables)
: function(typename ddk::mpl::make_sequence<0,ddk::mpl::num_types<Callables...>>::type{},i_templateCallables...)
{
}
template<set_type ImSet,set_type DomSet>
function<ImSet(DomSet)>::function(const function_base_t& i_function)
: function_base_t(i_function)
{
}

}
