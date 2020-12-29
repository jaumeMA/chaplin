#pragma once

#include "ddkFramework/ddk_function_impl.h"
#include "ddkFramework/ddk_inherited_value.h"

namespace cpn
{

template<typename>
class math_function;

template<typename T,typename TT>
using function_base_const_shared_ptr = shared_pointer_wrapper<const function_impl_base<T,TT>>;

template<typename Return, typename ... Types>
class math_function<Return(Types...)>
{
public:


private:
	ddk::shared_reference_wrapper<ddk::inherited_value<function_impl_base<Return,ddk::tuple<Types...>>>> m_impl;
};

}