#pragma once

#include "cpn_function_concepts.h"
#include "ddk_concepts.h"

namespace cpn
{

template<typename Im, typename Dom, typename T>
inline ddk::detail::builtin_number_function<Im,Dom> instance_as_function(const builtin_numeric_expression<T>& i_exp);
template<typename Im,typename Dom,size_t Comp>
inline ddk::detail::builtin_component_function<Im,Dom> instance_as_function(const component_builtin_expression<Comp>& i_exp);
template<typename Im,typename Dom,typename Expression>
inline ddk::detail::builtin_inverted_function<Im,Dom> instance_as_function(const builtin_inverted_expression<Expression>& i_exp);
template<typename Im,typename Dom, size_t ...Indexs, typename ... Expressions>
inline ddk::detail::builtin_add_nary_functor<Im,Dom> instance_as_function(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp);
template<typename Im,typename Dom,size_t ...Indexs,typename ... Expressions>
inline ddk::detail::builtin_prod_nary_functor<Im,Dom> instance_as_function(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp);
TEMPLATE(typename Im,typename Dom, typename LhsExpression, typename RhsExpression)
REQUIRES(IS_INSTANTIABLE(LhsExpression),IS_INSTANTIABLE(RhsExpression))
inline ddk::detail::builtin_composed_function<Im,Dom> instance_as_function(const builtin_composed_expression<LhsExpression,RhsExpression>& i_exp);
TEMPLATE(typename Im,typename Dom,typename T)
REQUIRES(IS_INSTANTIABLE(T))
inline auto instance_as_function(const T& i_exp);

template<typename Im,typename Dom>
inline bool operator==(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline bool operator!=(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline function<Im(Dom)> operator+(const function<Im(Dom)>& i_lhs, const function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline function<Im(Dom)> operator-(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline function<Im(Dom)> operator*(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline function<Im(Dom)> operator/(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs);
//linear versions
template<typename Im,typename Dom>
inline linear_function<Im(Dom)> operator+(const linear_function<Im(Dom)>& i_lhs,const linear_function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline linear_function<Im(Dom)> operator-(const linear_function<Im(Dom)>& i_lhs,const linear_function<Im(Dom)>& i_rhs);
template<typename Im,typename Dom>
inline auto operator*(const linear_function<Im(Dom)>& i_lhs,const linear_function<Im(Dom)>& i_rhs);

}

namespace ddk
{
namespace detail
{

TEMPLATE(typename T,typename TT)
REQUIRES(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
inline bool operator==(const T& i_lhs,const TT& i_rhs);
TEMPLATE(typename T,typename TT)
REQUIRES(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
inline bool operator!=(const T& i_lhs,const TT& i_rhs);

template<cpn::closed_additive_type Im,typename ... Dom>
inline auto operator+(const ddk::detail::builtin_number_function<Im,Dom...>& i_lhs, const ddk::detail::builtin_number_function<Im,Dom...>& i_rhs);
template<typename Im,typename ... Dom>
inline auto operator+(const ddk::detail::builtin_number_function<Im,Dom...>& i_lhs,const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs);
template<typename Im,typename ... Dom>
inline auto operator+(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs,const ddk::detail::builtin_number_function<Im,Dom...>& i_rhs);
template<typename T, typename Im, typename ... Dom>
inline auto operator+(const T& i_lhs, const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs);
template<typename T,typename Im,typename ... Dom>
inline auto operator+(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs, const T& i_rhs);
template<typename Im,typename ... Dom>
inline auto operator+(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs,const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs);
TEMPLATE(typename T, typename TT)
REQUIRES(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
inline auto operator+(const T& i_lhs, const TT& i_rhs);

template<cpn::closed_additive_type Im,typename ... Dom>
inline auto operator*(const ddk::detail::builtin_number_function<Im,Dom...>& i_lhs,const ddk::detail::builtin_number_function<Im,Dom...>& i_rhs);
template<typename T,typename Im,typename ... Dom>
inline auto operator*(const T& i_lhs,const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs);
template<typename T,typename Im,typename ... Dom>
inline auto operator*(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs,const T& i_rhs);
template<typename T,typename Im,typename ... Dom>
inline auto operator*(const T& i_lhs,const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_rhs);
template<typename T,typename Im,typename ... Dom>
inline auto operator*(const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_lhs,const T& i_rhs);
template<typename Im,typename ... Dom>
inline auto operator*(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs,const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs);
template<typename Im,typename ... Dom>
inline auto operator*(const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_lhs,const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_rhs);
TEMPLATE(typename T,typename TT)
REQUIRES(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
inline auto operator*(const T& i_lhs,const TT& i_rhs);

}
}

#include "cpn_builtin_function_ops.inl"