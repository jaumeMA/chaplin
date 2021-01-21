#pragma once

namespace cpn
{

template<typename Set, typename AddOperation,typename MultOperation, typename DivisionOperation>
using field = algebraic_structure<Set,AddOperation,MultOperation,DivisionOperation>;

template<typename Field, size_t ... Dims>
struct pow_div_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_div_operation,typename Field::operators_pack);

	typedef pow_set<Field,Dims...> pow_set_traits_t;
	typedef pow_div_operation div_operation;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator/(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_div(i_lhs,i_rhs);

		return res;
	}
};

template<typename Field, size_t ... Dims>
using pow_field = typename pow_ring<Field,Dims...>::template equip_with<pow_div_operation<Field,Dims...>>;

template<typename ... Fields>
struct sum_div_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_div_operation,ddk::mpl::type_pack_intersection<typename Fields::operators_pack...>);

    typedef sum_set<Fields...> sum_set_traits_t;
	typedef sum_div_operation div_operation;

	struct div_field_operation : public ddk::static_visitor<sum_set_traits_t>
	{
		template<typename T1,typename T2>
		sum_set_traits_t operator()(T1&& i_lhs,T2&& i_rhs) const
		{
			return i_lhs / i_rhs;
		}
	};

	friend inline sum_set_traits_t operator/(const sum_set_traits_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit(div_field_operation{},i_lhs,i_rhs);
	}
};

template<typename ... Fields>
using sum_field = typename sum_ring<Fields...>::template equip_with<sum_div_operation<Fields...>>;

}
