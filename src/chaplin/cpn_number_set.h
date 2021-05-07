#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_symbolic_number.h"
#include "cpn_metric_space.h"
#include "ddk_type_concepts.h"
#include "ddk_concepts.h"
#include <utility>

namespace cpn
{

struct integer_number
{
public:
	TEMPLATE(typename ... Args)
	REQUIRES(IS_CONSTRUCTIBLE(integer_symbolic_literal,Args...))
	constexpr integer_number(Args&& ... i_args);

	constexpr integer_symbolic_literal number() const;

private:
	const integer_symbolic_literal m_number;
};

struct integer_comparison_operation
{
	PUBLISH_OPERATION_PROPERTIES(integer_comparison_operation,comp_operation,totally_ordered);

	friend inline bool operator<(const integer_number& i_lhs,const integer_number& i_rhs)
	{
		return i_lhs.number() < i_rhs.number();
	}
	friend inline bool operator==(const integer_number& i_lhs,const integer_number& i_rhs)
	{
		return i_lhs.number() == i_rhs.number();
	}
	friend inline bool operator!=(const integer_number& i_lhs,const integer_number& i_rhs)
	{
		return (i_lhs.number() == i_rhs.number()) == false;
	}
};

using integer_set = typename algebraic_structure<integer_number>::template equip_with<integer_comparison_operation>;

struct rational_number
{
public:
	TEMPLATE(typename ... Args)
	REQUIRES(IS_CONSTRUCTIBLE(rational_symbolic_literal,Args...))
	constexpr rational_number(Args&& ... i_args);

	constexpr rational_symbolic_literal number() const;

private:
	const rational_symbolic_literal m_number;
};

struct rational_comparison_operation
{
	PUBLISH_OPERATION_PROPERTIES(rational_comparison_operation,comp_operation,totally_ordered);

	friend inline bool operator<(const rational_number& i_lhs,const rational_number& i_rhs)
	{
		return i_lhs.number() < i_rhs.number();
	}
	friend inline bool operator==(const rational_number& i_lhs,const rational_number& i_rhs)
	{
		return i_lhs.number() == i_rhs.number();
	}
	friend inline bool operator!=(const rational_number& i_lhs,const rational_number& i_rhs)
	{
		return (i_lhs.number() == i_rhs.number()) == false;
	}
};

using rational_set = typename algebraic_structure<rational_number>::template equip_with<rational_comparison_operation>;

struct real_number
{
	friend inline size_t hash(const real_number& i_number)
	{
		return hash(i_number.m_number);
	}

public:
	real_number() = default;
	real_number(const symbolic_number& i_number);

	real_number& operator=(const real_number& other);
	double resolve(unsigned char i_accuracy = 10) const;
	symbolic_number number() const;

private:
	const symbolic_number m_number;
};

struct real_comparison_operation
{
	PUBLISH_OPERATION_PROPERTIES(real_comparison_operation,comp_operation,totally_ordered);

	friend inline bool operator<(const real_number& i_lhs,const real_number& i_rhs)
	{
		return i_lhs.number() < i_rhs.number();
	}
	friend inline bool operator==(const real_number& i_lhs, const real_number& i_rhs)
	{
		return i_lhs.number() == i_rhs.number();
	}
	friend inline bool operator!=(const real_number& i_lhs,const real_number& i_rhs)
	{
		return i_lhs.number() == i_rhs.number();
	}
};

using real_set = typename algebraic_structure<real_number>::template equip_with<real_comparison_operation,metric_space_operation<real_number,abs_value_metric<real_number>>>;

}

#include "cpn_number_set.inl"
