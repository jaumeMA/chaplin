#pragma once

#include "cpn_number_set.h"
#include "cpn_group.h"

namespace cpn
{

struct rational_group_traits
{
	static constexpr rational_set identity = {1,1};

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
	static constexpr irrational_set identity = { };

	friend inline irrational_set operator+(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		//TBD
		return {};
		//return { i_lhs.numerator() * i_rhs.denominator() + i_rhs.numerator() * i_lhs.denominator(), i_lhs.denominator() * i_rhs.denominator() };
	}
	friend inline irrational_set operator-(const irrational_set& i_rhs)
	{
		//TBD
		return {};
		//return { -i_rhs.denominator(), i_rhs.denominator() };
	}
};

using irrational_group = group<irrational_set,irrational_group_traits>;

using real_group = sum_group<rational_group,irrational_group>;

}