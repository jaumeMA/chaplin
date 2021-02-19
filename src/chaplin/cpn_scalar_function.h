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

template<typename>
class function;

template<set_type ImSet, set_type DomSet>
class function<ImSet(DomSet)> : public function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>
{
    typedef function_impl<ImSet(mpl::terse_function_dominion<DomSet>)> function_base_t;

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,add,+);
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,subs,-);
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,prod,*);
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(function,div,/);

public:
    function(const function_base_t& i_function);
    TEMPLATE(typename T)
    REQUIRES(IS_INSTANTIABLE_BY(T,ImSet,mpl::terse_function_dominion<DomSet>))
    function(T&& i_callable);

    using function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>::m_functionImpl;
};

}

#include "cpn_scalar_function.inl"
