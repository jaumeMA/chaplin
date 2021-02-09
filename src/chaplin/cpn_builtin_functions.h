#pragma once

#include "ddk_rtti.h"
#include "cpn_function.h"
#include "ddk_concepts.h"
#include "cpn_function_concepts.h"
#include <cmath>

#define DEFINE_ARITHMETIC_UNARY_OPERATION(_NAME,_OP) \
template<typename ImSet, typename ... Dom> \
struct _NAME##_unary_functor : public ddk::detail::inherited_functor_impl<ImSet,Dom ...> \
{ \
    typedef cpn::function<ImSet(const Dom& ...)> function_t; \
    \
public: \
    _NAME##_unary_functor(const function_t & i_rhs) \
    : m_rhs(i_rhs) \
    { \
    } \
    \
    ImSet operator()(Dom ... i_args) const \
    { \
        return _OP m_rhs(std::forward<Dom>(i_args)...); \
    } \
    \
private: \
    const function_t m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_unary_functor,cpn::detail::function_impl_base); \
 \
template<typename RhsFunction> \
struct _NAME##_unary_template_functor \
{ \
    constexpr _NAME##_unary_template_functor() = default; \
    template<typename Type,typename ... Types> \
    static inline _NAME##_unary_functor<Type,ddk::mpl::type_pack<Types...>> instance() \
    { \
        return { RhsFunction::template instance<Type,Types...>() }; \
    } \
};

#define DEFINE_ARITHMETIC_BINARY_OPERATION(_NAME,_OP) \
template<typename ImSet, typename ... Dom> \
struct _NAME##_binary_functor : public ddk::detail::inherited_functor_impl<ImSet,Dom ...> \
{ \
    typedef cpn::function<ImSet(Dom...)> function_t; \
        \
public: \
    _NAME##_binary_functor(const function_t& i_lhs, const function_t& i_rhs) \
    : m_lhs(i_lhs) \
    , m_rhs(i_rhs) \
    { \
    } \
    \
    ImSet operator()(Dom ... i_args) const \
    { \
        return ddk::eval(m_lhs,std::forward<Dom>(i_args)...) _OP ddk::eval(m_rhs,std::forward<Dom>(i_args)...); \
    } \
    \
private: \
    const function_t m_lhs; \
    const function_t m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_binary_functor,cpn::detail::function_impl_base); \
 \
template<typename LhsFunction, typename RhsFunction> \
struct _NAME##_binary_template_functor \
{ \
    constexpr _NAME##_binary_template_functor() = default; \
    template<typename Type, typename ... Types> \
    static inline _NAME##_binary_functor<Type,Types...> instance() \
    { \
        return _NAME##_binary_functor<Type,Types...>{LhsFunction::template instance<Type,Types...>(), RhsFunction::template instance<Type,Types...>() }; \
    } \
};

#define DEFINE_BUILTIN_FUNCTION(_NAME,_FUNC) \
template<typename ImSet, typename ... Dom> \
struct _NAME##_builtin_function : public ddk::detail::inherited_functor_impl<ImSet,Dom...> \
{ \
    _NAME##_builtin_function() = default; \
    _NAME##_builtin_function(_NAME##_builtin_function&&) = default; \
    ImSet operator()(Dom... i_args) const \
    { \
        return static_cast<ImSet>(_FUNC(std::forward<Dom>(i_args) ...)); \
    } \
    \
} PUBLISH_RTTI_INHERITANCE(_NAME##_builtin_function,cpn::detail::function_impl_base); \
 \
struct _NAME##_builtin_template_function \
{ \
    constexpr _NAME##_builtin_template_function() = default; \
    template<typename Type,typename ... Types> \
    static inline _NAME##_builtin_function<Type,Types...> instance() \
    { \
        return _NAME##_builtin_function<Type,Types...>{}; \
    } \
\
}; \
extern const _NAME##_builtin_template_function _NAME = _NAME##_builtin_template_function{};

#define DEFINE_BUILTIN_FUNCTION_OPERATOR(_NAME,_OP) \
TEMPLATE(typename LhsFunctor,typename RhsFunctor) \
REQUIRES(IS_INSTANTIABLE(LhsFunctor),IS_INSTANTIABLE(RhsFunctor)) \
inline cpn::detail::##_NAME##_binary_template_functor<LhsFunctor,RhsFunctor> operator##_OP(const LhsFunctor& i_lhs,const RhsFunctor& i_rhs) \
{ \
    return {}; \
}

namespace cpn
{
namespace detail
{

//arithmetic operations
DEFINE_ARITHMETIC_UNARY_OPERATION(neg,-);
DEFINE_ARITHMETIC_BINARY_OPERATION(add,+);
DEFINE_ARITHMETIC_BINARY_OPERATION(subs,-);
DEFINE_ARITHMETIC_BINARY_OPERATION(prod,*);
DEFINE_ARITHMETIC_BINARY_OPERATION(div,/);

}

//predefined math functions
DEFINE_BUILTIN_FUNCTION(sin,std::sin);
DEFINE_BUILTIN_FUNCTION(cos,std::cos);
DEFINE_BUILTIN_FUNCTION(_x,ddk::projection<0>);
DEFINE_BUILTIN_FUNCTION(_x_0,ddk::projection<0>);
DEFINE_BUILTIN_FUNCTION(_x_1,ddk::projection<1>);
DEFINE_BUILTIN_FUNCTION(_x_2,ddk::projection<2>);
DEFINE_BUILTIN_FUNCTION(_x_3,ddk::projection<3>);
DEFINE_BUILTIN_FUNCTION(_x_4,ddk::projection<4>);
DEFINE_BUILTIN_FUNCTION(_x_5,ddk::projection<5>);
DEFINE_BUILTIN_FUNCTION(_x_6,ddk::projection<6>);
DEFINE_BUILTIN_FUNCTION(_x_7,ddk::projection<7>);
DEFINE_BUILTIN_FUNCTION(_x_8,ddk::projection<8>);
DEFINE_BUILTIN_FUNCTION(_x_9,ddk::projection<9>);


DEFINE_BUILTIN_FUNCTION_OPERATOR(add,+)
DEFINE_BUILTIN_FUNCTION_OPERATOR(subs,-)
DEFINE_BUILTIN_FUNCTION_OPERATOR(prod,*)
DEFINE_BUILTIN_FUNCTION_OPERATOR(div,/)

}

#include "cpn_builtin_functions.inl"