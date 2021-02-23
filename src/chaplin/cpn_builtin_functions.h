#pragma once

#include "ddk_rtti.h"
#include "cpn_function.h"
#include "cpn_math_functions.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
#include "ddk_projection_callable.h"
#include "ddk_intersection_function.h"

#define DEFINE_ARITHMETIC_UNARY_OPERATION(_NAME,_OP,_CONCEPT) \
namespace ddk \
{ \
namespace detail \
{ \
 \
template<_CONCEPT,typename> \
struct _NAME##_unary_functor; \
template<_CONCEPT ImSet, typename ... Dom> \
struct _NAME##_unary_functor<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom...> \
{ \
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_t; \
    \
public: \
    _NAME##_unary_functor(const function_t & i_rhs) \
    : m_rhs(i_rhs) \
    { \
    } \
    _NAME##_unary_functor(const _NAME##_unary_functor& other) \
    : m_rhs(other.m_rhs) \
    { \
    } \
    _NAME##_unary_functor(_NAME##_unary_functor&& other) \
    : m_rhs(std::move(other.m_rhs)) \
    { \
    } \
    \
    ImSet operator()(Dom ... i_args) const \
    { \
        return ImSet{}; \
    } \
    const function_t& get_rhs() const \
    { \
        return m_rhs; \
    } \
    \
private: \
    function_t m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_unary_functor,function_impl_base); \
template<typename Im, typename ... Dom> \
_NAME##_unary_functor(const cpn::function_impl<Im(mpl::type_pack<Dom...>)>&) -> _NAME##_unary_functor<Im,mpl::type_pack<Dom...>>; \
template<typename RhsFunction> \
struct _NAME##_unary_template_functor \
{ \
    struct ___instantiable_tag; \
    constexpr _NAME##_unary_template_functor(const RhsFunction& i_rhs) \
    : m_rhs(i_rhs) \
    { \
    } \
    template<typename Type,typename ... Types> \
    constexpr inline _NAME##_unary_functor<Type,mpl::type_pack<Types...>> instance() const \
    { \
        return { m_rhs.template instance<Type,Types...>() }; \
    } \
private: \
    const RhsFunction m_rhs; \
}; \
 \
} \
}

#define DEFINE_ARITHMETIC_BINARY_OPERATION(_NAME,_OP,_CONCEPT) \
namespace ddk \
{ \
namespace detail \
{ \
 \
template<_CONCEPT,typename> \
struct _NAME##_binary_functor; \
template<_CONCEPT ImSet, typename ... Dom> \
struct _NAME##_binary_functor<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom ...> \
{ \
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_t; \
        \
public: \
    _NAME##_binary_functor(const function_t& i_lhs, const function_t& i_rhs) \
    : m_lhs(i_lhs) \
    , m_rhs(i_rhs) \
    { \
    } \
    _NAME##_binary_functor(const _NAME##_binary_functor& other) \
    : m_lhs(other.m_lhs) \
    , m_rhs(other.m_rhs) \
    { \
    } \
    _NAME##_binary_functor(_NAME##_binary_functor&& other) \
    : m_lhs(std::move(other.m_lhs)) \
    , m_rhs(std::move(other.m_rhs)) \
    { \
    } \
    \
    ImSet operator()(Dom ... i_args) const \
    { \
        return { ddk::eval(m_lhs,std::forward<Dom>(i_args)...) _OP ddk::eval(m_rhs,std::forward<Dom>(i_args)...) }; \
    } \
    const function_t& get_lhs() const \
    { \
        return m_lhs; \
    } \
    const function_t& get_rhs() const \
    { \
        return m_rhs; \
    } \
\
private: \
    function_t m_lhs; \
    function_t m_rhs; \
} PUBLISH_RTTI_INHERITANCE(_NAME##_binary_functor,function_impl_base); \
template<typename Im, typename ... Dom> \
_NAME##_binary_functor(const cpn::function_impl<Im(mpl::type_pack<Dom...>)>&,const cpn::function_impl<Im(mpl::type_pack<Dom...>)>&) -> _NAME##_binary_functor<Im,mpl::type_pack<Dom...>>; \
template<typename LhsFunction, typename RhsFunction> \
struct _NAME##_binary_template_functor \
{ \
    struct ___instantiable_tag; \
    constexpr _NAME##_binary_template_functor(const LhsFunction& i_lhs, const RhsFunction& i_rhs) \
    : m_lhs(i_lhs) \
    , m_rhs(i_rhs) \
    { \
    } \
    template<typename Type, typename ... Types> \
    constexpr inline _NAME##_binary_functor<Type,mpl::type_pack<Types...>> instance() const \
    { \
        return {m_lhs.template instance<Type,Types...>(),m_rhs.template instance<Type,Types...>() }; \
    } \
private: \
    const LhsFunction m_lhs; \
    const RhsFunction m_rhs; \
}; \
 \
} \
}

#define DEFINE_BUILTIN_FUNCTION_OPERATOR(_NAME,_OP) \
namespace ddk \
{ \
namespace detail \
{ \
 \
TEMPLATE(typename T,typename TT) \
REQUIRES_COND(IS_INSTANTIABLE_COND(T) || IS_INSTANTIABLE_COND(TT)) \
constexpr inline _NAME##_binary_template_functor<decltype(resolve_template_function(std::declval<T>())),decltype(resolve_template_function(std::declval<TT>()))> operator _OP(const T& i_lhs,const TT& i_rhs) \
{ \
    typedef decltype(resolve_template_function(std::declval<T>())) lhs_template_functor; \
    typedef decltype(resolve_template_function(std::declval<TT>())) rhs_template_functor; \
    \
    return { lhs_template_functor(i_lhs),rhs_template_functor(i_rhs) }; \
} \
 \
} \
}

#define DEFINE_BUILTIN_FUNCTION(_NAME,_FUNC,_CONSTRAINT) \
namespace ddk \
{ \
namespace detail \
{ \
 \
template<typename,typename> \
struct _NAME##__builtin_function; \
template<typename ImSet, typename ... Dom> \
struct _NAME##__builtin_function<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom...> \
{ \
    constexpr _NAME##__builtin_function() = default; \
    inline ImSet operator()(Dom... i_args) const \
    { \
        return _FUNC(std::forward<Dom>(i_args)...); \
    } \
}; \
template<typename ImSet, _CONSTRAINT T> \
struct _NAME##_builtin_function : _NAME##__builtin_function<ImSet,T> \
{ \
} PUBLISH_RTTI_INHERITANCE(_NAME##_builtin_function,function_impl_base); \
struct _NAME##_builtin_template_function \
{ \
    struct ___instantiable_tag; \
    constexpr _NAME##_builtin_template_function() = default; \
    template<typename Type,typename ... Types> \
    constexpr inline _NAME##_builtin_function<Type,mpl::type_pack<Types...>> instance() const \
    { \
        return {}; \
    } \
    TEMPLATE(typename T) \
    REQUIRES(IS_INSTANTIABLE(T)) \
    constexpr builtin_composed_template_function<_NAME##_builtin_template_function,T> operator()(const T& other) const \
    { \
        return { *this, other }; \
    } \
}; \
 \
} \
} \
namespace cpn \
{ \
 \
const ddk::detail::_NAME##_builtin_template_function _NAME = ddk::detail::_NAME##_builtin_template_function{}; \
 \
}

namespace ddk
{
namespace detail
{

template<typename Im, typename Callable, typename ... Dom>
constexpr inline cpn::function_impl<Im(ddk::mpl::type_pack<Dom...>)> instantiate_template_callable(Callable&& i_callable, const ddk::mpl::type_pack<Dom...>&);

template<cpn::coordinate_type,typename>
struct builtin_fusioned_function;
template<cpn::coordinate_type ImSet,typename ... Dom>
struct builtin_fusioned_function<ImSet,ddk::mpl::type_pack<Dom...>> : public ddk::detail::inherited_functor_impl<ImSet,Dom...>
{
    template<typename>
    struct fusioned_components;
    template<size_t ... Components>
    struct fusioned_components<ddk::mpl::sequence<Components...>>
    {
        fusioned_components(const ddk::detail::intersection_function<cpn::function_impl<ddk::mpl::nth_coordinate_of_t<Components,ImSet>(mpl::type_pack<Dom...>)>...>& i_callable);

        ddk::detail::intersection_function<cpn::function_impl<ddk::mpl::nth_coordinate_of_t<Components,ImSet>(mpl::type_pack<Dom...>)>...> m_fusionedFunction;
    };

public:
    template<typename ... T>
    builtin_fusioned_function(const ddk::detail::intersection_function<cpn::function_impl<T(mpl::type_pack<Dom...>)>...>& i_args);

    inline ImSet operator()(Dom... i_args) const;
    template<size_t Index>
    inline const cpn::function_impl<ddk::mpl::nth_coordinate_of_t<Index,ImSet>(mpl::type_pack<Dom...>)>& get_callable() const;

private:
    template<size_t ... Indexs>
    inline ImSet execute(const ddk::mpl::sequence<Indexs...>&, Dom ... i_args) const;

    const fusioned_components<typename ddk::mpl::make_sequence<0,ImSet::num_coordinates>::type> m_callables;
} PUBLISH_RTTI_INHERITANCE(builtin_fusioned_function,ddk::detail::function_impl_base);

template<typename,typename>
struct builtin_composed_function;
template<typename ImSet,typename ... Dom>
struct builtin_composed_function<ImSet,ddk::mpl::type_pack<Dom...>> : public ddk::detail::inherited_functor_impl<ImSet,Dom...>
{
    typedef cpn::function_impl<ImSet(ddk::mpl::type_pack<ImSet>)> function_lhs_t;
    typedef cpn::function_impl<ImSet(ddk::mpl::type_pack<Dom...>)> function_rhs_t;

public:
    builtin_composed_function(const function_lhs_t& i_lhs, const function_rhs_t& i_rhs);
    inline ImSet operator()(Dom... i_args) const;

    const function_lhs_t& get_dest_function() const;
    const function_rhs_t& get_source_function() const;

private:
    const function_lhs_t m_lhs;
    const function_rhs_t m_rhs;
} PUBLISH_RTTI_INHERITANCE(builtin_composed_function,ddk::detail::function_impl_base);

template<typename,typename>
struct builtin_number_function;
template<typename ImSet,typename ... Dom>
struct builtin_number_function<ImSet,ddk::mpl::type_pack<Dom...>> : public ddk::detail::inherited_functor_impl<ImSet,Dom...>
{
    typedef cpn::function_impl<ImSet(ddk::mpl::type_pack<Dom...>)> function_t;

public:
    builtin_number_function(const function_t& i_number);
    inline ImSet operator()(Dom... i_args) const;

    const function_t& get_number() const;

private:
    const function_t m_number;
} PUBLISH_RTTI_INHERITANCE(builtin_number_function,ddk::detail::function_impl_base);

template<typename LhsFunction, typename RhsFunction>
struct builtin_composed_template_function
{
    struct ___instantiable_tag;

    constexpr builtin_composed_template_function(const LhsFunction& i_lhs, const RhsFunction& i_rhs);

    template<typename Type,typename ... Types>
    constexpr inline builtin_composed_function<Type,ddk::mpl::type_pack<Types...>> instance() const;

private:
    const LhsFunction m_lhs;
    const RhsFunction m_rhs;
};

template<typename T>
struct builtin_numeric_template_function
{
    static_assert(std::is_arithmetic_v<T>, "You shall use numeric types for this kind of template function");

    struct ___instantiable_tag;

    constexpr builtin_numeric_template_function(const T& i_number);

    template<typename Type,typename ... Types>
    constexpr inline builtin_number_function<Type,ddk::mpl::type_pack<Types...>> instance() const;

private:
    const T m_number;
};

TEMPLATE(typename T)
REQUIRES(IS_INSTANTIABLE(T))
constexpr T resolve_template_function(const T&);
TEMPLATE(typename T)
REQUIRES_COND(std::is_arithmetic_v<T>)
constexpr builtin_numeric_template_function<T> resolve_template_function(const T&);

}
}

//arithmetic operations
DEFINE_ARITHMETIC_UNARY_OPERATION(neg,-,cpn::inverse_additive_component_wise_type);
DEFINE_ARITHMETIC_BINARY_OPERATION(add,+,cpn::additive_component_wise_type);
DEFINE_ARITHMETIC_BINARY_OPERATION(subs,-,cpn::substractive_component_wise_type);
DEFINE_ARITHMETIC_BINARY_OPERATION(prod,*,cpn::multiplicative_component_wise_type);
DEFINE_ARITHMETIC_BINARY_OPERATION(div,/,cpn::divisible_component_wise_type);

//predefined math functions
DEFINE_BUILTIN_FUNCTION(sin,cpn::detail::sin,cpn::type_pack_args_equal_to_1);
DEFINE_BUILTIN_FUNCTION(cos,cpn::detail::cos,cpn::type_pack_args_equal_to_1);
DEFINE_BUILTIN_FUNCTION(tan,cpn::detail::tan,cpn::type_pack_args_equal_to_1);
DEFINE_BUILTIN_FUNCTION(x,ddk::projection<0>,cpn::type_pack_args_more_or_equal_to_1);
DEFINE_BUILTIN_FUNCTION(x_0,ddk::projection<0>,cpn::type_pack_args_more_or_equal_to_1);
DEFINE_BUILTIN_FUNCTION(x_1,ddk::projection<1>,cpn::type_pack_args_more_or_equal_to_2);
DEFINE_BUILTIN_FUNCTION(x_2,ddk::projection<2>,cpn::type_pack_args_more_or_equal_to_3);
DEFINE_BUILTIN_FUNCTION(x_3,ddk::projection<3>,cpn::type_pack_args_more_or_equal_to_4);
DEFINE_BUILTIN_FUNCTION(x_4,ddk::projection<4>,cpn::type_pack_args_more_or_equal_to_5);
DEFINE_BUILTIN_FUNCTION(x_5,ddk::projection<5>,cpn::type_pack_args_more_or_equal_to_6);
DEFINE_BUILTIN_FUNCTION(x_6,ddk::projection<6>,cpn::type_pack_args_more_or_equal_to_7);
DEFINE_BUILTIN_FUNCTION(x_7,ddk::projection<7>,cpn::type_pack_args_more_or_equal_to_8);
DEFINE_BUILTIN_FUNCTION(x_8,ddk::projection<8>,cpn::type_pack_args_more_or_equal_to_9);
DEFINE_BUILTIN_FUNCTION(x_9,ddk::projection<9>,cpn::type_pack_args_more_or_equal_to_10);

DEFINE_BUILTIN_FUNCTION_OPERATOR(add,+)
DEFINE_BUILTIN_FUNCTION_OPERATOR(subs,-)
DEFINE_BUILTIN_FUNCTION_OPERATOR(prod,*)
DEFINE_BUILTIN_FUNCTION_OPERATOR(div,/ )


#include "cpn_builtin_functions.inl"
