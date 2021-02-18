#pragma once

#define IS_INSTANTIABLE(_TYPE) \
	typename std::enable_if<cpn::concepts::is_instantiable<_TYPE>>::type
#define IS_INSTANTIABLE_COND(_TYPE) \
	cpn::concepts::is_instantiable<_TYPE>
#define IS_INSTANTIABLE_BY(_TYPE,_IM,_DOM) \
	typename std::enable_if<cpn::concepts::is_instantiable_by<_TYPE,_IM,_DOM>>::type
#define IS_LINEAR_INSTANTIABLE(_TYPE) \
	IS_INSTANTIABLE(_TYPE)
#define IS_LINEAR_INSTANTIABLE_BY(_TYPE,_IM,_DOM) \
	IS_INSTANTIABLE_BY(_TYPE,_IM,_DOM)

namespace cpn
{
namespace concepts
{

template<typename T>
std::false_type is_instantiable_resolver(const T&,...);
template<typename T,typename = typename T::___instantiable_tag>
std::true_type is_instantiable_resolver(T&);

template<typename T>
inline constexpr bool is_instantiable = decltype(is_instantiable_resolver(std::declval<T&>()))::value;

std::false_type is_instantiable_by_resolver(...);
template<typename T, typename Im, typename ... Dom, typename = decltype(std::declval<T>().template instance<Im,Dom...>())>
std::true_type is_instantiable_by_resolver(T&, const Im&, const ddk::mpl::type_pack<Dom...>&);

template<typename T, typename Im, typename Dom>
inline constexpr bool is_instantiable_by = decltype(is_instantiable_by_resolver(std::declval<T&>(),std::declval<Im>(),std::declval<Dom>()))::value;

}
}