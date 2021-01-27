#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_module.h"
#include "cpn_number_group.h"
#include "cpn_number_ring.h"
#include "ddkFramework/ddk_iterable_algorithm.h"
#include "ddkFramework/ddk_concepts.h"
#include "ddkFramework/ddk_type_concepts.h"

namespace cpn
{

struct integer_module_operation
{
    PUBLISH_OPERATION_PROPERTIES(integer_module_operation,mod_operation,commutative,associative,distributive);

    typedef integer_ring ring_type;

	static constexpr ring_type identity = ring_type(ring_type::mult_operation::identity);

	friend inline integer_set operator^(const ring_type& i_lhs,const integer_set& i_rhs)
	{
		return i_lhs.number() * i_rhs.number();
	}
};

using integer_module = integer_group::equip_with<integer_module_operation>;

template<size_t ... Dims>
using integer_module_n = pow_module<integer_module,Dims...>;

typedef integer_module_n<1> integer_module_1;
typedef integer_module_n<2> integer_module_2;
typedef integer_module_n<3> integer_module_3;
typedef integer_module_n<4> integer_module_4;

struct rational_module_operation
{
    PUBLISH_OPERATION_PROPERTIES(rational_module_operation,mod_operation,commutative,associative,distributive);

    typedef rational_ring ring_type;

	static constexpr ring_type identity = ring_type(ring_type::mult_operation::identity);

	friend inline rational_set operator^(const ring_type& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.numerator(), i_lhs.denominator() * i_rhs.denominator() };
	}
};

using rational_module = rational_group::equip_with<rational_module_operation>;

template<size_t ... Dims>
using rational_module_n = pow_module<rational_module,Dims...>;

typedef rational_module_n<1> rational_module_1;
typedef rational_module_n<2> rational_module_2;
typedef rational_module_n<3> rational_module_3;
typedef rational_module_n<4> rational_module_4;

struct real_module_operation
{
    PUBLISH_OPERATION_PROPERTIES(real_module_operation,mod_operation,commutative,associative,distributive);

    typedef real_ring ring_type;

	static const ring_type identity;

	friend inline real_set operator^(const ring_type& i_lhs,const real_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(prodVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
};

using real_module = real_group::equip_with<real_module_operation>;

template<size_t ... Dims>
using real_module_n = pow_module<real_module,Dims...>;

typedef real_module_n<1> real_module_1;
typedef real_module_n<2> real_module_2;
typedef real_module_n<3> real_module_3;
typedef real_module_n<4> real_module_4;

}

#include "cpn_number_module.inl"
