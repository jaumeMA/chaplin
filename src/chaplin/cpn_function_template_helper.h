#pragma once

#include "cpn_vector_space.h"
#include "cpn_function.h"
#include "cpn_space_ops.h"
#include "ddk_template_helper.h"

namespace cpn
{
namespace mpl
{
namespace detail
{

template<set_type Dom, size_t ... Indexs>
ddk::mpl::type_pack<ddk::mpl::index_to_type<Indexs,Dom>...> coordinate_function_dominion(const ddk::mpl::sequence<Indexs...>&);

}

template<typename Dom>
ddk::mpl::type_pack<Dom> function_dominion_resolver(const Dom&, ...);
template<coordinate_type Dom>
decltype(detail::coordinate_function_dominion<typename Dom::place_type>(std::declval<typename ddk::mpl::make_sequence<0,get_rank<Dom>()>::type>())) function_dominion_resolver(const Dom&);

template<set_type Dom>
using terse_function_dominion = decltype(function_dominion_resolver(std::declval<Dom>()));

template<set_type Im>
Im function_image_resolver(const Im&,...);
template<free_module_type Im>
typename Im::ring_t function_image_resolver(const Im&);

template<set_type Im>
using component_wise_function_image = decltype(function_image_resolver(std::declval<Im>()));

}
}