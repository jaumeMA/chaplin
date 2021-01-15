#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_module.h"
#include "cpn_number_group.h"
#include "cpn_number_ring.h"
#include "ddkFramework/ddk_iterable_algorithm.h"

namespace cpn
{

struct rational_module_traits
{
	typedef rational_module_traits module_traits;

	static constexpr rational_set identity = {1,1};

	friend inline rational_set operator^(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.numerator(), i_lhs.denominator() * i_rhs.denominator() };
	}
};

using rational_module = ring<rational_set,rational_group_traits,rational_module_traits>;

struct irrational_module_traits
{
    typedef irrational_module_traits module_traits;

	friend inline irrational_set operator^(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(i_lhs.numerator(),i_lhs.denominator())),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator^(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(i_rhs.numerator(),i_rhs.denominator())),share(i_lhs.get_number()));
	}
	friend inline irrational_set operator^(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(prodVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
};

using irrational_module = module<irrational_set,irrational_group_traits,irrational_module_traits>;

using real_module = module<real_set,typename real_group::group_traits,module_from_ring_traits<real_ring>>;

template<size_t ... Dims>
using real_module_n = module<pow_set<real_set,Dims...>,pow_group_traits<real_group,Dims...>,pow_module_traits<real_module,Dims...>>;

typedef real_module_n<1> real_module_1;
typedef real_module_n<2> real_module_2;
typedef real_module_n<3> real_module_3;
typedef real_module_n<4> real_module_4;

}
