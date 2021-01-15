#pragma once

#include "cpn_number_set.h"
#include "cpn_group.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct rational_group_traits
{
	typedef rational_group_traits group_traits;

	static constexpr rational_set identity = {0,1};

	friend inline rational_set operator+(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.denominator() + i_rhs.numerator() * i_lhs.denominator(), i_lhs.denominator() * i_rhs.denominator() };
	}
	friend inline rational_set operator-(const rational_set& i_rhs)
	{
		return { -i_rhs.denominator(), i_rhs.denominator() };
	}
};

using rational_group = group<rational_set,rational_group_traits>;

struct irrational_group_traits
{
    typedef irrational_group_traits group_traits;

	friend inline irrational_set operator+(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(ddk::specialize(addVisitor,rational_symbolic_number(i_lhs.numerator(),i_lhs.denominator())),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator+(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(ddk::specialize(addVisitor,rational_symbolic_number(i_rhs.numerator(),i_rhs.denominator())),share(i_lhs.get_number()));
	}
	friend inline irrational_set operator+(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(addVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
	friend inline irrational_set operator-(const irrational_set& i_lhs)
	{
		neg_symbolic_number_visitor negVisitor;

		return ddk::visit(negVisitor,share(i_lhs.get_number()));
	}
};

using irrational_group = group<irrational_set,irrational_group_traits>;

using real_group = group<real_set,sum_group_traits<rational_group,irrational_group>>;

template<size_t ... Dims>
using real_group_n = group<pow_set<real_set,Dims...>,pow_group_traits<real_group,Dims...>>;

typedef real_group_n<1> real_group_1;
typedef real_group_n<2> real_group_2;
typedef real_group_n<3> real_group_3;
typedef real_group_n<4> real_group_4;

}
