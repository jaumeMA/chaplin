#pragma once

#define _ENABLE_EXTENDED_ALIGNED_STORAGE

#include "ddk_concepts.h"
#include "ddk_type_concepts.h"
#include "cpn_algebraic_concepts.h"

namespace cpn
{
namespace detail
{

template<set_type,typename>
class algebraic_structure_impl;

template<set_type T,typename ... Operators>
class algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>> : public T, public Operators ...
{
public:
    typedef ddk::mpl::type_pack<Operators...> operators_pack;
    typedef T set_traits;

    template<typename ... Operations>
    using equip_with = algebraic_structure_impl<T,typename ddk::mpl::type_pack<Operators...>::template add<Operations...>::type>;
    using T::operator==;

    using T::T;
    algebraic_structure_impl() = default;
    TEMPLATE(set_type TT)
    REQUIRES_COND((IS_SAME_CLASS_COND(T,TT) || IS_NOT_BASE_OF_COND(T,TT)) && IS_CONSTRUCTIBLE_COND(T,TT))
    constexpr algebraic_structure_impl(const TT& other);
    TEMPLATE(set_type TT, typename ... OOperators)
    REQUIRES(IS_CONSTRUCTIBLE(T,TT),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
    constexpr algebraic_structure_impl(const algebraic_structure_impl<TT,ddk::mpl::type_pack<OOperators...>>& other);
    TEMPLATE(set_type TT)
    REQUIRES(IS_CONSTRUCTIBLE(T,TT))
    constexpr algebraic_structure_impl(const algebraic_structure_impl<TT,ddk::mpl::type_pack<>>& other);

    TEMPLATE(set_type TT, typename ... OOperators)
    REQUIRES(IS_ASSIGNABLE(T,TT),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
    constexpr algebraic_structure_impl& operator=(const algebraic_structure_impl<TT,ddk::mpl::type_pack<OOperators...>>& other);
    TEMPLATE(set_type TT)
    REQUIRES(IS_ASSIGNABLE(T,TT))
    constexpr algebraic_structure_impl& operator=(const algebraic_structure_impl<TT,ddk::mpl::type_pack<>>& other);
};

}

template<set_type Set, typename ... Operators>
using algebraic_structure = detail::algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>;

}

#include "cpn_algebraic_structure.inl"
#include "cpn_algebraic_functor.h"
