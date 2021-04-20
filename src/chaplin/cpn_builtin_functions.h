#pragma once

#include "cpn_function_impl.h"
#include "cpn_math_functions.h"
#include "cpn_function_concepts.h"
#include "cpn_algebraic_defs.h"
#include "cpn_function_template_helper.h"
#include "cpn_builtin_expressions.h"
#include "ddk_rtti.h"
#include "ddk_concepts.h"
#include "ddk_projection_callable.h"
#include "ddk_constant_callable.h"
#include "ddk_intersection_function.h"
#include "ddk_tuple.h"
#include "ddk_function_exceptions.h"
#include "ddk_dynamic_callable.h"
#include "ddk_dynamic_multivisitor.h"
#include <vector>

#define DEFINE_ARITHMETIC_NARY_OPERATION(_NAME,_OP,_CONCEPT) \
namespace ddk \
{ \
namespace detail \
{ \
 \
template<_CONCEPT,typename> \
struct builtin_##_NAME##_nary_functor; \
template<_CONCEPT ImSet, typename ... Dom> \
struct builtin_##_NAME##_nary_functor<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom ...> \
{ \
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_t; \
    friend inline size_t hash(const builtin_##_NAME##_nary_functor& i_function) \
    { \
        static const rtti::TypeInfo s_typeHash = rtti::type_info<builtin_##_NAME##_nary_functor<ImSet,mpl::type_pack<Dom...>>,function_impl_base<ImSet,mpl::type_pack<Dom...>>>(); \
        commutative_builtin_hasher _hasher(s_typeHash); \
        const auto nestedHasher = dynamic_callable<size_t,function_impl_base<ImSet,mpl::type_pack<Dom...>>>([&_hasher](auto&& i_nestedFunction) -> size_t { return _hasher(i_nestedFunction); }); \
        \
        for(auto operand : i_function.m_functions) \
        { \
            visit(nestedHasher,operand); \
        } \
        \
        return _hasher.get(); \
    } \
    \
public: \
    struct __builtin_function_tag; \
    \
    TEMPLATE(typename ... Functions) \
    REQUIRES(IS_CONSTRUCTIBLE(function_t,Functions)...) \
    explicit builtin_##_NAME##_nary_functor(Functions&& ... i_functions) \
    : m_functions({i_functions ...}) \
    { \
    } \
    builtin_##_NAME##_nary_functor(const std::vector<function_t>& i_functions) \
    : m_functions(i_functions) \
    { \
    } \
    builtin_##_NAME##_nary_functor(std::vector<function_t>&& i_functions) \
    : m_functions(std::move(i_functions)) \
    { \
    } \
    builtin_##_NAME##_nary_functor& operator=(const builtin_##_NAME##_nary_functor& other) \
    { \
        m_functions = other.m_functions; \
        \
        return *this; \
    } \
    ImSet operator()(Dom ... i_args) const final override \
    { \
        if(m_functions.empty()) \
        { \
            throw ddk::call_function_exception{"Trying to call empty function"}; \
        } \
        \
        ImSet res = ddk::eval(m_functions[0],std::forward<Dom>(i_args)...); \
        \
        for(size_t index=1;index<m_functions.size();++index) \
        { \
            res = res _OP ddk::eval(m_functions[index],std::forward<Dom>(i_args)...); \
        } \
        \
        return res; \
    } \
    bool empty() const \
    { \
        return m_functions.empty(); \
    } \
    size_t size() const \
    { \
        return m_functions.size(); \
    } \
    const function_t& get_operand(size_t i_index) const \
    { \
        return m_functions[i_index]; \
    } \
    void add(const function_t& i_operand) \
    { \
        m_functions.push_back(i_operand); \
    } \
    void add(const builtin_##_NAME##_nary_functor& i_operand) \
    { \
        m_functions.insert(m_functions.end(),i_operand.m_functions.begin(),i_operand.m_functions.end()); \
    } \
    builtin_##_NAME##_nary_functor combine(const function_t& i_operand) const \
    { \
        builtin_##_NAME##_nary_functor res(m_functions); \
        \
        res.m_functions.push_back(i_operand); \
        \
        return res; \
    } \
    builtin_##_NAME##_nary_functor combine(const builtin_##_NAME##_nary_functor& i_operand) const \
    { \
        builtin_##_NAME##_nary_functor res(m_functions); \
        \
        res.m_functions.insert(res.m_functions.end(),i_operand.m_functions.begin(),i_operand.m_functions.end()); \
        \
        return res; \
    } \
    template<typename Callable> \
    void enumerate(const Callable& i_sink) const \
    { \
        ddk::make_function([&i_sink](const function_t& i_func) \
        { \
            visit(i_sink,i_func); \
        })  <<= m_functions; \
    } \
    \
private: \
    std::vector<function_t> m_functions; \
} PUBLISH_RTTI_INHERITANCE(builtin_##_NAME##_nary_functor,function_impl_base); \
template<typename Im, typename ... Dom> \
builtin_##_NAME##_nary_functor(const std::vector<cpn::function_impl<Im(mpl::type_pack<Dom...>)>>&) -> builtin_##_NAME##_nary_functor<Im,mpl::type_pack<Dom...>>; \
template<template<typename,typename> typename Function, template<typename,typename> typename FFunction, typename Im, typename ... Dom> \
builtin_##_NAME##_nary_functor(const Function<Im,mpl::type_pack<Dom...>>&, const FFunction<Im,mpl::type_pack<Dom...>>&) -> builtin_##_NAME##_nary_functor<Im,mpl::type_pack<Dom...>>; \
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
struct _NAME##___builtin_function; \
template<typename Im, typename ... Dom> \
struct _NAME##___builtin_function<Im,mpl::type_pack<Dom...>> : public inherited_functor_impl<Im,Dom...> \
{ \
    struct __builtin_function_tag; \
    \
    friend inline size_t hash(const _NAME##___builtin_function& i_function) \
    { \
        static const rtti::TypeInfo s_typeHash = rtti::type_info<_NAME##___builtin_function<Im,mpl::type_pack<Dom...>>,function_impl_base<Im,mpl::type_pack<Dom...>>>(); \
        return hash_combine(s_typeHash,ddk::hash(#_NAME)); \
    } \
    constexpr _NAME##___builtin_function() = default; \
    Im operator()(Dom... i_args) const final override \
    { \
        return _FUNC(std::forward<Dom>(i_args)...); \
    } \
}; \
template<cpn::fundamental_type,typename> \
struct _NAME##__builtin_function; \
template<cpn::fundamental_type Im, typename ... Dom> \
struct _NAME##__builtin_function<Im,mpl::type_pack<Dom...>> : mpl::static_if<std::is_constructible<Im,decltype(_FUNC(std::declval<Dom>()...))>::value,_NAME##___builtin_function<Im,mpl::type_pack<Dom...>>,ddk::constant_callable<Im>>::type \
{ \
    typedef typename mpl::static_if<std::is_constructible<Im,decltype(_FUNC(std::declval<Dom>()...))>::value,_NAME##___builtin_function<Im,mpl::type_pack<Dom...>>,ddk::constant_callable<Im>>::type base_t; \
    using base_t::operator(); \
}; \
template<cpn::fundamental_type Im, _CONSTRAINT Dom> \
struct _NAME##_builtin_function : _NAME##__builtin_function<Im,Dom> \
{ \
    using _NAME##__builtin_function<Im,Dom>::operator(); \
} PUBLISH_RTTI_INHERITANCE(_NAME##_builtin_function,function_impl_base); \
template<cpn::fundamental_type Im, typename Dom> \
struct builtin_expression_function<cpn::_NAME##_builtin_expression,Im,Dom> : _NAME##_builtin_function<Im,Dom> \
{ \
	struct callable_tag; \
    using _NAME##_builtin_function<Im,Dom>::operator(); \
}; \
\
} \
}

namespace ddk
{
namespace detail
{

template<typename Im, typename Callable, typename ... Dom>
constexpr inline cpn::function_impl<Im(mpl::type_pack<Dom...>)> instantiate_template_callable(Callable&& i_callable, const ddk::mpl::type_pack<Dom...>&);

template<cpn::coordinate_type,typename>
struct builtin_fusioned_function;
template<cpn::coordinate_type ImSet,typename ... Dom>
struct builtin_fusioned_function<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom...>
{
    template<typename>
    struct fusioned_components;
    template<size_t ... Components>
    struct fusioned_components<ddk::mpl::sequence<Components...>>
    {
        friend inline size_t hash(const fusioned_components& i_function)
        {
            static const auto nestedHasher = dynamic_callable<size_t,function_impl_base<typename ImSet::place_type,mpl::type_pack<Dom...>>>([](auto&& i_function) -> size_t { return hash(i_function); });

            return ddk::hash_combine(visit(nestedHasher,i_function.m_fusionedFunction.template get_callable<Components>())...);
        }

        fusioned_components(const ddk::detail::intersection_function<cpn::function_impl<ddk::mpl::index_to_type<Components,typename ImSet::place_type>(mpl::type_pack<Dom...>)>...>& i_callable);

        const intersection_function<cpn::function_impl<ddk::mpl::index_to_type<Components,typename ImSet::place_type>(mpl::type_pack<Dom...>)>...> m_fusionedFunction;
    };
    friend inline size_t hash(const builtin_fusioned_function& i_function)
    {
        return hash(i_function.m_callables);
    }

public:
    struct __builtin_function_tag;

    template<typename ... T>
    builtin_fusioned_function(const intersection_function<cpn::function_impl<T(mpl::type_pack<Dom...>)>...>& i_args);

    template<size_t Index>
    inline const cpn::function_impl<typename ImSet::place_type(mpl::type_pack<Dom...>)>& get_callable() const;

    ImSet operator()(Dom... i_args) const final override;

private:
    template<size_t ... Indexs>
    inline ImSet execute(const mpl::sequence<Indexs...>&, Dom ... i_args) const;

    const fusioned_components<typename mpl::make_sequence<0,ImSet::num_places>::type> m_callables;
}PUBLISH_RTTI_INHERITANCE(builtin_fusioned_function,function_impl_base);

template<cpn::fundamental_type,typename>
struct builtin_composed_function;
template<cpn::fundamental_type ImSet,typename ... Dom>
struct builtin_composed_function<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom...>
{
    typedef cpn::function_impl<ImSet(mpl::type_pack<ImSet>)> function_lhs_t;
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_rhs_t;
    friend inline size_t hash(const builtin_composed_function& i_function)
    {
        static const rtti::TypeInfo s_typeHash = rtti::type_info<builtin_composed_function<ImSet,mpl::type_pack<Dom...>>,function_impl_base<ImSet,mpl::type_pack<Dom...>>>();
        static const auto nestedSrcHasher = ddk::dynamic_callable<size_t,function_impl_base<ImSet,mpl::type_pack<Dom...>>>([](auto&& i_function) -> size_t { return hash(i_function); });
        static const auto nestedDestHasher = ddk::dynamic_callable<size_t,function_impl_base<ImSet,mpl::type_pack<ImSet>>>([](auto&& i_function) -> size_t { return hash(i_function); });

        return hash_combine(s_typeHash,visit(nestedDestHasher,i_function.m_lhs),visit(nestedSrcHasher,i_function.m_rhs));
    }

public:
    struct __builtin_function_tag;

    TEMPLATE(typename Function, typename FFunction)
    REQUIRES(IS_CONSTRUCTIBLE(function_lhs_t,Function),IS_CONSTRUCTIBLE(function_rhs_t,FFunction))
    builtin_composed_function(Function&& i_lhs, FFunction&& i_rhs);

    const function_lhs_t& get_dest_function() const;
    const function_rhs_t& get_source_function() const;

    ImSet operator()(Dom... i_args) const final override;

private:
    const function_lhs_t m_lhs;
    const function_rhs_t m_rhs;
} PUBLISH_RTTI_INHERITANCE(builtin_composed_function,function_impl_base);

template<cpn::fundamental_type,typename>
struct builtin_component_function;
template<cpn::fundamental_type ImSet,typename ... Dom>
struct builtin_component_function<ImSet,mpl::type_pack<Dom...>>: public inherited_functor_impl<ImSet,Dom...>
{
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_t;
    friend inline size_t hash(const builtin_component_function& i_function)
    {
        static const rtti::TypeInfo s_typeHash = rtti::type_info<builtin_component_function<ImSet,mpl::type_pack<Dom...>>,function_impl_base<ImSet,mpl::type_pack<Dom...>>>();
        return hash_combine(s_typeHash,i_function.m_component);
    }

public:
    struct __builtin_function_tag;

    template<size_t Comp>
    builtin_component_function(const ddk::mpl::static_number<Comp>&);

    ImSet operator()(Dom... i_args) const final override;
    size_t get_component() const;

private:
    const cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> m_projection;
    const size_t m_component;

} PUBLISH_RTTI_INHERITANCE(builtin_component_function,function_impl_base);

template<cpn::fundamental_type,typename>
struct builtin_number_function;
template<cpn::fundamental_type ImSet,typename ... Dom>
struct builtin_number_function<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom...>
{
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_t;
    friend inline size_t hash(const builtin_number_function& i_function)
    {
        static const rtti::TypeInfo s_typeHash = rtti::type_info<builtin_number_function<ImSet,mpl::type_pack<Dom...>>,function_impl_base<ImSet,mpl::type_pack<Dom...>>>();
        return hash_combine(s_typeHash,i_function.m_number);
    }

public:
    struct __builtin_function_tag;

    builtin_number_function(const ImSet& i_number);

    const ImSet& get_number() const;

    ImSet operator()(Dom... i_args) const final override;

private:
    const ImSet m_number;
} PUBLISH_RTTI_INHERITANCE(builtin_number_function,function_impl_base);

template<cpn::fundamental_type,typename>
struct builtin_inverted_function;
template<cpn::fundamental_type ImSet,typename ... Dom>
struct builtin_inverted_function<ImSet,mpl::type_pack<Dom...>> : public inherited_functor_impl<ImSet,Dom...>
{
    typedef cpn::function_impl<ImSet(mpl::type_pack<Dom...>)> function_t;
    friend inline size_t hash(const builtin_inverted_function& i_function)
    {
        static const rtti::TypeInfo s_typeHash = rtti::type_info<builtin_inverted_function<ImSet,mpl::type_pack<Dom...>>,function_impl_base<ImSet,mpl::type_pack<Dom...>>>();
        static const auto nestedHasher = dynamic_callable<size_t,function_impl_base<ImSet,mpl::type_pack<Dom...>>>([](auto&& i_function) -> size_t { return hash(i_function); });
        return ~hash_combine(s_typeHash,visit(nestedHasher,i_function.m_function));
    }

public:
    struct __builtin_function_tag;

    template<typename Expression>
    builtin_inverted_function(Expression&& i_expression);

    const function_t& get_expresion() const;

    ImSet operator()(Dom... i_args) const final override;

private:
    const function_t m_function;
} PUBLISH_RTTI_INHERITANCE(builtin_inverted_function,function_impl_base);

template<typename,cpn::fundamental_type,typename>
struct builtin_expression_function;

}
}

////arithmetic operations
DEFINE_ARITHMETIC_NARY_OPERATION(add,+,cpn::fundamental_type);
DEFINE_ARITHMETIC_NARY_OPERATION(prod,*,cpn::fundamental_type);
//DEFINE_ARITHMETIC_NARY_OPERATION(div,/,cpn::closed_divisible_type);

//predefined math functions
DEFINE_BUILTIN_FUNCTION(sin,cpn::detail::sin,cpn::type_pack_args_equal_to_1);
DEFINE_BUILTIN_FUNCTION(cos,cpn::detail::cos,cpn::type_pack_args_equal_to_1);
DEFINE_BUILTIN_FUNCTION(tan,cpn::detail::tan,cpn::type_pack_args_equal_to_1);


#include "cpn_builtin_functions.inl"