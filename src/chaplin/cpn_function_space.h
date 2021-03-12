#pragma once

#include "cpn_function_module.h"
#include "cpn_number_vector_space.h"

namespace cpn
{
namespace detail
{

template<typename Im, typename Dom>
function_set<Im,Dom> resolve_function_category(const Im&, const Dom&);
template<additive_component_wise_type Im,set_type Dom>
function_group<Im,Dom> resolve_function_category(const Im&,const Dom&);
template<multiplicative_component_wise_type Im,set_type Dom>
function_module<Im,Dom> resolve_function_category(const Im&,const Dom&);

}

template<set_type Im,set_type Dom>
using F = decltype(detail::resolve_function_category(std::declval<Im>(),std::declval<Dom>()));

template<set_type T>
using Endo = F<T,T>;
template<size_t Dim>
using EndoR = F<R_n<Dim>,R_n<Dim>>;
template<size_t Dim, size_t DDim>
using FR = F<R_n<Dim>,R_n<DDim>>;

}