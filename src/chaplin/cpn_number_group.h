#pragma once

#include "cpn_number_set.h"
#include "cpn_group.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct rational_group_traits
{
	typedef rational_set set_traits;

	static constexpr set_traits identity = {1,1};

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
	typedef irrational_set set_traits;

	friend inline irrational_set operator+(const rational_set& i_lhs,const irrational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(ddk::specialize(addVisitor,rational_symbolic_number(i_lhs.numerator(),i_lhs.denominator())),i_rhs.get_number().get_impl());
	}
	friend inline irrational_set operator+(const irrational_set& i_lhs, const rational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(ddk::specialize(addVisitor,rational_symbolic_number(i_rhs.numerator(),i_rhs.denominator())),i_lhs.get_number().get_impl());
	}
	friend inline irrational_set operator+(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(addVisitor,i_lhs.get_number().get_impl(),i_rhs.get_number().get_impl());
	}
	friend inline irrational_set operator-(const irrational_set& i_lhs)
	{
		neg_symbolic_number_visitor negVisitor;

		return ddk::visit(negVisitor,i_lhs.get_number().get_impl());
	}
};

using irrational_group = group<irrational_set,irrational_group_traits>;

using real_group = group<real_set,sum_group_traits<rational_group_traits,irrational_group_traits>>;

}