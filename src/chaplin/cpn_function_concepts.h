#pragma once

#include "cpn_expression_inspector.h"

#define IS_INSTANTIABLE_COND(_TYPE) \
	cpn::concepts::is_instantiable<_TYPE>
#define IS_INSTANTIABLE(_TYPE) \
	typename std::enable_if<IS_INSTANTIABLE_COND(_TYPE)>::type
#define IS_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM) \
	cpn::concepts::is_instantiable_by<_TYPE,_IM,_DOM>
#define IS_INSTANTIABLE_BY(_TYPE,_IM,_DOM) \
	typename std::enable_if<IS_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM)>::type
#define IS_LINEAR_INSTANTIABLE_COND(_TYPE) \
	cpn::inspect_linearity<_TYPE> && IS_INSTANTIABLE_COND(_TYPE)
#define IS_LINEAR_INSTANTIABLE(_TYPE) \
	typename std::enable_if<IS_LINEAR_INSTANTIABLE_COND(_TYPE)>::type
#define IS_LINEAR_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM) \
	cpn::inspect_linearity<_TYPE> && IS_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM)
#define IS_LINEAR_INSTANTIABLE_BY(_TYPE,_IM,_DOM) \
	typename std::enable_if<IS_LINEAR_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM)>::type

namespace cpn
{
namespace concepts
{

template<typename T>
std::false_type is_instantiable_resolver(const T&,...);
template<typename T>
std::true_type is_instantiable_resolver(T&, const typename T::__instantiable_tag* = nullptr);

template<typename T>
inline constexpr bool is_instantiable = decltype(is_instantiable_resolver(std::declval<T&>()))::value;

std::false_type is_instantiable_by_resolver(...);
template<typename T, typename Im, typename ... Dom, typename = decltype(std::declval<T>().template instance<Im,Dom...>())>
std::true_type is_instantiable_by_resolver(T&, const Im&, const ddk::mpl::type_pack<Dom...>&);

template<typename T, typename Im, typename Dom>
inline constexpr bool is_instantiable_by = decltype(is_instantiable_by_resolver(std::declval<T&>(),std::declval<Im>(),std::declval<Dom>()))::value;

}
}
