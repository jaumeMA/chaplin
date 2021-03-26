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

    template<typename Visitor>
    friend inline auto visit(const function_impl& i_function)
    {
        return ddk::visit<Visitor>(i_function.m_functionImpl);
    }
    template<typename Visitor>
    friend inline auto visit(Visitor&& i_visitor,const function_impl& i_function)
    {
        return ddk::visit(i_visitor,i_function.m_functionImpl);
    }

protected:
    using function_base_t::function_base_t;

public:
    function_impl(const function_impl& other);
    function_impl(function_impl&& other);

    function_impl& operator=(const function_impl& other) = default;
    function_impl& operator=(function_impl&& other) = default;
};

}

namespace ddk
{
namespace mpl
{

template<typename Return, typename ... Types>
struct aqcuire_callable_return_type<cpn::function_impl<Return(type_pack<Types...>)>>
{
	typedef Return type;
};

}
}

#include "cpn_function.inl"
#include "cpn_builtin_functions.h"
