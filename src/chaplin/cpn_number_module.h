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
namespace detail
{

inline irrational_set mixed_module_operation(const rational_set& i_lhs,const irrational_set& i_rhs);
inline irrational_set mixed_module_operation(const irrational_set& i_lhs, const rational_set& i_rhs);

}

struct rational_module_operation
{
    PUBLISH_OPERATION_PROPERTIES(rational_module_operation,mod_operation,commutative,associative,distributive);

    typedef rational_ring ring_type;

	static constexpr rational_set identity = {1,1};

	friend inline rational_set operator^(const rational_set& i_lhs,const rational_set& i_rhs)
	{
		return { i_lhs.numerator() * i_rhs.numerator(), i_lhs.denominator() * i_rhs.denominator() };
	}
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_BASE_OF(rational_set,T))
	friend inline auto operator^(const rational_set& i_lhs, const T& i_rhs)
	{
	    return detail::mixed_module_operation(i_lhs,i_rhs);
	}
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_BASE_OF(rational_set,T))
	friend inline auto operator^(const T& i_lhs, const rational_set& i_rhs)
	{
	    return detail::mixed_module_operation(i_lhs,i_rhs);
	}
};

using rational_module = rational_group::equip_with<rational_module_operation>;

struct irrational_module_operation
{
    PUBLISH_OPERATION_PROPERTIES(irrational_module_operation,mod_operation,commutative,associative,distributive);

    typedef irrational_ring ring_type;

	friend inline irrational_set operator^(const irrational_set& i_lhs,const irrational_set& i_rhs)
	{
		prod_symbolic_number_visitor prodVisitor;

		return ddk::visit(prodVisitor,share(i_lhs.get_number()),share(i_rhs.get_number()));
	}
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_BASE_OF(irrational_set,T))
	friend inline auto operator^(const irrational_set& i_lhs, const T& i_rhs)
	{
	    return detail::mixed_module_operation(i_lhs,i_rhs);
	}
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_BASE_OF(irrational_set,T))
	friend inline auto operator^(const T& i_lhs, const irrational_set& i_rhs)
	{
	    return detail::mixed_module_operation(i_lhs,i_rhs);
	}
};

using irrational_module = irrational_group::equip_with<irrational_module_operation>;

using real_module = sum_module<rational_module,irrational_module>;

template<size_t ... Dims>
using real_module_n = pow_module<real_module,Dims...>;

typedef real_module_n<1> real_module_1;
typedef real_module_n<2> real_module_2;
typedef real_module_n<3> real_module_3;
typedef real_module_n<4> real_module_4;

}

#include "cpn_number_module.inl"
