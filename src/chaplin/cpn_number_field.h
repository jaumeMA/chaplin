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

template<size_t ... Dims>
using rational_field_n = pow_field<rational_field,Dims...>;

typedef rational_field_n<1> rational_field_1;
typedef rational_field_n<2> rational_field_2;
typedef rational_field_n<3> rational_field_3;
typedef rational_field_n<4> rational_field_4;

struct real_division
{
    PUBLISH_OPERATION_PROPERTIES(real_division,div_operation,commutative,associative,distributive);

	friend inline real_set operator/(const real_set& i_lhs,const real_set& i_rhs)
	{
		const div_symbolic_number_visitor divVisitor;

		return ddk::visit(divVisitor,share(i_lhs.number()),share(i_rhs.number()));
	}
};

using real_field = real_ring::equip_with<real_division>;

template<size_t ... Dims>
using real_field_n = pow_field<real_field,Dims...>;

typedef real_field_n<1> real_field_1;
typedef real_field_n<2> real_field_2;
typedef real_field_n<3> real_field_3;
typedef real_field_n<4> real_field_4;

using real = real_field;

template<size_t ... Dims>
using real_n = pow_field<real,Dims...>;

typedef real_n<1> real_1;
typedef real_n<2> real_2;
typedef real_n<3> real_3;
typedef real_n<4> real_4;

}
