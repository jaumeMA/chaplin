#pragma once

#include "ddkFramework/ddk_function_impl.h"
#include "ddkFramework/ddk_inherited_value.h"
#include "ddk_function.h"
#include "cpn_function_allocator.h"
#include "ddk_rtti.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(NAME,OP) \
friend inline cpn::function operator OP(const cpn::function& i_lhs, const cpn::function& i_rhs) \
{ \
    return static_cast<const base_function&>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

namespace cpn
{
namespace detail
{

template<typename Return, typename ... Types>
struct function_impl_base : public ddk::detail::function_impl_base<Return,ddk::tuple<Types...>>
{
    DECLARE_TYPE_VISITABLE_BASE(function_impl_base)

    typedef ddk::detail::function_impl_base<Return,ddk::tuple<Types...>> function_base_t;

public:
    using function_base_t::function_base_t;
    using function_base_t::operator();
};

}

template<typename Return, typename ... Types>
using inherited_function_base = ddk::inherited_value<detail::function_impl_base<Return,Types...>>;

template<template<typename> typename FinalType, typename Im, typename ... Dom>
class function : public ddk::detail::function_impl<Im(Dom...),function_allocator,inherited_function_base<Im,const Dom& ...>>
{
    typedef ddk::detail::function_impl<Im(Dom...),function_allocator,inherited_function_base<Im,Dom...>> function_base_t;

public:
    template<typename IIm, typename DDom>
    struct map_to
    {
        typedef FinalType<IIm,DDom> type;
    };

    using function_base_t::function_base_t;
};

}

#include "cpn_function.inl"
