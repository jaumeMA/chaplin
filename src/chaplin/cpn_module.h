#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "cpn_ring.h"

namespace cpn
{

template<typename set, typename AddOperation, typename ModuleOperation>
using module = algebraic_structure<set,AddOperation,ModuleOperation>;

template<typename Module>
using module_ring = typename Module::ring_type;

template<typename Module,size_t ... Dims>
struct pow_mod_operation
{
    PUBLISH_OPERATION_PROPERTIES(pow_mod_operation,mod_operation,typename Module::operators_pack);

	typedef pow_set<Module,Dims...> pow_set_traits_t;
    typedef typename Module::ring_type ring_type;

	static const ring_type identity;
    static inline constexpr size_t rank()
    {
        return ddk::mpl::get_num_ranks<Dims...>();
    }
    static inline constexpr ddk::high_order_array<size_t,ddk::mpl::get_num_ranks<Dims...>()> dimension()
    {
        return { Dims ...};
    }
	friend inline pow_set_traits_t operator^(const ring_type& i_lhs, const pow_set_traits_t& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_transform([&i_lhs](const Module& i_value){ return i_lhs ^ i_value; },i_rhs);

		return res;
	}
	friend inline pow_set_traits_t operator^(const pow_set_traits_t& i_lhs,const ring_type& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_transform([&i_rhs](const Module& i_value){ return i_value ^ i_rhs; },i_lhs);

		return res;
	}
};

template<typename Module, size_t ... Dims>
using pow_module = typename pow_group<forget_mod<Module>,Dims...>::template equip_with<pow_mod_operation<Module,Dims...>>;

template<typename ... Modules>
struct sum_mod_operation
{
    PUBLISH_OPERATION_PROPERTIES(sum_mod_operation,mod_operation,ddk::mpl::type_pack_intersection<typename Modules::operators_pack...>);

	typedef sum_set<Modules ...> sum_set_traits_t;
    typedef sum_ring<typename Modules::ring_type ...> ring_type;

	struct module_prod_operation : public ddk::static_visitor<sum_set_traits_t>
	{
    public:
	    module_prod_operation() = default;
		template<typename T1, typename T2>
		inline sum_set_traits_t operator()(T1&& i_lhs, T2&& i_rhs) const;
	};

	static const sum_set_traits_t identity;
    static inline constexpr size_t rank()
    {
        return ddk::mpl::get_num_types<Modules...>();
    }
	friend inline sum_set_traits_t operator^(const ring_type& i_lhs,const sum_set_traits_t& i_rhs)
	{
		return ddk::visit(module_prod_operation{},i_lhs,i_rhs);
	}
	friend inline sum_set_traits_t operator^(const sum_set_traits_t& i_lhs, const ring_type& i_rhs)
	{
		return ddk::visit(module_prod_operation{},i_lhs,i_rhs);
	}
};

template<typename ... Modules>
using sum_module = typename sum_group<forget_mod<Modules>...>::template equip_with<sum_mod_operation<Modules...>>;

}


#include "cpn_module.inl"
