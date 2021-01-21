#pragma once

#include "cpn_number_group.h"
#include "cpn_ring.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct rational_multiplication
{
    PUBLISH_OPERATION_PROPERTIES(rational_multiplication,commutative,associative,distributive);

	typedef rational_multiplication mult_operation;

	static constexpr rational_set identity = {1,1};

	friend inline rational_set operator*(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.numerator(), i_lhs.denominator() * i_rhs.denominator() };
	}
};

using rational_semi_ring = rational_semi_group::equip_with<rational_multiplication>;
using rational_ring = rational_group::equip_with<rational_multiplication>;

struct irrational_multiplication
{
    PUBLISH_OPERATION_PROPERTIES(irrational_multiplication,commutative,associative,distributive);

    typedef irrational_multiplication mult_operation;

	friend inline irrational_set operator*(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(integer(i_lhs.numerator()),integer(i_lhs.denominator()))),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator*(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(integer(i_rhs.numerator()),integer(i_rhs.denominator()))),share(i_lhs.get_number()));
	}
	friend inline irrational_set operator*(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(prodVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
};

using irrational_semi_ring = irrational_semi_group::equip_with<irrational_multiplication>;
using irrational_ring = irrational_group::equip_with<irrational_multiplication>;

using real_semi_ring = sum_ring<rational_semi_ring,irrational_semi_ring>;
using real_ring = sum_ring<rational_ring,irrational_ring>;

template<size_t ... Dims>
using real_ring_n = pow_ring<real_ring,Dims...>;

typedef real_ring_n<1> real_ring_1;
typedef real_ring_n<2> real_ring_2;
typedef real_ring_n<3> real_ring_3;
typedef real_ring_n<4> real_ring_4;

}

