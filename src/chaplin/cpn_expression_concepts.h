#pragma once

#define IS_INSTANTIABLE_COND(_TYPE) \
	cpn::concepts::is_instantiable<_TYPE>
#define IS_INSTANTIABLE(_TYPE) \
	typename std::enable_if<IS_INSTANTIABLE_COND(_TYPE)>::type

namespace cpn
{
namespace concepts
{

std::false_type is_instantiable_resolver(...);
template<typename T, typename = typename T::__instantiable_tag>
std::true_type is_instantiable_resolver(T&);

template<typename T>
inline constexpr bool is_instantiable = decltype(is_instantiable_resolver(std::declval<T&>()))::value;

}
}
