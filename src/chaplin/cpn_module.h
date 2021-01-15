#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_group.h"
#include "cpn_ring.h"

namespace cpn
{

template<typename set, typename group_traits, typename module_traits>
using module = algebraic_structure<set,group_traits,module_traits>;

template<typename ring>
struct left_module_from_ring_traits : virtual public ring::set_traits
{
	typedef typename ring::set_traits set_traits;
	typedef left_module_from_ring_traits<ring> module_traits;

	static const set_traits identity;
	friend inline set_traits operator^(const ring& i_lhs,const module_traits& i_rhs)
	{
		return i_lhs * ring{static_cast<set_traits>(i_rhs)};
	}
};

template<typename ring>
struct right_module_from_ring_traits : virtual public ring::set_traits
{
	typedef typename ring::set_traits set_traits;
	typedef right_module_from_ring_traits<ring> module_traits;

	static const set_traits identity;
	friend inline set_traits operator^(const module_traits& i_lhs, const ring& i_rhs)
	{
		return ring{i_lhs} * i_rhs;
	}
};

template<typename ring>
struct module_from_ring_traits : virtual public ring::set_traits
{
    static_assert(ring::ring_traits::is_commutative, "You cannot create bilateral module from non commutative ring");

	typedef typename ring::set_traits set_traits;
	typedef module_from_ring_traits<ring> module_traits;

	static const set_traits identity;
	friend inline set_traits operator^(const ring& i_lhs,const module_traits& i_rhs)
	{
		return i_lhs * ring{static_cast<set_traits>(i_rhs)};
	}
	friend inline set_traits operator^(const module_traits& i_lhs, const ring& i_rhs)
	{
		return ring{i_lhs} * i_rhs;
	}
};

template<typename modules,size_t ... Dims>
struct pow_module_traits : virtual public pow_set<module<typename modules::set_traits,typename modules::group_traits,typename modules::module_traits>,Dims...>
{
    typedef typename modules::set_traits set_traits;
	typedef pow_set<module<typename modules::set_traits,typename modules::group_traits,typename modules::module_traits>,Dims...> pow_set_traits_t;
	typedef pow_module_traits<modules,Dims...> module_traits;

	static const set_traits identity;
	friend inline pow_set_traits_t operator^(const module_traits& i_lhs,const set_traits& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_transform([&i_rhs](const modules& i_value){ return i_value ^ i_rhs; },static_cast<pow_set_traits_t>(i_lhs));

		return res;
	}
	friend inline pow_set_traits_t operator^(const set_traits& i_lhs, const module_traits& i_rhs)
	{
		pow_set_traits_t res;

		res <<= ddk::trans::iterable_transform([&i_lhs](const modules& i_value){ return i_lhs ^ i_value; },static_cast<pow_set_traits_t>(i_rhs));

		return res;
	}
};

template<typename ring, typename ... modules>
struct sum_module_traits : virtual public sum_set<module<typename modules::set_traits,typename modules::group_traits,typename modules::module_traits> ...>
{
	typedef sum_set<module<typename modules::set_traits,typename modules::group_traits,typename modules::module_traits> ...> sum_set_traits_t;
	typedef sum_module_traits<modules...> module_traits;

	struct module_prod_operation : public ddk::static_visitor<sum_set_traits_t>
	{
    public:
	    module_prod_operation(const ring& i_ring);
		template<typename T>
		inline sum_set_traits_t operator()(T&& i_value) const;

    private:
        const ring& m_ring;
	};

	static const sum_set_traits_t identity;
	friend inline sum_set_traits_t operator^(const ring& i_lhs,const module_traits& i_rhs);
	{
		return ddk::visit(module_prod_operation{i_lhs},static_cast<const sum_set_traits_t&>(i_rhs));
	}
	friend inline sum_set_traits_t operator^(const module_traits& i_lhs, const ring& i_rhs)
	{
		return ddk::visit(module_prod_operation{i_rhs},static_cast<const sum_set_traits_t&>(i_lhs));
	}
};

}


#include "cpn_module.inl"
