
#include "ddk_constant_callable.h"

namespace ddk
{
namespace detail
{

template<typename Im,typename Callable,typename ... Dom>
constexpr cpn::function_impl<Im(ddk::mpl::type_pack<Dom...>)> instantiate_template_callable(Callable&& i_callable,const ddk::mpl::type_pack<Dom...>&)
{
    return i_callable.instance<Im,Dom...>();
}

template<typename ImSet,typename ... Dom>
builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::builtin_composed_function(const function_lhs_t& i_lhs,const function_rhs_t& i_rhs)
: m_lhs(i_lhs)
, m_rhs(i_rhs)
{
}
template<typename ImSet,typename ... Dom>
ImSet builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return ddk::eval(m_lhs,ddk::eval(m_rhs,std::forward<Dom>(i_args) ...));
}
template<typename ImSet,typename ... Dom>
const typename builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::function_lhs_t& builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::get_dest_function() const
{
    return m_lhs;
}
template<typename ImSet,typename ... Dom>
const typename builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::function_rhs_t& builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>>::get_source_function() const
{
    return m_rhs;
}

template<typename LhsFunction,typename RhsFunction>
constexpr builtin_composed_template_function<LhsFunction,RhsFunction>::builtin_composed_template_function(const LhsFunction& i_lhs,const RhsFunction& i_rhs)
: m_lhs(i_lhs)
, m_rhs(i_rhs)
{
}
template<typename LhsFunction,typename RhsFunction>
template<typename Type,typename ... Types>
constexpr builtin_composed_function<Type,ddk::mpl::type_pack<Types...>> builtin_composed_template_function<LhsFunction,RhsFunction>::instance() const
{
    return { m_lhs.template instance<Type,const Type&>(),m_rhs.template instance<Type,Types...>() };
}

template<typename ImSet,typename ... Dom>
builtin_number_function<ImSet,ddk::mpl::type_pack<Dom...>>::builtin_number_function(const function_t& i_number)
: m_number(i_number)
{
}
template<typename ImSet,typename ... Dom>
inline ImSet builtin_number_function<ImSet,ddk::mpl::type_pack<Dom...>>::operator()(Dom... i_args) const
{
    return ddk::eval(m_number,std::forward<Dom>(i_args) ...);
}
template<typename ImSet,typename ... Dom>
const typename builtin_number_function<ImSet,ddk::mpl::type_pack<Dom...>>::function_t& builtin_number_function<ImSet,ddk::mpl::type_pack<Dom...>>::get_number() const
{
    return m_number;
}

template<typename T>
constexpr builtin_numeric_template_function<T>::builtin_numeric_template_function(const T& i_number)
: m_number(i_number)
{
}
template<typename T>
template<typename Type,typename ... Types>
constexpr builtin_number_function<Type,ddk::mpl::type_pack<Types...>> builtin_numeric_template_function<T>::instance() const
{
    return { ddk::constant_callable<Type>(Type(m_number)) };
}

}
}