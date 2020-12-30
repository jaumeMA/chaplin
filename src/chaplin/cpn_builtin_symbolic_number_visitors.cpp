#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

typename neg_symbolic_number_visitor::return_type neg_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs) const
{
	return rational(-i_lhs.numerator(),i_lhs.denominator());
}
typename neg_symbolic_number_visitor::return_type neg_symbolic_number_visitor::operator()(const root_symbolic_number& i_lhs) const
{
	return root(i_lhs.get_number(),i_lhs.get_degree(),!i_lhs.get_sign());
}
typename neg_symbolic_number_visitor::return_type neg_symbolic_number_visitor::operator()(const log_symbolic_number& i_lhs) const
{
	return log(i_lhs.get_number(),i_lhs.get_base(),!i_lhs.get_sign());
}
typename neg_symbolic_number_visitor::return_type neg_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs) const
{
	return symbolic_sum(i_lhs.begin_summands(),i_lhs.end_summands(),!i_lhs.get_sign());
}
typename neg_symbolic_number_visitor::return_type neg_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs) const
{
	return symbolic_prod(i_lhs.begin_prods(),i_lhs.end_prods(),!i_lhs.get_sign());
}

typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const
{
	return rational(i_lhs.numerator() * i_rhs.denominator() + i_lhs.denominator() * i_rhs.numerator(),i_lhs.denominator() * i_rhs.denominator());
}
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::operator()(const log_symbolic_number& i_lhs,const log_symbolic_number& i_rhs) const
{
	const int lhsBase = i_lhs.get_base();
	const int rhsBase = i_rhs.get_base();

	if(lhsBase == rhsBase)
	{
		return log(i_lhs.get_number() + i_rhs.get_number(),lhsBase);
	}
	else
	{
		return symbolic_sum(share(i_lhs),share(i_rhs));
	}
}
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const
{
	typename sum_symbolic_number::summand_list lhsSummands = i_lhs.get_summands();
	typename sum_symbolic_number::summand_list rhsSummands = i_rhs.get_summands();

	lhsSummands.insert_after(lhsSummands.end(),rhsSummands.begin(),rhsSummands.end());

	return ddk::make_inherited_value<sum_symbolic_number>(lhsSummands);
}

typename prod_symbolic_number_visitor::return_type prod_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const
{
	return rational(i_lhs.numerator() * i_rhs.numerator(),i_lhs.denominator() * i_rhs.denominator());
}
typename prod_symbolic_number_visitor::return_type prod_symbolic_number_visitor::operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const
{
	const int lhsNumber = i_lhs.get_number();
	const int rhsNumber = i_rhs.get_number();

	if(lhsNumber == rhsNumber)
	{
		return root(lhsNumber,i_lhs.get_degree() + i_rhs.get_degree());
	}
	else
	{
		return symbolic_sum(share(i_lhs),share(i_rhs));
	}
}
typename prod_symbolic_number_visitor::return_type prod_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const
{
	typename prod_symbolic_number::prod_list lhsProds = i_lhs.get_prods();
	typename prod_symbolic_number::prod_list rhsProds = i_rhs.get_prods();

	lhsProds.insert_after(lhsProds.end(),rhsProds.begin(),rhsProds.end());

	return ddk::make_inherited_value<sum_symbolic_number>(lhsProds);
}

}