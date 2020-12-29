#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "ddkFramework/ddk_iterable_algorithm.h"

namespace cpn
{

template<typename set, typename group_traits,typename ring_traits>
using ring = algebraic_structure<set,group_traits,ring_traits>;

template<typename ring_traits, size_t ... Indexs>
struct pow_ring_traits
{
	typedef pow_set<typename ring_traits::set_traits,Indexs...> pow_set_traits_t;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator*(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_prod(i_lhs,i_rhs);

		return res;
	}
};

template<typename ... ring_traits>
struct sum_ring_traits
{
	typedef sum_set<typename ring_traits::set_traits ...> sum_set_traits_t;

	struct ring_prod_operation
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return i_lhs * i_rhs;
		}
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator*(const sum_set_traits_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit<sum_set_traits_t>(ring_prod_operation{},i_lhs,i_rhs);
	}
};

}