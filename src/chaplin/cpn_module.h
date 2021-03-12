#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "cpn_ring.h"

namespace cpn
{

template<set_type T, typename AddOperation, typename ModuleOperation>
using module = algebraic_structure<T,AddOperation,ModuleOperation>;

template<module_type T>
using module_ring = typename T::ring_t;

template<ring_type T>
struct ring_module_operation
{
	PUBLISH_OPERATION_PROPERTIES(ring_module_operation,mod_operation,typename T::operators_pack);

	typedef typename T::set_traits set_traits;
	typedef T ring_t;

	friend inline set_traits operator^(const set_traits& i_lhs, const set_traits& i_rhs)
	{
		return i_lhs * i_rhs;
	}
};

template<ring_type T>
using ring_as_module = typename algebraic_structure<T>::template equip_with<ring_module_operation<T>>;

template<module_type T,size_t ... Dims>
struct pow_mod_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_mod_operation,mod_operation,typename T::operators_pack);

	typedef pow_set<T,Dims...> pow_set_traits_t;
    typedef typename T::ring_t ring_t;

	static const ring_t identity;
	static inline constexpr ddk::high_order_array<size_t,ddk::mpl::num_ranks<Dims...>> dimension = {Dims...};
	friend inline pow_set_traits_t operator^(const ring_t& i_lhs, const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::iter::transform([&i_lhs](const T& i_value){ return i_lhs ^ i_value; }) <<= i_rhs;

		return res;
	}
	friend inline pow_set_traits_t operator^(const pow_set_traits_t& i_lhs,const ring_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::iter::transform([&i_rhs](const T& i_value){ return i_value ^ i_rhs; }) <<= i_lhs;

		return res;
	}
};

template<module_type T, size_t ... Dims>
using pow_module = typename pow_group<forget_mod<T>,Dims...>::template equip_with<pow_mod_operation<T,Dims...>>;

template<module_type ... T>
struct sum_mod_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_mod_operation,mod_operation,ddk::mpl::type_pack_intersection<typename T::operators_pack...>);

	typedef sum_set<T...> sum_set_traits_t;
    typedef sum_ring<typename T::ring_t ...> ring_t;

	struct module_prod_operation : public ddk::static_visitor<sum_set_traits_t>
	{
    public:
	    module_prod_operation() = default;
		template<typename T1, typename T2>
		inline sum_set_traits_t operator()(T1&& i_lhs, T2&& i_rhs) const;
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator^(const ring_t& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit(module_prod_operation{},i_lhs,i_rhs);
	}
	friend inline sum_set_traits_t operator^(const sum_set_traits_t& i_lhs, const ring_t& i_rhs)
	{
		return ddk::visit(module_prod_operation{},i_lhs,i_rhs);
	}
};

template<module_type ... T>
using sum_module = typename sum_group<forget_mod<T>...>::template equip_with<sum_mod_operation<T...>>;

}


#include "cpn_module.inl"
