#pragma once

#include "ddkFramework/ddk_function_impl.h"
#include "ddkFramework/ddk_inherited_value.h"
#include "ddk_function.h"
#include "cpn_function_allocator.h"
#include "ddk_rtti.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(_FUNC,_NAME,_OP) \
friend inline _FUNC operator _OP(const _FUNC& i_lhs, const _FUNC& i_rhs) \
{ \
    return { _NAME##_binary_functor{i_lhs,i_rhs} }; \
}

namespace cpn
{

template<typename Return, typename ... Types>
using inherited_function_base = ddk::inherited_value<ddk::detail::function_impl_base<Return,Types...>>;

template<typename>
class function;
    
template<typename Im, typename ... Dom>
class function<Im(const Dom& ...)> : public ddk::detail::function_impl<Im(const Dom& ...),function_allocator,inherited_function_base<Im,const Dom& ...>>
{
    typedef ddk::detail::function_impl<Im(const Dom& ...),function_allocator,inherited_function_base<Im,const Dom& ...>> function_base_t;

public:
    using function_base_t::function_base_t;
};

}

#include "cpn_function.inl"
