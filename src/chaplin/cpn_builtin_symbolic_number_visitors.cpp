#include "cpn_builtin_symbolic_number_visitors.h"
#include "cpn_builtin_symbolic_number_factory.h"

namespace cpn
{

typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::visit(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const
{
	return rational(i_lhs.numerator() * i_rhs.denominator() + i_lhs.denominator() * i_rhs.numerator(),i_lhs.denominator() * i_rhs.denominator());
}
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::visit(const rational_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const
{
	inherited_symbolic_number res;

	typename sum_symbolic_number::const_iterator itSummand = i_rhs.begin_summands();
	for(;itSummand!=i_rhs.end_summands();++itSummand)
	{
		if(res = ddk::visit(*this,ddk::make_inherited_value<const symbolic_number_interface>(share(i_lhs)),*itSummand))
		{
			break;
		}
	}

	return res;
}
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::visit(const rational_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const
{
	inherited_symbolic_number res;

	return res;
}

}