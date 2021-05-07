#pragma once

#include "cpn_set.h"
#include "cpn_algebraic_structure.h"
#include "ddkFramework/ddk_template_helper.h"
#include "ddkFramework/ddk_iterable_algorithm.h"
#include "ddk_high_order_array_adaptor.h"

namespace cpn
{

template<set_type T,typename AddOperation>
using semi_group = typename T::template equip_with<AddOperation>;

template<set_type T,typename AddOperation, typename AddInverseOperation>
using group = typename semi_group<T,AddOperation>::template equip_with<AddInverseOperation>;

template<semi_group_type T, size_t ... Dims>
struct pow_add_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_add_operation,add_operation,typename T::operators_pack);

	typedef typename pow_set<T,Dims...>::set_traits pow_set_traits_t;

	static const pow_set_traits_t identity;
    static inline constexpr ddk::high_order_array<size_t,ddk::mpl::num_ranks<Dims...>> dimension = { Dims... };

	friend inline pow_set_traits_t operator+(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::iter::sum(i_lhs,i_rhs);

		return res;
	}
};

template<semi_group_type T, size_t ... Dims>
using pow_semi_group = semi_group<pow_set<T,Dims...>,pow_add_operation<T,Dims...>>;

template<group_type T, size_t ... Dims>
struct pow_add_inverse_operation
{
	PUBLISH_OPERATION_PROPERTIES(pow_add_inverse_operation,add_inverse_operation,typename T::operators_pack);

	typedef typename pow_set<T,Dims...>::set_traits pow_set_traits_t;

	friend inline pow_set_traits_t operator-(const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::iter::inv(i_rhs);

		return res;
	}
	friend inline pow_set_traits_t operator-(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::iter::subs(i_lhs,i_rhs);

		return res;
	}
};

template<group_type T, size_t ... Dims>
using pow_group = typename pow_semi_group<T,Dims...>::template equip_with<pow_add_inverse_operation<T,Dims...>>;

template<semi_group_type ... T>
struct sum_add_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_add_operation,add_operation,ddk::mpl::type_pack_intersection<typename T::operators_pack...>);

	typedef typename sum_set<T...>::set_traits sum_set_traits_t;

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
		return ddk::visit<add_operation_visitor>(i_lhs,i_rhs);
	}
};

template<semi_group_type ... T>
using sum_semi_group = semi_group<sum_set<T...>,sum_add_operation<T...>>;

template<group_type ... T>
struct sum_add_inverse_operation
{
	PUBLISH_OPERATION_PROPERTIES(sum_add_inverse_operation,add_inverse_operation,typename T::operators_pack...);

	typedef typename sum_set<T...>::set_traits sum_set_traits_t;

	struct inverse_operation_visitor : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return -i_lhs;
		}
	};
	struct subs_operation_visitor: public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return i_lhs - i_rhs;
		}
	};

	friend inline sum_set_traits_t operator-(const sum_set_traits_t& i_rhs)
	{
		return ddk::visit<inverse_operation_visitor>(i_rhs);
	}
	friend inline sum_set_traits_t operator-(const sum_set_traits_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit<subs_operation_visitor>(i_lhs,i_rhs);
	}
};

template<group_type ... T>
using sum_group = typename sum_semi_group<T...>::template equip_with<sum_add_inverse_operation<T...>>;

}
