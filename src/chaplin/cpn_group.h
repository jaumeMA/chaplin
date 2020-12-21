#pragma once

#include "cpn_set.h"
#include "cpn_algebraic_structure.h"
#include "ddkFramework/ddk_template_helper.h"

namespace cpn
{

// think about adding concepts here
template<typename Set,typename SumOperator>
using group = algebraic_structure<Set,SumOperator>;

template<typename ... Groups>
struct prod_group_traits
{
private:
	typedef prod_set<typename Groups::set_t ...> prod_set_t;

	template<size_t ... Indexs>
	inline static prod_set_t inner_sum(const ddk::mpl::sequence<Indexs...>&, const prod_set_t& i_lhs,const prod_set_t& i_rhs)
	{
		return { i_lhs.template get<Indexs>() + i_rhs.template get<Indexs>() ... };
	}
	template<size_t ... Indexs>
	inline static prod_set_t inverse(const ddk::mpl::sequence<Indexs...>&,const prod_set_t& i_rhs)
	{
		return { -i_rhs.template get<Indexs>() ... };
	}

public:
	static const prod_set_t identity;
	friend inline prod_set_t operator+(const prod_set_t& i_lhs, const prod_set_t& i_rhs)
	{
		return inner_sum(ddk::mpl::make_sequence<0,ddk::mpl::get_num_types<Groups...>::value>::type{},i_lhs,i_rhs);
	}
	friend inline prod_set_t operator-(const prod_set_t& i_rhs)
	{
		return inverse(ddk::mpl::make_sequence<0,ddk::mpl::get_num_types<Groups...>::value>::type{},i_rhs);
	}
};

template<typename ... Groups>
using prod_group = group<prod_set<typename Groups::set_t ...>,prod_group_traits<Groups...>>;

template<typename Group, size_t ... Indexs>
struct pow_group_traits
{
	typedef pow_set<typename Group::set_t,Indexs...> pow_set_t;

	static const pow_set_t identity;
	friend inline pow_set_t operator+(const pow_set_t& i_lhs,const pow_set_t& i_rhs)
	{
		//USE ITERABLES AND APPLY SUM ALGORITHM
	}
	friend inline pow_set_t operator-(const pow_set_t& i_rhs)
	{
		//USE ITERABLES AND APPLY INVERSE ALGORITHM
	}
};

template<typename Group, size_t ... Indexs>
using pow_group = group<pow_set<typename Group::set_t,Indexs...>,pow_group_traits<Group,Indexs...>>;

template<typename ... Groups>
struct sum_group_traits
{
	//TBD
};

template<typename ... Groups>
using sum_group = group<sum_set<typename Groups::set_t ...>,sum_group_traits<Groups...>>;

}