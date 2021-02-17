#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "ddkFramework/ddk_iterable_algorithm.h"

namespace cpn
{

template<set_type T, typename AddOperation,typename MultOperation>
using semi_ring = algebraic_structure<T,AddOperation,MultOperation>;

template<set_type T, typename AddOperation, typename AddInverseOperation,typename MultOperation>
using ring = algebraic_structure<T,AddOperation,AddInverseOperation,MultOperation>;

template<semi_ring_type T, size_t ... Dims>
struct pow_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_mult_operation,mult_operation,typename T::operators_pack);

	typedef pow_set<T,Dims...> pow_set_traits_t;

	static const pow_set_traits_t identity;
	static const pow_set_traits_t annihilator;

    static inline ddk::high_order_array<size_t,ddk::mpl::num_ranks<Dims...>> dimension()
    {
        return { Dims... };
    }
	friend inline pow_set_traits_t operator*(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_prod(i_lhs,i_rhs);

		return res;
	}
};

template<semi_ring_type T, size_t ... Dims>
using pow_semi_ring = typename pow_semi_group<forget_mult<T>,Dims...>::template equip_with<pow_mult_operation<T,Dims...>>;

template<ring_type T, size_t ... Dims>
using pow_ring = typename pow_group<forget_mult<T>,Dims...>::template equip_with<pow_mult_operation<T,Dims...>>;

template<semi_ring_type ... T>
struct sum_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_mult_operation,mult_operation,ddk::mpl::type_pack_intersection<typename T::operators_pack...>);

    typedef sum_set<T...> sum_set_traits_t;

	struct mult_operation_visitor : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return i_lhs * i_rhs;
		}
	};

	static const sum_set_traits_t identity;
	static const sum_set_traits_t annihilator;
	friend inline sum_set_traits_t operator*(const sum_set_traits_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit(mult_operation_visitor{},i_lhs,i_rhs);
	}
};

template<semi_ring_type ... T>
using sum_semi_ring = typename sum_semi_group<forget_mult<T>...>::template equip_with<sum_mult_operation<T...>>;

template<ring_type ... T>
using sum_ring = typename sum_group<forget_mult<T>...>::template equip_with<sum_mult_operation<T...>>;

}
