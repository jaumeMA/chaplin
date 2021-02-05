#pragma once

#include "cpn_number_set.h"
#include "cpn_group.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

struct integer_addition
{
    PUBLISH_OPERATION_PROPERTIES(integer_addition,add_operation,commutative,associative,distributive);

	static constexpr integer_set identity = 0;

	friend inline integer_set operator+(const integer_set& i_lhs,const integer_set& i_rhs)
	{
		return i_lhs.number() + i_rhs.number();
	}
};

using integer_semi_group = semi_group<integer_set,integer_addition>;

template<size_t ... Dims>
using integer_semi_group_n = pow_semi_group<integer_semi_group,Dims...>;

typedef integer_semi_group_n<1> integer_semi_group_1;
typedef integer_semi_group_n<2> integer_semi_group_2;
typedef integer_semi_group_n<3> integer_semi_group_3;
typedef integer_semi_group_n<4> integer_semi_group_4;

struct integer_addition_inverse
{
    PUBLISH_OPERATION_PROPERTIES(integer_addition_inverse,add_inverse_operation);

	friend inline integer_set operator-(const integer_set& i_rhs)
	{
		return -i_rhs.number();
	}
};

using integer_group = integer_semi_group::template equip_with<integer_addition_inverse>;

template<size_t ... Dims>
using integer_group_n = pow_group<integer_group,Dims...>;

typedef integer_group_n<1> integer_group_1;
typedef integer_group_n<2> integer_group_2;
typedef integer_group_n<3> integer_group_3;
typedef integer_group_n<4> integer_group_4;

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

template<size_t ... Dims>
using rational_semi_group_n = pow_semi_group<rational_semi_group,Dims...>;

typedef rational_semi_group_n<1> rational_semi_group_1;
typedef rational_semi_group_n<2> rational_semi_group_2;
typedef rational_semi_group_n<3> rational_semi_group_3;
typedef rational_semi_group_n<4> rational_semi_group_4;

struct rational_addition_inverse
{
	typedef rational_addition_inverse add_inverse_operation;

	friend inline rational_set operator-(const rational_set& i_rhs)
	{
		return { -i_rhs.denominator(), i_rhs.denominator() };
	}
};

using rational_group = rational_semi_group::template equip_with<rational_addition_inverse>;

template<size_t ... Dims>
using rational_group_n = pow_group<rational_group,Dims...>;

typedef rational_group_n<1> rational_group_1;
typedef rational_group_n<2> rational_group_2;
typedef rational_group_n<3> rational_group_3;
typedef rational_group_n<4> rational_group_4;

struct real_addition
{
    PUBLISH_OPERATION_PROPERTIES(real_addition,add_operation,commutative,associative,distributive);

	friend inline real_set operator+(const real_set& i_lhs,const real_set& i_rhs)
	{
		add_symbolic_number_visitor addVisitor;

		return ddk::visit(addVisitor,share(i_lhs.number()),share(i_rhs.number()));
	}
};

using real_semi_group = semi_group<real_set,real_addition>;

template<size_t ... Dims>
using real_semi_group_n = pow_semi_group<real_semi_group,Dims...>;

typedef real_semi_group_n<1> real_semi_group_1;
typedef real_semi_group_n<2> real_semi_group_2;
typedef real_semi_group_n<3> real_semi_group_3;
typedef real_semi_group_n<4> real_semi_group_4;

struct real_addition_inverse
{
    PUBLISH_OPERATION_PROPERTIES(real_addition_inverse,add_inverse_operation);

	friend inline real_set operator-(const real_set& i_lhs)
	{
		neg_symbolic_number_visitor negVisitor;

		return ddk::visit(negVisitor,share(i_lhs.number()));
	}
};

using real_group = real_semi_group::template equip_with<real_addition_inverse>;

template<size_t ... Dims>
using real_group_n = pow_group<real_group,Dims...>;

typedef real_group_n<1> real_group_1;
typedef real_group_n<2> real_group_2;
typedef real_group_n<3> real_group_3;
typedef real_group_n<4> real_group_4;

}
