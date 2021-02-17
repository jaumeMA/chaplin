#pragma once

#include "ddkFramework/ddk_function_impl.h"
#include "ddkFramework/ddk_inherited_value.h"
#include "ddk_function.h"
#include "cpn_function_allocator.h"
#include "ddk_rtti.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(_FUNC,_NAME,_OP) \
friend inline _FUNC operator##_OP(const _FUNC& i_lhs, const _FUNC& i_rhs) \
{ \
    return _NAME##_binary_functor(i_lhs,i_rhs); \
}

namespace cpn
{

template<set_type Return, set_type ... Types>
using inherited_function_base = ddk::inherited_value<ddk::detail::function_base<Return,Types...>>;

template<typename>
class function_impl;
    
template<set_type Im,set_type ... Dom>
class function_impl<Im(ddk::mpl::type_pack<Dom...>)> : public ddk::detail::function_impl<Im(Dom...),function_allocator,inherited_function_base<Im,Dom...>>
{
    typedef ddk::detail::function_impl<Im(Dom...),function_allocator,inherited_function_base<Im,Dom...>> function_base_t;

protected:
    using function_base_t::function_base_t;
};

}

#include "cpn_function.inl"
#include "cpn_builtin_functions.h"
