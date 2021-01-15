#pragma once

#include "cpn_set.h"
#include "cpn_algebraic_structure.h"
#include "ddkFramework/ddk_template_helper.h"
#include "ddkFramework/ddk_iterable_algorithm.h"
#include "ddk_high_order_array_adaptor.h"

namespace cpn
{

template<typename set,typename group_traits>
using group = algebraic_structure<set,group_traits>;

template<typename groups, size_t ... Dims>
struct pow_group_traits : virtual public pow_set<group<typename groups::set_traits,typename groups::group_traits>,Dims...>
{
	typedef pow_set<group<typename groups::set_traits,typename groups::group_traits>,Dims...> pow_set_traits_t;
	typedef pow_group_traits<groups,Dims...> group_traits;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator+(const group_traits& i_lhs,const group_traits& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_sum(static_cast<const pow_set_traits_t&>(i_lhs),static_cast<const pow_set_traits_t&>(i_rhs));

		return res;
	}
	friend inline pow_set_traits_t operator-(const group_traits& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_neg(static_cast<const pow_set_traits_t&>(i_rhs));

		return res;
	}
};

template<typename ... groups>
struct sum_group_traits : virtual public sum_set<group<typename groups::set_traits,typename groups::group_traits> ...>
{
	typedef sum_set<group<typename groups::set_traits,typename groups::group_traits> ...> sum_set_traits_t;
	typedef sum_group_traits<groups...> group_traits;

	struct sum_group_operation : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1, typename T2>
		sum_set_traits_t operator()(T1&& i_lhs, T2&& i_rhs) const
		{
			return i_lhs + i_rhs;
		}
	};
	struct neg_group_operation : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return -i_lhs;
		}
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator+(const group_traits& i_lhs,const group_traits& i_rhs)
	{
		return ddk::visit(sum_group_operation{},static_cast<sum_set_traits_t>(i_lhs),static_cast<sum_set_traits_t>(i_rhs));
	}
	friend inline sum_set_traits_t operator-(const group_traits& i_rhs)
	{
		return ddk::visit(neg_group_operation{},static_cast<sum_set_traits_t>(i_rhs));
	}
};

}
