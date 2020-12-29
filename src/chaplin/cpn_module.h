#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "cpn_ring.h"

namespace cpn
{

template<typename set, typename group_traits, typename module_traits>
using module = algebraic_structure<set,group_traits,module_traits>;

template<typename ring_traits>
struct module_from_ring_traits
{
	typedef typename ring_traits::set_traits set_traits;
	typedef set_traits r_module_set_traits;

	static const set_traits identity;
	friend inline set_traits operator^(const set_traits& i_lhs,const set_traits& i_rhs)
	{
		return i_lhs * i_rhs;
	}
};

template<typename module_traits,size_t ... Indexs>
struct pow_module_traits
{
	typedef typename module_traits::r_module_set_traits r_module_set_traits;
	typedef typename module_traits::set_traits slice_set_traits;
	typedef pow_set<slice_set_traits,Indexs...> set_traits;

	static const set_traits identity;
	friend inline set_traits operator^(const r_module_set_traits& i_lhs,const set_traits& i_rhs)
	{
		set_traits res;

		res <<= ddk::trans::iterable_transform([&i_lhs](const slice_set_traits& i_value){ return i_lhs ^ i_value; },i_rhs);

		return res;
	}
};

template<typename set,typename group_traits,typename module_traits,size_t ... Indexs>
using pow_module = module<pow_set<set,Indexs...>,pow_group_traits<group_traits,Indexs...>,pow_ring_traits<module_traits,Indexs...>>;

}