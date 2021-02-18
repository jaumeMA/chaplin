
namespace cpn
{

template<set_type ImSet,set_type DomSet>
TEMPLATE(typename T)
REQUIRED(IS_INSTANTIABLE_BY(T,ImSet,mpl::terse_function_dominion<DomSet>))
function<ImSet(DomSet)>::function(T&& i_templateCallable)
: function_base_t(instantiate_template_callable<ImSet>(std::forward<T>(i_templateCallable),mpl::terse_function_dominion<DomSet>{}))
{
}
template<set_type ImSet,set_type DomSet>
function<ImSet(DomSet)>::function(const function_base_t& i_function)
: function_base_t(i_function)
{
}

}