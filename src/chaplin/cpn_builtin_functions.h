#pragma once

#include "ddk_visitable_defs.h"

#define DEFINE_ARITHMETIC_BINARY_FUNCTION(_NAME,_OP) \
template<typename FunctionRhs> \
struct _NAME##_unary_functor : public cpn::detail::function_impl_base<ImSet,DomSet> \
{ \
public: \
    _NAME##_unary_functor(const FunctionRhs& i_rhs) \
    : m_rhs(i_rhs) \
    { \
    } \
    \
    template<typename ... Args> \
    inline auto operator(Args&& ... i_args) const; \
    { \
        return _OP m_rhs(std::forward<Args>(i_args)...); \
    } \
    \
private: \
    FunctionRhs m_rhs; \
}; \
const bool ____expand_type_visitable_type##_Type_Name##_Type_Interface = ddk::visitable_type<_Type_Name,_Type_Interface>::s_initialized;\
template<typename FunctionRhs> \
typename decltype(__get_inherited_type_list(std::declval<cpn::detail::function_impl_base<ImSet,DomSet>>(),std::declval<ddk::mpl::static_number<ddk::static_counter<cpn::detail::function_impl_base<ImSet,DomSet>>::get_curr_count()>>()))::add<_NAME##_unary_functor<FunctionRhs>>::type __get_inherited_type_list(const cpn::detail::function_impl_base<ImSet,DomSet>&,const ddk::mpl::static_number<ddk::static_counter<cpn::detail::function_impl_base<ImSet,DomSet>>::get_next_count()>&);


#define DEFINE_ARITHMETIC_BINARY_FUNCTION(_NAME,_OP) \
template<typename FunctionLhs, typename FunctionRhs> \
struct _NAME##_binary_functor : public cpn::detail::function_impl_base<ImSet,DomSet> \
{ \
public: \
    _NAME##_binary_functor(const FunctionLhs& i_lhs, const FunctionRhs& i_rhs) \
    : m_lhs(i_lhs) \
    , m_rhs(i_rhs) \
    { \
    } \
    \
    template<typename ... Args> \
    inline auto operator(Args&& ... i_args) const; \
    { \
        return m_lhs(std::forward<Args>(i_args)...) _OP m_rhs(std::forward<Args>(i_args)...); \
    } \
    \
private: \
    FunctionLhs m_lhs; \
    FunctionRhs m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_binary_functor,cpn::detail::function_impl_base<ImSet,DomSet>);


namespace cpn
{
namespace detail
{

DEFINE_ARITHMETIC_BINARY_FUNCTION(neg,-);
DEFINE_ARITHMETIC_BINARY_FUNCTION(add,+);
DEFINE_ARITHMETIC_BINARY_FUNCTION(prod,*);
DEFINE_ARITHMETIC_BINARY_FUNCTION(div,/);

}
}
