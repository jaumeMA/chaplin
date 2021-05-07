#pragma once

#include "cpn_type_concepts.h"
#include "cpn_algebraic_defs.h"
#include "cpn_expression_concepts.h"
#include "ddk_concepts.h"
#include "ddk_type_concepts.h"
#include "ddk_tuple.h"
#include "ddk_iterable.h"
#include "ddk_callable.h"


#define DEFINE_ARITHMETIC_NARY_EXPRESSION(_NAME,_OP) \
template<typename, typename ...> \
struct _NAME##_nary_expression; \
template<size_t ... Indexs, typename ... Expressions> \
struct _NAME##_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...> \
{ \
    template<size_t ... IIndexs, typename ... EExpressions> \
    friend constexpr auto operator&&(const _NAME##_nary_expression& i_lhs, const _NAME##_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs) \
    { \
        return i_lhs.combine(i_rhs); \
    } \
    template<typename,typename ...> \
    friend struct _NAME##_nary_expression; \
    typedef void __instantiable_tag; \
    typedef ddk::mpl::type_pack<> __expression_properties; \
    constexpr _NAME##_nary_expression() = default; \
    constexpr _NAME##_nary_expression(const ddk::tuple<Expressions...>& i_exps) \
    : m_expressions(i_exps) \
    { \
    } \
    constexpr _NAME##_nary_expression(ddk::tuple<Expressions...>&& i_exps) \
    : m_expressions(i_exps) \
    { \
    } \
    constexpr _NAME##_nary_expression(const Expressions& ... i_exps) \
    : m_expressions(i_exps...) \
    { \
    } \
    template<size_t Index> \
    constexpr auto get() const \
    { \
        return m_expressions.template get<Index>(); \
    } \
    template<typename Callable> \
    constexpr void enumerate(Callable&& i_callable) const \
    { \
        ddk::deduce_callable(i_callable) <<= m_expressions; \
    } \
    template<typename Callable> \
    constexpr auto apply(Callable&& i_callable) const \
    { \
        return _NAME##_nary_expression<ddk::mpl::sequence<Indexs...>,decltype(i_callable(m_expressions.template get<Indexs>()))...>(i_callable(m_expressions.template get<Indexs>()) ...); \
    } \
    template<size_t ... IIndexs> \
    constexpr auto truncate() const \
    { \
        return _NAME##_nary_expression<ddk::mpl::sequence<IIndexs...>,ddk::mpl::nth_type_of_t<IIndexs,Expressions...>...>(m_expressions.template get<IIndexs>()...); \
    } \
    template<typename Expression> \
    constexpr auto combine(const Expression& i_exp) const \
    { \
        typedef typename ddk::mpl::make_sequence<0,ddk::mpl::num_ranks<Indexs...>+1>::type total_sequence; \
        \
        return _NAME##_nary_expression<total_sequence,Expressions...,Expression>(ddk::merge_args<Expressions...,Expression>(total_sequence{},total_sequence{},m_expressions,i_exp)); \
    } \
    template<size_t Pos, size_t ... IIndexs, typename Expression> \
    constexpr auto combine(const ddk::mpl::sequence<IIndexs...>&, const Expression& i_exp) const \
    { \
        typedef typename ddk::mpl::merge_sequence<ddk::mpl::sequence<IIndexs...>,ddk::mpl::sequence<Pos>>::type total_sequence; \
        return ddk::make_indexed_tuple(total_sequence{},m_expressions.template get<IIndexs>()...,i_exp); \
    } \
    template<size_t Pos, typename Expression> \
    constexpr auto combine(const Expression& i_exp) const \
    { \
        static_assert(std::is_same<Expression,ddk::mpl::nth_type_of_t<Pos,Expressions...>>::value, "Type mismatch between old and new value."); \
        typedef typename ddk::mpl::sequence<Indexs...>::template drop<Pos> non_pos_sequence_t; \
        \
        return combine<Pos>(non_pos_sequence_t{},i_exp); \
    } \
    template<size_t ... IIndexs, typename ... EExpressions> \
    constexpr auto combine(const _NAME##_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_exp) const \
    { \
        typedef typename ddk::mpl::make_sequence<0,ddk::mpl::num_ranks<Indexs...> + ddk::mpl::num_ranks<IIndexs...>>::type total_sequence; \
        \
        return _NAME##_nary_expression<total_sequence,Expressions...,EExpressions...>(ddk::merge_args<Expressions...,EExpressions...>(total_sequence{},total_sequence{},m_expressions,i_exp.m_expressions.template get<IIndexs>()...)); \
    } \
private: \
    const ddk::tuple<Expressions...> m_expressions; \
}; \
template<typename ... T> \
_NAME##_nary_expression(const T& ... i_args) -> _NAME##_nary_expression<typename ddk::mpl::make_sequence<0,ddk::mpl::num_types<T...>>::type,T...>; \
template<typename ... T> \
_NAME##_nary_expression(const ddk::tuple<T...>&)->_NAME##_nary_expression<typename ddk::mpl::make_sequence<0,ddk::mpl::num_types<T...>>::type,T...>;

#define DEFINE_BUILTIN_EXPRESSION(_NAME,...) \
struct _NAME##_builtin_expression \
{ \
    typedef void __instantiable_tag; \
    typedef ddk::mpl::type_pack<__VA_ARGS__> __expression_properties; \
    constexpr _NAME##_builtin_expression() = default; \
    template<typename T> \
    constexpr builtin_composed_expression<_NAME##_builtin_expression,T> operator()(const T& other) const \
    { \
        return { *this, other }; \
    } \
}; \
constexpr _NAME##_builtin_expression _NAME = _NAME##_builtin_expression();

namespace cpn
{

template<typename Expression>
struct builtin_inverted_expression
{
    typedef void __instantiable_tag;

    constexpr builtin_inverted_expression() = default;
    constexpr builtin_inverted_expression(const Expression& i_exp);

    constexpr const Expression& get() const;

private:
    const Expression m_exp;
};
template<typename Expression>
builtin_inverted_expression(const Expression&) -> builtin_inverted_expression<Expression>;

template<typename LhsFunction,typename RhsFunction>
struct builtin_composed_expression
{
    typedef void __instantiable_tag;
    constexpr builtin_composed_expression() = default;
    constexpr builtin_composed_expression(const LhsFunction& i_lhs,const RhsFunction& i_rhs);

    constexpr const LhsFunction& get_lhs() const;
    constexpr const RhsFunction& get_rhs() const;

private:
    const LhsFunction m_lhs;
    const RhsFunction m_rhs;
};

template<typename T>
struct builtin_numeric_expression
{
    static_assert(std::is_arithmetic_v<T>,"You shall use numeric types for this kind of template function");

    typedef void __instantiable_tag;
    typedef ddk::mpl::type_pack<linear,cnstant> __expression_properties;

    constexpr builtin_numeric_expression() = default;
    constexpr builtin_numeric_expression(const T& i_number);
    constexpr const T& get() const;

private:
    const T m_number = 0;
};

template<size_t Comp>
struct component_builtin_expression
{
    typedef void __instantiable_tag;
    typedef ddk::mpl::type_pack<cpn::incognita,cpn::linear> __expression_properties;
    constexpr component_builtin_expression() = default;
    constexpr component_builtin_expression(const component_builtin_expression&) = default;
    constexpr component_builtin_expression(component_builtin_expression&&) = default;
    TEMPLATE(typename T)
    REQUIRES(IS_INSTANTIABLE(T))
    constexpr builtin_composed_expression<component_builtin_expression,T> operator()(const T & other) const;
};

//predfined nary arithmetic operators
DEFINE_ARITHMETIC_NARY_EXPRESSION(add,+);
DEFINE_ARITHMETIC_NARY_EXPRESSION(subs,-);
DEFINE_ARITHMETIC_NARY_EXPRESSION(prod,*);
DEFINE_ARITHMETIC_NARY_EXPRESSION(div,/);

//predefined math functions
DEFINE_BUILTIN_EXPRESSION(sin);
DEFINE_BUILTIN_EXPRESSION(cos);
DEFINE_BUILTIN_EXPRESSION(tan);


constexpr component_builtin_expression<0> x = component_builtin_expression<0>();
constexpr component_builtin_expression<0> x_0 = component_builtin_expression<0>();
constexpr component_builtin_expression<1> x_1 = component_builtin_expression<1>();
constexpr component_builtin_expression<2> x_2 = component_builtin_expression<2>();
constexpr component_builtin_expression<3> x_3 = component_builtin_expression<3>();
constexpr component_builtin_expression<4> x_4 = component_builtin_expression<4>();
constexpr component_builtin_expression<5> x_5 = component_builtin_expression<5>();
constexpr component_builtin_expression<6> x_6 = component_builtin_expression<6>();
constexpr component_builtin_expression<7> x_7 = component_builtin_expression<7>();
constexpr component_builtin_expression<8> x_8 = component_builtin_expression<8>();
constexpr component_builtin_expression<9> x_9 = component_builtin_expression<9>();

}

#include "cpn_builtin_expressions.inl"
#include "cpn_builtin_expression_ops.h"
#include "cpn_expression_inspector.h"
