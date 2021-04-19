
#include "ddk_constant_callable.h"
#include "ddk_projection_callable.h"

namespace ddk
{
namespace detail
{

template<typename Im,typename Callable,typename ... Dom>
constexpr cpn::function_impl<Im(ddk::mpl::type_pack<Dom...>)> instantiate_template_callable(Callable&& i_callable,const ddk::mpl::type_pack<Dom...>&)
{
    return i_callable.template instance<Im,Dom...>();
}

template<cpn::coordinate_type ImSet,typename ... Dom>
template<size_t ... Components>
builtin_fusioned_function<ImSet,ddk::mpl::type_pack<Dom...>>::fusioned_components<mpl::sequence<Components...>>::fusioned_components(const intersection_function<cpn::function_impl<mpl::index_to_type<Components,typename ImSet::place_type>(mpl::type_pack<Dom...>)>...>& i_callable)
: m_fusionedFunction(i_callable)
{
}
template<cpn::coordinate_type ImSet,typename ... Dom>
template<typename ... T>
builtin_fusioned_function<ImSet,mpl::type_pack<Dom...>>::builtin_fusioned_function(const intersection_function<cpn::function_impl<T(mpl::type_pack<Dom...>)>...>& i_fusionedCallable)
: m_callables(i_fusionedCallable)
{
}
template<cpn::coordinate_type ImSet,typename ... Dom>
ImSet builtin_fusioned_function<ImSet,mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return execute(typename mpl::make_sequence<0,ImSet::num_places>::type{},i_args...);
}
template<cpn::coordinate_type ImSet,typename ... Dom>
template<size_t Index>
const cpn::function_impl<typename ImSet::place_type(mpl::type_pack<Dom...>)>& builtin_fusioned_function<ImSet,mpl::type_pack<Dom...>>::get_callable() const
{
    return m_callables.m_fusionedFunction.template get_callable<Index>();
}
template<cpn::coordinate_type ImSet,typename ... Dom>
template<size_t ... Indexs>
ImSet builtin_fusioned_function<ImSet,mpl::type_pack<Dom...>>::execute(const mpl::sequence<Indexs...>&, Dom ... i_args) const
{
    return ImSet(eval(m_callables.m_fusionedFunction.template get_callable<Indexs>(),i_args...) ...);
}

template<cpn::fundamental_type ImSet,typename ... Dom>
TEMPLATE(typename Function,typename FFunction)
REQUIRED(IS_CONSTRUCTIBLE(function_lhs_t,Function),IS_CONSTRUCTIBLE(function_rhs_t,FFunction))
builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::builtin_composed_function(Function&& i_lhs, FFunction&& i_rhs)
: m_lhs(std::forward<Function>(i_lhs))
, m_rhs(std::forward<FFunction>(i_rhs))
{
}
template<cpn::fundamental_type ImSet,typename ... Dom>
ImSet builtin_composed_function<ImSet,mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return ddk::eval(m_lhs,ddk::eval(m_rhs,std::forward<Dom>(i_args) ...));
}
template<cpn::fundamental_type ImSet,typename ... Dom>
const typename builtin_composed_function<ImSet,mpl::type_pack<Dom...>>::function_lhs_t& builtin_composed_function<ImSet,mpl::type_pack<Dom...>>::get_dest_function() const
{
    return m_lhs;
}
template<cpn::fundamental_type ImSet,typename ... Dom>
const typename builtin_composed_function<ImSet,mpl::type_pack<Dom...>>::function_rhs_t& builtin_composed_function<ImSet,mpl::type_pack<Dom...>>::get_source_function() const
{
    return m_rhs;
}

template<cpn::fundamental_type ImSet,typename ... Dom>
template<size_t Comp>
builtin_component_function<ImSet,ddk::mpl::type_pack<Dom...>>::builtin_component_function(const ddk::mpl::static_number<Comp>&)
: m_projection(ddk::projection<Comp>)
, m_component(Comp)
{
}
template<cpn::fundamental_type ImSet,typename ... Dom>
ImSet builtin_component_function<ImSet,ddk::mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return ddk::eval(m_projection,std::forward<Dom>(i_args)...);
}
template<cpn::fundamental_type ImSet,typename ... Dom>
size_t builtin_component_function<ImSet,ddk::mpl::type_pack<Dom...>>::get_component() const
{
    return m_component;
}

template<cpn::fundamental_type ImSet,typename ... Dom>
builtin_number_function<ImSet,ddk::mpl::type_pack<Dom...>>::builtin_number_function(const ImSet& i_number)
: m_number(i_number)
{
}
template<cpn::fundamental_type ImSet,typename ... Dom>
inline ImSet builtin_number_function<ImSet,mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return m_number;
}
template<cpn::fundamental_type ImSet,typename ... Dom>
const ImSet& builtin_number_function<ImSet,mpl::type_pack<Dom...>>::get_number() const
{
    return m_number;
}

template<cpn::fundamental_type ImSet,typename ... Dom>
template<typename Expression>
builtin_inverted_function<ImSet,mpl::type_pack<Dom...>>::builtin_inverted_function(Expression&& i_expression)
: m_function(std::forward<Expression>(i_expression))
{
}
template<cpn::fundamental_type ImSet,typename ... Dom>
const typename builtin_inverted_function<ImSet,mpl::type_pack<Dom...>>::function_t& builtin_inverted_function<ImSet,mpl::type_pack<Dom...>>::get_expresion() const
{
    return m_function;
}
template<cpn::fundamental_type ImSet,typename ... Dom>
ImSet builtin_inverted_function<ImSet,mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return -ddk::eval(m_function,std::forward<Dom>(i_args)...);
}

}
}
