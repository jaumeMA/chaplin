#pragma once

#include "cpn_number_group.h"
#include "cpn_ring.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct rational_ring_traits
{
    DECLARE_OPERATION_PROPERTIES(rational_ring_traits,commutative,associative,distributive);

	typedef rational_ring_traits ring_traits;

	static constexpr rational_set identity = {1,1};

	friend inline rational_set operator*(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.numerator(), i_lhs.denominator() * i_rhs.denominator() };
	}
};

using rational_ring = ring<rational_set,rational_group_traits,rational_ring_traits>;

struct irrational_ring_traits
{
    DECLARE_OPERATION_PROPERTIES(irrational_ring_traits,commutative,associative,distributive);

    typedef irrational_ring_traits ring_traits;

	friend inline irrational_set operator*(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(i_lhs.numerator(),i_lhs.denominator())),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator*(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(i_rhs.numerator(),i_rhs.denominator())),share(i_lhs.get_number()));
	}
	friend inline irrational_set operator*(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(prodVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
};

using irrational_ring = ring<irrational_set,irrational_group_traits,irrational_ring_traits>;

using real_ring = ring<real_set,sum_group_traits<rational_group,irrational_group>,sum_ring_traits<rational_ring,irrational_ring>>;

template<size_t ... Dims>
using real_ring_n = ring<pow_set<real_set,Dims...>,pow_group_traits<real_ring,Dims...>,pow_ring_traits<real_ring,Dims...>>;

typedef real_ring_n<1> real_ring_1;
typedef real_ring_n<2> real_ring_2;
typedef real_ring_n<3> real_ring_3;
typedef real_ring_n<4> real_ring_4;

}

