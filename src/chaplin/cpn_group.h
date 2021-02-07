#pragma once

#include "cpn_set.h"
#include "cpn_algebraic_structure.h"
#include "ddkFramework/ddk_template_helper.h"
#include "ddkFramework/ddk_iterable_algorithm.h"
#include "ddk_high_order_array_adaptor.h"

namespace cpn
{

template<typename Set,typename AddOperation>
using semi_group = algebraic_structure<Set,AddOperation>;

template<typename Set,typename AddOperation, typename AddInverseOperation>
using group = algebraic_structure<Set,AddOperation,AddInverseOperation>;

template<typename Group, size_t ... Dims>
struct pow_add_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_add_operation,add_operation,typename Group::operators_pack);

	typedef pow_set<Group,Dims...> pow_set_traits_t;

	static const pow_set_traits_t identity;
    static inline ddk::high_order_array<size_t,ddk::mpl::num_ranks<Dims...>> dimension()
    {
        return { Dims... };
    }
	friend inline pow_set_traits_t operator+(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_sum(i_lhs,i_rhs);

		return res;
	}
};

template<typename SemiGroup, size_t ... Dims>
using pow_semi_group = semi_group<pow_set<forget_add<SemiGroup>,Dims...>,pow_add_operation<SemiGroup,Dims...>>;

template<typename Group, size_t ... Dims>
struct pow_add_inverse_operation
{
	typedef pow_set<Group,Dims...> pow_set_traits_t;
	typedef pow_add_inverse_operation<Group,Dims...> add_inverse_operation;

	friend inline pow_set_traits_t operator-(const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_neg(i_rhs);

		return res;
	}
};

template<typename Group, size_t ... Dims>
using pow_group = typename pow_semi_group<forget_add_inverse<Group>,Dims...>::template equip_with<pow_add_inverse_operation<Group,Dims...>>;

template<typename ... Groups>
struct sum_add_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_add_operation,add_operation,ddk::mpl::type_pack_intersection<typename Groups::operators_pack...>);

	typedef sum_set<Groups...> sum_set_traits_t;

	struct add_operation_visitor : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1, typename T2>
		sum_set_traits_t operator()(T1&& i_lhs, T2&& i_rhs) const
		{
			return i_lhs + i_rhs;
		}
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator+(const sum_set_traits_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit(add_operation_visitor{},i_lhs,i_rhs);
	}
};

template<typename ... SemiGroups>
using sum_semi_group = semi_group<sum_set<forget_add<SemiGroups>...>,sum_add_operation<SemiGroups...>>;

template<typename ... Groups>
struct sum_add_inverse_operation
{
	typedef sum_set<Groups...> sum_set_traits_t;
	typedef sum_add_inverse_operation<Groups...> add_inverse_operation;

	struct inverse_operation_visitor : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return -i_lhs;
		}
	};

	friend inline sum_set_traits_t operator-(const sum_set_traits_t& i_rhs)
	{
		return ddk::visit(inverse_operation_visitor{},i_rhs);
	}
};

template<typename ... Groups>
using sum_group = typename sum_semi_group<forget_add_inverse<Groups>...>::template equip_with<sum_add_inverse_operation<Groups...>>;

}
