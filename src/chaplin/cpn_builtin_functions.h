#pragma once

#include "ddk_rtti.h"
#include "cpn_function.h"
#include <cmath>

#define DEFINE_ARITHMETIC_BINARY_OPERATION(_NAME,_OP) \
template<typename Imset, typename ... Dom> \
struct _NAME##_unary_functor : public ddk::detail::inherited_functor_impl<ImSet,const Dom& ...> \
{ \
    typedef cpn::function<Imset(const Dom& ...)> function_t;
    \
public: \
    _NAME##_unary_functor(const function_t & i_rhs) \
    : ddk::detail::functor_impl<const _NAME##_unary_functor&,ImSet,const Dom& ...>(*this)
    , m_rhs(i_rhs) \
    { \
    } \
    \
    ImSet operator()(const Dom& ... i_args) const \
    { \
        return _OP m_rhs(std::forward<Args>(i_args)...); \
    } \
    \
private: \
    const function_t m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_unary_functor,ddk::detail::function_impl_base);

#define DEFINE_ARITHMETIC_BINARY_OPERATION(_NAME,_OP) \
template<typename Imset, typename ... Dom> \
struct _NAME##_binary_functor : public ddk::detail::inherited_functor_impl<ImSet,const DomSet& ...> \
{ \
    typedef cpn::function<Imset(const Dom& ...)> function_t;
        \
public: \
    _NAME##_binary_functor(const function_t & i_lhs, const function_t & i_rhs) \
    : ddk::detail::functor_impl<const _NAME##_binary_functor&,ImSet,const DomSet& ...>(*this)
    , m_lhs(i_lhs) \
    , m_rhs(i_rhs) \
    { \
    } \
    \
    ImSet operator()(const Dom& ... i_args) const \
    { \
        return eval(m_lhs,std::forward<Args>(i_args)...) _OP eval(m_rhs,std::forward<Args>(i_args)...); \
    } \
    \
private: \
    const function_t m_lhs; \
    const function_t m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_binary_functor,cpn::detail::function_impl_base);

#define DEFINE_BUILTIN_FUNCTION(_NAME,_FUNC) \
template<typename ImSet, typename DomSet> \
struct _NAME##_builtin_function : public ddk::detail::inherited_functor_impl<ImSet,const DomSet&> \
{ \
    _NAME##_builtin_function(_NAME##_builtin_function&&) = default; \
    ImSet operator()(const Dom& i_args) const \
    { \
        return _FUNC(i_args); \
    } \
    \
}; \
extern const _NAME = cpn::function(_NAME##_builtin_function{});

namespace cpn
{
namespace detail
{

//arithmetic operations
DEFINE_ARITHMETIC_BINARY_OPERATION(neg,-);
DEFINE_ARITHMETIC_BINARY_OPERATION(add,+);
DEFINE_ARITHMETIC_BINARY_OPERATION(prod,*);
DEFINE_ARITHMETIC_BINARY_OPERATION(div,/);

}

//predefined math functions
DEFINE_BUILTIN_FUNCTION(sin,std::sin);
DEFINE_BUILTIN_FUNCTION(cos,std::cos);

}
