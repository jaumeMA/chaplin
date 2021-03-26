#pragma once

#include "cpn_number_ring.h"
#include "cpn_field.h"

namespace cpn
{

struct rational_division
{
    PUBLISH_OPERATION_PROPERTIES(rational_division,div_operation,commutative,associative,distributive);

	friend inline rational_number operator/(const rational_number& i_lhs,const rational_number& i_rhs)
	{
		return i_lhs.number() / i_rhs.number();
	}
};

using rational_field = typename rational_ring::template equip_with<rational_division>;

template<size_t ... Dims>
using rational_field_n = pow_field<rational_field,Dims...>;

typedef rational_field_n<1> rational_field_1;
typedef rational_field_n<2> rational_field_2;
typedef rational_field_n<3> rational_field_3;
typedef rational_field_n<4> rational_field_4;

struct real_division
{
    PUBLISH_OPERATION_PROPERTIES(real_division,div_operation,commutative,associative,distributive);

	friend inline real_number operator/(const real_number& i_lhs,const real_number& i_rhs)
	{
		return i_lhs.number() / i_rhs.number();
	}
};

using real_field = typename real_ring::template equip_with<real_division>;

template<size_t ... Dims>
using real_field_n = pow_field<real_field,Dims...>;

typedef real_field_n<1> real_field_1;
typedef real_field_n<2> real_field_2;
typedef real_field_n<3> real_field_3;
typedef real_field_n<4> real_field_4;

}
