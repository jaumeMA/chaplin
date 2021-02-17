#pragma once

#define IS_INSTANTIABLE(_TYPE) \
	decltype(std::declval<ddk::mpl::remove_qualifiers<_TYPE>>().template instance<int,int>())
#define IS_INSTANTIABLE_COND(_TYPE) \
	cpn::concepts::is_instantiable<_TYPE>
#define IS_INSTANTIABLE_BY(_TYPE,...) \
	decltype(std::declval<ddk::mpl::remove_qualifiers<_TYPE>>().template instance<__VA_ARGS__>())
#define IS_LINEAR_INSTANTIABLE(_TYPE) \
	IS_INSTANTIABLE(_TYPE)
#define IS_LINEAR_INSTANTIABLE_BY(_TYPE,...) \
	IS_INSTANTIABLE_BY(_TYPE,##__VA_ARGS__)

namespace cpn
{
namespace concepts
{

template<typename T>
std::false_type is_instantiable_resolver(const T&, ...);
template<typename T, typename = decltype(std::declval<T>().template instance<int,int>())>
std::true_type is_instantiable_resolver(T&);

template<typename T, typename ... TT>
inline constexpr bool is_instantiable = decltype(is_instantiable_resolver(std::declval<T&>()))::value;

}
}