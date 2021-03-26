#pragma once

#include "cpn_number_group.h"
#include "cpn_ring.h"

namespace cpn
{

struct integer_multiplication
{
    PUBLISH_OPERATION_PROPERTIES(integer_multiplication,mult_operation,commutative,associative,distributive);

	static constexpr integer_number identity = integer_number(1);
	static constexpr integer_number annihilator = integer_number(0);

	friend inline integer_number operator*(const integer_number& i_lhs,const integer_number& i_rhs)
	{
		return i_lhs.number() * i_rhs.number();
	}
};

using integer_semi_ring = typename integer_semi_group::template equip_with<integer_multiplication>;

template<size_t ... Dims>
using integer_semi_ring_n = pow_semi_ring<integer_semi_ring,Dims...>;

typedef integer_semi_ring_n<1> integer_semi_ring_1;
typedef integer_semi_ring_n<2> integer_semi_ring_2;
typedef integer_semi_ring_n<3> integer_semi_ring_3;
typedef integer_semi_ring_n<4> integer_semi_ring_4;

using integer_ring = integer_group::template equip_with<integer_multiplication>;

template<size_t ... Dims>
using integer_ring_n = pow_ring<integer_ring,Dims...>;

typedef integer_ring_n<1> integer_ring_1;
typedef integer_ring_n<2> integer_ring_2;
typedef integer_ring_n<3> integer_ring_3;
typedef integer_ring_n<4> integer_ring_4;

struct rational_multiplication
{
    PUBLISH_OPERATION_PROPERTIES(rational_multiplication,mult_operation,commutative,associative,distributive);

	static constexpr rational_number identity = rational_number{1,1};
	static constexpr rational_number annihilator = rational_number{0,1};

	friend inline rational_number operator*(const rational_number& i_lhs,const rational_number& i_rhs)
	{
		return i_lhs.number() * i_rhs.number();
	}
};

using rational_semi_ring = rational_semi_group::template equip_with<rational_multiplication>;

template<size_t ... Dims>
using rational_semi_ring_n = pow_semi_ring<rational_semi_ring,Dims...>;

typedef rational_semi_ring_n<1> rational_semi_ring_1;
typedef rational_semi_ring_n<2> rational_semi_ring_2;
typedef rational_semi_ring_n<3> rational_semi_ring_3;
typedef rational_semi_ring_n<4> rational_semi_ring_4;

using rational_ring = rational_group::template equip_with<rational_multiplication>;

template<size_t ... Dims>
using rational_ring_n = pow_ring<rational_ring,Dims...>;

typedef rational_ring_n<1> rational_ring_1;
typedef rational_ring_n<2> rational_ring_2;
typedef rational_ring_n<3> rational_ring_3;
typedef rational_ring_n<4> rational_ring_4;

struct real_multiplication
{
    PUBLISH_OPERATION_PROPERTIES(real_multiplication,mult_operation,commutative,associative,distributive);

	static const real_number identity;
	static const real_number annihilator;

	friend inline real_number operator*(const real_number& i_lhs,const real_number& i_rhs)
	{
		return i_lhs.number() * i_rhs.number();
	}
	friend inline real_number operator^(const real_number& i_lhs, size_t i_exp)
	{
		return i_lhs;
	}
};

using real_semi_ring = real_semi_group::template equip_with<real_multiplication>;

template<size_t ... Dims>
using real_semi_ring_n = pow_semi_ring<real_semi_ring,Dims...>;

typedef real_semi_ring_n<1> real_semi_ring_1;
typedef real_semi_ring_n<2> real_semi_ring_2;
typedef real_semi_ring_n<3> real_semi_ring_3;
typedef real_semi_ring_n<4> real_semi_ring_4;

using real_ring = typename real_group::template equip_with<real_multiplication>;

template<size_t ... Dims>
using real_ring_n = pow_ring<real_ring,Dims...>;

typedef real_ring_n<1> real_ring_1;
typedef real_ring_n<2> real_ring_2;
typedef real_ring_n<3> real_ring_3;
typedef real_ring_n<4> real_ring_4;

}

