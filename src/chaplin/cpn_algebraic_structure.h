#pragma once

#include "ddk_concepts.h"
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

	algebraic_structure_impl(const Set& i_value);
	TEMPLATE(typename T)
	REQUIRES(IS_SUPERSTRUCTURE_OF(T,algebraic_structure_impl))
    algebraic_structure_impl& operator=(T&& other);

protected:
    using Set::operator=;
};

}

template<typename Set, typename ... Operators>
using algebraic_structure = detail::algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>;

}

#include "cpn_algebraic_structure.inl"
#include "cpn_algebraic_functor.h"
