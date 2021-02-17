#pragma once

#include "cpn_vector_space.h"
#include "cpn_function.h"
#include "ddk_template_helper.h"

namespace cpn
{
namespace mpl
{
namespace detail
{

template<ring_type Dom, size_t ... Indexs>
ddk::mpl::type_pack<ddk::mpl::index_to_type<Indexs,Dom>...> free_module_function_dominion(const ddk::mpl::sequence<Indexs...>&);

}

template<set_type Dom>
ddk::mpl::type_pack<Dom> function_dominion_resolver(const Dom&, ...);
template<free_module_type Dom>
decltype(detail::free_module_function_dominion<typename Dom::ring_t>(std::declval<typename ddk::mpl::make_sequence<0,Dom::rank>::type>())) function_dominion_resolver(const Dom&);

template<typename Dom>
using terse_function_dominion = decltype(function_dominion_resolver(std::declval<Dom>()));

}
}