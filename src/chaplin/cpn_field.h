#pragma once

namespace cpn
{

template<ring_type T, typename DivisionOperation>
using field = typename T::template equip_with<DivisionOperation>;

template<field_type T, size_t ... Dims>
struct pow_div_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_div_operation,div_operation,typename T::operators_pack);

	typedef typename pow_set<T,Dims...>::set_traits pow_set_traits_t;

	static const pow_set_traits_t identity;
	friend inline pow_set_traits_t operator/(const pow_set_traits_t& i_lhs,const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::iter::div(i_lhs,i_rhs);

		return res;
	}
};

template<field_type T, size_t ... Dims>
using pow_field = typename pow_ring<T,Dims...>::template equip_with<pow_div_operation<T,Dims...>>;

template<field_type ... T>
struct sum_div_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_div_operation,div_operation,ddk::mpl::type_pack_intersection<typename T::operators_pack...>);

    typedef typename sum_set<T...>::set_traits sum_set_traits_t;

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

template<field_type ... T>
using sum_field = typename sum_ring<T...>::template equip_with<sum_div_operation<T...>>;

}
