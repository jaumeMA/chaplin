#pragma once

#define IS_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM) \
	cpn::concepts::is_instantiable_by<_TYPE,_IM,_DOM>
#define IS_INSTANTIABLE_BY(_TYPE,_IM,_DOM) \
	typename std::enable_if<IS_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM)>::type
#define IS_LINEAR_INSTANTIABLE_COND(_TYPE) \
	IS_INSTANTIABLE_COND(_TYPE)
#define IS_LINEAR_INSTANTIABLE(_TYPE) \
	typename std::enable_if<IS_LINEAR_INSTANTIABLE_COND(_TYPE)>::type
#define IS_LINEAR_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM) \
	IS_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM) && cpn::inspect_linearity<_TYPE>
#define IS_LINEAR_INSTANTIABLE_BY(_TYPE,_IM,_DOM) \
	typename std::enable_if<IS_LINEAR_INSTANTIABLE_BY_COND(_TYPE,_IM,_DOM)>::type
#define IS_BUILTIN_FUNCTION(_TYPE) \
	typename std::enable_if<cpn::concepts::is_builtin_function<_TYPE>>::type

namespace cpn
{

//this is just a misery way of publishing this symbol
template<typename Im,typename Dom>
typename std::enable_if<sizeof(Im)==0>::type instance_as_function(...);

namespace concepts
{

std::false_type is_instantiable_by_resolver(...);
template<typename T, typename Im, typename Dom>
std::true_type is_instantiable_by_resolver(T&, const Im&, const Dom&, decltype(instance_as_function<Im,Dom>(std::declval<T>()))* = nullptr);

template<typename T, typename Im, typename Dom>
inline constexpr bool is_instantiable_by = decltype(is_instantiable_by_resolver(std::declval<T&>(),std::declval<Im>(),std::declval<Dom>()))::value;

template<typename T>
std::true_type is_builtin_function_impl(T&, typename T::__builtin_function_tag* = nullptr);
template<typename T>
std::false_type is_builtin_function_impl(const T&, ...);

template<typename T>
inline constexpr bool is_builtin_function = decltype(is_builtin_function_impl(std::declval<T&>()))::value;

}
}
