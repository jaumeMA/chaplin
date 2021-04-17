#pragma once

#include "ddk_concepts.h"
#include "ddk_type_concepts.h"

namespace cpn
{

template<typename T>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_exp);
template<size_t Comp>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_exp);
template<typename ... Expressions>
constexpr  auto operator-(const add_nary_expression<Expressions...>& i_exp);
template<typename ... Expressions>
constexpr  auto operator-(const prod_nary_expression<Expressions...>& i_exp);
TEMPLATE(typename T)
REQUIRES(IS_INSTANTIABLE(T))
constexpr auto operator-(const T& i_exp);

template<typename T>
constexpr  auto operator+(const builtin_numeric_expression<T>& i_lhs, const builtin_numeric_expression<T>& i_rhs);
TEMPLATE(typename T,typename TT)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr auto operator+(const builtin_numeric_expression<T>& i_lhs,const T& i_rhs);
TEMPLATE(typename T,typename TT)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr auto operator+(const T& i_lhs,const builtin_numeric_expression<TT>& i_rhs);
template<typename T, size_t Comp>
constexpr  auto operator+(const builtin_numeric_expression<T>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<typename T,size_t Comp>
constexpr  auto operator+(const component_builtin_expression<Comp>& i_lhs, const builtin_numeric_expression<T>& i_rhs);
template<size_t Comp1, size_t Comp2>
constexpr  auto operator+(const component_builtin_expression<Comp1>& i_lhs, const component_builtin_expression<Comp2>& i_rhs);
TEMPLATE(typename T,size_t Comp)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const T& i_lhs,const component_builtin_expression<Comp>& i_rhs);
TEMPLATE(typename T,size_t Comp)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const component_builtin_expression<Comp>& i_lhs,const T& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const T& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs);
template<typename T, size_t ... Indexs, typename ... Expressions>
constexpr  auto operator+(const builtin_numeric_expression<T>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<typename T, size_t ... Indexs, typename ... Expressions>
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const T& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const builtin_numeric_expression<T>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
template<size_t Comp, size_t ... Indexs, typename ... Expressions>
constexpr  auto operator+(const component_builtin_expression<Comp>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<size_t Comp, size_t ... Indexs, typename ... Expressions>
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<size_t ... Indexs, typename ... Expressions, size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const component_builtin_expression<Comp>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator+(const Expression& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator+(const builtin_inverted_expression<Expression>& i_lhs,const EExpression& i_rhs);
template<typename Expression, typename EExpression>
constexpr  auto operator+(const builtin_inverted_expression<Expression>& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs);
TEMPLATE(typename T,typename TT)
REQUIRES_COND((IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T)) && (IS_NUMERIC_COND(TT) || IS_INSTANTIABLE_COND(TT)))
constexpr auto operator+(const T& i_lhs,const TT& i_rhs);

template<typename T>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
TEMPLATE(typename T,size_t Comp)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator-(const T& i_lhs,const component_builtin_expression<Comp>& i_rhs);
TEMPLATE(typename T,size_t Comp)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const T& i_rhs);
template<typename T,size_t Comp>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<typename T,size_t Comp>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
template<size_t Comp1,size_t Comp2>
constexpr  auto operator-(const component_builtin_expression<Comp1>& i_lhs,const component_builtin_expression<Comp2>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator-(const T& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator-(const T& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<size_t ... Indexs,typename ... Expressions, size_t ... IIndexs, typename ... EExpressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator-(const Expression& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator-(const builtin_inverted_expression<Expression>& i_lhs,const EExpression& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator-(const builtin_inverted_expression<Expression>& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs);

template<typename T>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
TEMPLATE(typename T,size_t Comp)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator*(const T& i_lhs,const component_builtin_expression<Comp>& i_rhs);
TEMPLATE(typename T,size_t Comp)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const T& i_rhs);
template<typename T,size_t Comp>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<typename T,size_t Comp>
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
template<size_t Comp1,size_t Comp2>
constexpr  auto operator*(const component_builtin_expression<Comp1>& i_lhs,const component_builtin_expression<Comp2>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator*(const T& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator*(const T& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRES(IS_NUMERIC(T))
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs);
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs);
template<size_t ... Indexs,typename ... Expressions, size_t ... IIndexs, typename ... EExpressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator*(const Expression& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator*(const builtin_inverted_expression<Expression>& i_lhs,const EExpression& i_rhs);
template<typename Expression,typename EExpression>
constexpr  auto operator*(const builtin_inverted_expression<Expression>& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs);

}

#include "cpn_builtin_expression_ops.inl"