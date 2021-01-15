#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "ddkFramework/ddk_iterable_algorithm.h"

namespace cpn
{

template<typename set, typename group_traits,typename ring_traits>
using ring = algebraic_structure<set,group_traits,ring_traits>;

template<typename rings, size_t ... Dims>
struct pow_ring_traits : virtual public pow_set<ring<typename rings::set_traits,typename rings::group_traits, typename rings::ring_traits>,Dims...>
{
	typedef pow_set<ring<typename rings::set_traits,typename rings::group_traits, typename rings::ring_traits>,Dims...> pow_set_traits_t;
    typedef pow_ring_traits<rings,Dims...> ring_traits;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator*(const ring_traits& i_lhs,const ring_traits& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_prod(static_cast<const pow_set_traits_t&>(i_lhs),static_cast<const pow_set_traits_t&>(i_rhs));

		return res;
	}
};

template<typename ... rings>
struct sum_ring_traits : virtual public sum_set<ring<typename rings::set_traits,typename rings::group_traits,typename rings::ring_traits> ...>
{
    typedef sum_set<ring<typename rings::set_traits,typename rings::group_traits,typename rings::ring_traits> ...> sum_set_traits_t;
    typedef sum_ring_traits<rings...> ring_traits;

	struct ring_prod_operation : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return i_lhs * i_rhs;
		}
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator*(const ring_traits& i_lhs,const ring_traits& i_rhs)
	{
		return ddk::visit(ring_prod_operation{},static_cast<sum_set_traits_t>(i_lhs),static_cast<sum_set_traits_t>(i_rhs));
	}
};

}
