#pragma once

#include "cpn_set.h"
#include "cpn_algebraic_structure.h"
#include "ddkFramework/ddk_template_helper.h"
#include "ddkFramework/ddk_algorithm.h"

namespace cpn
{

template<typename set,typename group_traits>
using group = algebraic_structure<set,group_traits>;

template<typename group_traits, size_t ... Indexs>
struct pow_group_traits
{
	typedef pow_set<typename group_traits::set_traits,Indexs...> pow_set_traits_t;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator+(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_sum(i_lhs,i_rhs);

		return res;
	}
	friend inline pow_set_traits_t operator-(const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_neg(i_rhs);

		return res;
	}
};

template<typename ... group_traits>
struct sum_group_traits
{
	typedef sum_set<typename group_traits::set_traits ...> sum_set_traits_t;

	struct sum_group_operation
	{
		template<typename T1, typename T2>
		sum_set_traits_t operator()(T1&& i_lhs, T2&& i_rhs) const
		{
			return i_lhs + i_rhs;
		}
	};
	struct neg_group_operation
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return - i_lhs;
		}
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator+(const sum_set_traits_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit<sum_set_traits_t>(sum_group_operation{},i_lhs,i_rhs);
	}
	friend inline sum_set_traits_t operator-(const sum_set_traits_t& i_rhs)
	{
		return ddk::visit<sum_set_traits_t>(neg_group_operation{},i_rhs);
	}
};

}