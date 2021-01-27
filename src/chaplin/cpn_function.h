#pragma once

#include "ddkFramework/ddk_function_impl.h"
#include "ddkFramework/ddk_inherited_value.h"
#include "ddk_function.h"
#include "cpn_function_allocator.h"

namespace cpn
{

template<typename Return, typename ... Types>
using inherited_function_base = ddk::inherited_value<function_impl_base<Return,ddk::tuple<Types...>>>;

template<template<typename> typename FinalType, typename Im, typename ... Dom>
class function : public ddk::detail::function_impl<Im(Dom...),function_allocator,inherited_function_base<Im,Dom...>>
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
