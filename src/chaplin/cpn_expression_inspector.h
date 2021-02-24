#pragma once

#include "cpn_builtin_functions.h"

namespace cpn
{

template<typename T>
std::false_type linearity_inspection(const T&, ...);

template<typename T>
inline constexpr bool inspect_linearity = decltype(linearity_inspection(std::declval<T>()))::value;

template<typename LhsFunction, typename RhsFunction>
typename ddk::mpl::static_if<inspect_linearity<LhsFunction> && inspect_linearity<RhsFunction>,std::true_type,std::false_type>::type linearity_inspection(const ddk::detail::add_binary_template_functor<LhsFunction,RhsFunction>&);

template<typename LhsFunction,typename RhsFunction>
typename ddk::mpl::static_if<inspect_linearity<LhsFunction> && inspect_linearity<RhsFunction>,std::true_type,std::false_type>::type linearity_inspection(const ddk::detail::prod_binary_template_functor<LhsFunction,RhsFunction>&);

template<typename LhsFunction,typename RhsFunction>
typename ddk::mpl::static_if<inspect_linearity<LhsFunction>&& inspect_linearity<RhsFunction>,std::true_type,std::false_type>::type linearity_inspection(const ddk::detail::builtin_composed_template_function<LhsFunction,RhsFunction>&);

template<typename T, typename TT = typename T::__instantiable_properties>
typename ddk::mpl::static_if<T::__instantiable_properties::template contains(ddk::mpl::type_pack<linear>{}),std::true_type,std::false_type> linearity_inspection(const T&, ...);

}
