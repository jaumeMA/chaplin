#pragma once

#include "cpn_function_allocator.h"
#include "cpn_algebraic_concepts.h"
#include "cpn_function_template_helper.h"
#include "ddk_inherited_value.h"
#include "ddk_function.h"
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

    template<typename Callable,typename ... Functions>
    friend inline auto visit(Callable&& i_callable,const function_impl& i_function, const Functions& ... i_functions)
    {
        typedef decltype(ddk::visit<ddk::detail::function_impl_base<Im,ddk::mpl::type_pack<Dom...>>>(std::forward<Callable>(i_callable),i_function.m_functionImpl,i_functions.m_functionImpl ...)) return_type;

        if constexpr (std::is_same<return_type,void>::value)
        {
            ddk::visit<ddk::detail::function_impl_base<Im,ddk::mpl::type_pack<Dom...>>>(std::forward<Callable>(i_callable),i_function.m_functionImpl,i_functions.m_functionImpl ...);
        }
        else
        {
            return ddk::visit<ddk::detail::function_impl_base<Im,ddk::mpl::type_pack<Dom...>>>(std::forward<Callable>(i_callable),i_function.m_functionImpl,i_functions.m_functionImpl ...);
        }
    }
    TEMPLATE(typename Callable,typename ... Functions)
    REQUIRES(IS_SAME_CLASS(function_impl,Functions)...)
    friend inline auto visit(const function_impl& i_function, const Functions& ... i_functions)
    {
        typedef decltype(ddk::visit<ddk::detail::function_impl_base<Im,ddk::mpl::type_pack<Dom...>>>(Callable{},i_function.m_functionImpl,i_functions.m_functionImpl ...)) return_type;

        if constexpr(std::is_same<return_type,void>::value)
        {
            ddk::visit<ddk::detail::function_impl_base<Im,ddk::mpl::type_pack<Dom...>>>(Callable{},i_function.m_functionImpl,i_functions.m_functionImpl ...);
        }
        else
        {
            return ddk::visit<ddk::detail::function_impl_base<Im,ddk::mpl::type_pack<Dom...>>>(Callable{},i_function.m_functionImpl,i_functions.m_functionImpl ...);
        }
    }

public:
    function_impl(const function_impl& other);
    function_impl(function_impl&& other);

    function_impl& operator=(const function_impl& other) = default;
    function_impl& operator=(function_impl&& other) = default;

protected:
    using function_base_t::function_base_t;
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

#include "cpn_function_impl.inl"