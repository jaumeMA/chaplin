
namespace cpn
{

template<set_type ImSet,set_type DomSet>
template<size_t ... Indexs, typename ... Callables>
function<ImSet(DomSet)>::function(const ddk::mpl::sequence<Indexs...>&, const Callables& ... i_callables)
: function_base_t(ddk::detail::builtin_fusioned_function<ImSet,mpl::terse_function_dominion<DomSet>>(ddk::fusion(ddk::detail::instantiate_template_callable<ddk::mpl::nth_coordinate_of_t<Indexs,ImSet>>(i_callables,mpl::terse_function_dominion<DomSet>{})...)))
{
}
template<set_type ImSet,set_type DomSet>
TEMPLATE(typename Callable)
REQUIRED(IS_INSTANTIABLE_BY(Callable,ImSet,mpl::terse_function_dominion<DomSet>))
function<ImSet(DomSet)>::function(const Callable& i_templateCallable)
: function_base_t(ddk::detail::instantiate_template_callable<ImSet>(i_templateCallable,mpl::terse_function_dominion<DomSet>{}))
{
}
template<set_type ImSet,set_type DomSet>
TEMPLATE(typename ... Callables)
REQUIRED(IS_NUMBER_OF_ARGS_GREATER(1,Callables...),IS_INSTANTIABLE_BY(Callables,ImSet,mpl::terse_function_dominion<DomSet>)...)
function<ImSet(DomSet)>::function(const Callables& ... i_templateCallables)
: function(typename ddk::mpl::make_sequence<0,ddk::mpl::num_types<Callables...>>::type{},i_templateCallables...)
{
    static_assert(IS_COORDINATE_COND(ImSet),"You shall use coordinate target types in case of multi functions");
}
template<set_type ImSet,set_type DomSet>
function<ImSet(DomSet)>::function(const function_base_t& i_function)
: function_base_t(i_function)
{
}

}
