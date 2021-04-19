#pragma once

namespace cpn
{

constexpr bool linearity_inspection(...);

template<size_t ... Indexs, typename ... Expressions>
constexpr bool linearity_inspection(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>&);

template<size_t ... Indexs,typename ... Expressions>
constexpr bool linearity_inspection(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>&);

template<typename LhsFunction,typename RhsFunction>
constexpr bool linearity_inspection(const builtin_composed_expression<LhsFunction,RhsFunction>&);

template<typename Expression>
constexpr bool linearity_inspection(const builtin_inverted_expression<Expression>&);

template<typename T, typename TT = typename T::__expression_properties>
constexpr bool linearity_inspection(const T&);

template<typename T>
constexpr bool inspect_linearity = linearity_inspection(T{});

constexpr bool linearity_inspection(...);

template<size_t ... Indexs,typename ... Expressions>
constexpr bool constant_inspection(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>&);

template<size_t ... Indexs,typename ... Expressions>
constexpr bool constant_inspection(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>&);

template<typename LhsFunction,typename RhsFunction>
constexpr bool constant_inspection(const builtin_composed_expression<LhsFunction,RhsFunction>&);

template<typename Expression>
constexpr bool constant_inspection(const builtin_inverted_expression<Expression>&);

template<typename T,typename TT = typename T::__expression_properties>
constexpr bool constant_inspection(const T&);

template<typename T>
constexpr bool inspect_constant = constant_inspection(T{});

}

#include "cpn_expression_inspector.inl"