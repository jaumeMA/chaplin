#pragma once

#define IS_INSTANTIABLE_COND(_TYPE) \
	cpn::concepts::is_instantiable<_TYPE>
#define IS_INSTANTIABLE(_TYPE) \
	typename std::enable_if<IS_INSTANTIABLE_COND(_TYPE)>::type

namespace cpn
{
namespace concepts
{

template<typename T>
std::false_type is_instantiable_resolver(const T&,...);
template<typename T>
std::true_type is_instantiable_resolver(T&,const typename T::__instantiable_tag* = nullptr);

template<typename T>
inline constexpr bool is_instantiable = decltype(is_instantiable_resolver(std::declval<T&>()))::value;

}
}