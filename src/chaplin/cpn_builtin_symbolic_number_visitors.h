#pragma once

#include "cpn_builtin_symbolic_numbers.h"

namespace cpn
{

class add_symbolic_number_visitor
{
public:
	typedef inherited_symbolic_number return_type;
	typedef ddk::tuple<rational_symbolic_number,sum_symbolic_number,prod_symbolic_number> considered_types;

	return_type visit(const rational_symbolic_number& i_lhs, const rational_symbolic_number& i_rhs) const;
	return_type visit(const rational_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const;
	return_type visit(const rational_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const;

	template<typename Type1, typename Type2>
	return_type visit(const Type1& i_lhs, const Type2& i_rhs);
};

}

#include "cpn_builtin_symbolic_number_visitors.inl"