#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
#include "cpn_set.h"
#include "cpn_function_template_helper.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(_FUNC,_NAME,_OP) \
friend inline _FUNC operator _OP(const _FUNC& i_lhs, const _FUNC& i_rhs) \
{ \
    return { ddk::detail::_NAME##_binary_functor(i_lhs,i_rhs) }; \
}

namespace cpn
{
namespace detail
{

TEMPLATE(typename T, typename ... TT)
REQUIRES(IS_SAME_CLASS(T,TT)...)
inline ddk::high_order_array<T,1+ddk::mpl::num_types<TT...>> as_uniform_tuple(const ddk::function_arguments<T,TT...>& i_args);

}

template<typename>
class function;

template<set_type ImSet, set_type DomSet>
class function<ImSet(DomSet)> : public function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>
{
    typedef function_impl<ImSet(mpl::terse_function_dominion<DomSet>)> function_base_t;
    template<size_t Index>
    using nth_coordinate_type = ddk::mpl::nth_coordinate_of_t<Index,ImSet>;

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,add,+);
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,subs,-);
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,prod,*);
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,div,/);

public:
    function(const function_base_t& i_function);
    TEMPLATE(typename T)
    REQUIRES(IS_INSTANTIABLE_BY(T,ImSet,mpl::terse_function_dominion<DomSet>))
    function(const T& i_callable);
    TEMPLATE(typename ... Callables)
    REQUIRES(IS_COORDINATE(ImSet),IS_INSTANTIABLE(Callables)...)
    function(const Callables& ... i_callables);

    using function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>::m_functionImpl;

protected:
    template<size_t ... Indexs, typename ...Callables>
    function(const ddk::mpl::sequence<Indexs...>&, const Callables& ... i_callables);
};

}

#include "cpn_scalar_function.inl"
