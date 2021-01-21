#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "ddkFramework/ddk_iterable_algorithm.h"

namespace cpn
{

template<typename Set, typename AddOperation,typename MultOperation>
using ring = algebraic_structure<Set,AddOperation,MultOperation>;

template<typename Ring, size_t ... Dims>
struct pow_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_mult_operation,typename Ring::operators_pack);

	typedef pow_set<Ring,Dims...> pow_set_traits_t;
	typedef pow_mult_operation mult_operation;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator*(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_prod(i_lhs,i_rhs);

		return res;
	}
};

template<typename Ring, size_t ... Dims>
using pow_semi_ring = typename pow_semi_group<Ring,Dims...>::template equip_with<pow_mult_operation<Ring,Dims...>>;

template<typename Ring, size_t ... Dims>
using pow_ring = typename pow_group<Ring,Dims...>::template equip_with<pow_mult_operation<Ring,Dims...>>;

template<typename ... Rings>
struct sum_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_mult_operation,ddk::mpl::type_pack_intersection<typename Rings::operators_pack...>);

    typedef sum_set<Rings...> sum_set_traits_t;
	typedef sum_mult_operation mult_operation;

	struct mult_operation_visitor : public ddk::static_visitor<sum_set_traits_t>
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
		return ddk::visit(mult_operation_visitor{},i_lhs,i_rhs);
	}
};

template<typename ... Rings>
using sum_semi_ring = typename sum_semi_group<Rings...>::template equip_with<sum_mult_operation<Rings...>>;

template<typename ... Rings>
using sum_ring = typename sum_group<Rings...>::template equip_with<sum_mult_operation<Rings...>>;

}
