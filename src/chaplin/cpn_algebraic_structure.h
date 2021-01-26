#pragma once

#include "ddk_concepts.h"
#include "ddk_type_concepts.h"
#include "cpn_algebraic_concepts.h"

namespace cpn
{
namespace detail
{

template<typename,typename>
class algebraic_structure_impl;

template<typename Set,typename ... Operators>
class algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>> : public Set, public Operators ...
{
public:
    typedef ddk::mpl::type_pack<Operators...> operators_pack;

    template<typename ... Operations>
    using equip_with = algebraic_structure_impl<Set,typename ddk::mpl::type_pack<Operators...>::template add<Operations...>::type>;
    typedef Set set_traits;
	using Set::Set;

    explicit constexpr algebraic_structure_impl(const Set&);
    TEMPLATE(typename SSet, typename ... OOperators)
    REQUIRES(IS_CONSTRUCTIBLE(Set,SSet),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
    constexpr algebraic_structure_impl(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<OOperators...>>& other);
    TEMPLATE(typename SSet)
    REQUIRES(IS_CONSTRUCTIBLE(Set,SSet))
    constexpr algebraic_structure_impl(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<>>& other);

    TEMPLATE(typename SSet, typename ... OOperators)
    REQUIRES(IS_ASSIGNABLE(Set,SSet),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
    constexpr algebraic_structure_impl& operator=(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<OOperators...>>& other);
    TEMPLATE(typename SSet)
    REQUIRES(IS_ASSIGNABLE(Set,SSet))
    constexpr algebraic_structure_impl& operator=(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<>>& other);
};

}

template<typename Set, typename ... Operators>
using algebraic_structure = detail::algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>;

}

#include "cpn_algebraic_structure.inl"
#include "cpn_algebraic_functor.h"
