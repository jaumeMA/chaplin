#pragma once

#include "cpn_number_ring.h"
#include "cpn_field.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct rational_division
{
    PUBLISH_OPERATION_PROPERTIES(rational_division,div_operation,commutative,associative,distributive);

	friend inline rational_set operator/(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.denominator(), i_lhs.denominator() * i_rhs.numerator() };
	}
};

using rational_field = rational_ring::equip_with<rational_division>;

struct irrational_division
{
    PUBLISH_OPERATION_PROPERTIES(irrational_division,div_operation,commutative,associative,distributive);

	friend inline irrational_set operator/(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		const div_symbolic_number_visitor divVisitor;

		return ddk::visit(ddk::specialize(divVisitor,rational_symbolic_number(integer(i_lhs.numerator()),integer(i_lhs.denominator()))),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator/(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		const div_symbolic_number_visitor divVisitor;

		return ddk::visit(ddk::specialize(divVisitor,rational_symbolic_number(integer(i_rhs.numerator()),integer(i_rhs.denominator()))),share(i_lhs.get_number()));
	}
	friend inline irrational_set operator/(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		const div_symbolic_number_visitor divVisitor;

		return ddk::visit(divVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
};

using irrational_field = irrational_ring::equip_with<irrational_division>;

using real_field = sum_field<rational_field,irrational_field>;
using real = real_field;

template<size_t ... Dims>
using real_field_n = pow_field<real_field,Dims...>;

typedef real_field_n<1> real_field_1;
typedef real_field_n<2> real_field_2;
typedef real_field_n<3> real_field_3;
typedef real_field_n<4> real_field_4;

}
