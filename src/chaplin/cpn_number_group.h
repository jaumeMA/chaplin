#pragma once

#include "cpn_number_set.h"
#include "cpn_group.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct rational_addition
{
    PUBLISH_OPERATION_PROPERTIES(rational_addition,add_operation,commutative,associative,distributive);

	static constexpr rational_set identity = {0,1};

	friend inline rational_set operator+(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.denominator() + i_rhs.numerator() * i_lhs.denominator(),i_lhs.denominator() * i_rhs.denominator() };
	}
};

using rational_semi_group = semi_group<rational_set,rational_addition>;

struct rational_addition_inverse
{
	typedef rational_addition_inverse add_inverse_operation;

	friend inline rational_set operator-(const rational_set& i_rhs)
	{
		return { -i_rhs.denominator(), i_rhs.denominator() };
	}
};

using rational_group = rational_semi_group::template equip_with<rational_addition_inverse>;

struct irrational_addition
{
    PUBLISH_OPERATION_PROPERTIES(irrational_addition,add_operation,commutative,associative,distributive);

	friend inline irrational_set operator+(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(ddk::specialize(addVisitor,rational_symbolic_number(integer(i_lhs.numerator()),integer(i_lhs.denominator()))),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator+(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(ddk::specialize(addVisitor,rational_symbolic_number(integer(i_rhs.numerator()),integer(i_rhs.denominator()))),share(i_lhs.get_number()));
	}
	friend inline irrational_set operator+(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(addVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
};

using irrational_semi_group = semi_group<irrational_set,irrational_addition>;

struct irrational_addition_inverse
{
    typedef irrational_addition_inverse add_inverse_operation;

	friend inline irrational_set operator-(const irrational_set& i_lhs)
	{
		neg_symbolic_number_visitor negVisitor;

		return ddk::visit(negVisitor,share(i_lhs.get_number()));
	}
};

using irrational_group = irrational_semi_group::template equip_with<irrational_addition_inverse>;

using real_semi_group = sum_semi_group<rational_semi_group,irrational_semi_group>;
using real_group = sum_group<rational_group,irrational_group>;

template<size_t ... Dims>
using real_semi_group_n = pow_semi_group<real_semi_group,Dims...>;

typedef real_semi_group_n<1> real_semi_group_1;
typedef real_semi_group_n<2> real_semi_group_2;
typedef real_semi_group_n<3> real_semi_group_3;
typedef real_semi_group_n<4> real_semi_group_4;

template<size_t ... Dims>
using real_group_n = pow_group<real_group,Dims...>;

typedef real_group_n<1> real_group_1;
typedef real_group_n<2> real_group_2;
typedef real_group_n<3> real_group_3;
typedef real_group_n<4> real_group_4;

}
