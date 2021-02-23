#pragma once

#include "ddkFramework/ddk_function_impl.h"
#include "ddkFramework/ddk_inherited_value.h"
#include "ddk_function.h"
#include "cpn_function_allocator.h"
#include "ddk_rtti.h"

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

public:
    using function_base_t::m_functionImpl;
    function_impl(const function_impl& other);
    function_impl(function_impl&& other);
};

}

namespace ddk
{
namespace mpl
{

template<cpn::set_type Return, cpn::set_type ... Types>
struct aqcuire_callable_return_type<cpn::function_impl<Return(type_pack<Types...>)>>
{
	typedef Return return_type;
	typedef type_pack<Types...> args_type;
};

}
}

#include "cpn_function.inl"
#include "cpn_builtin_functions.h"
