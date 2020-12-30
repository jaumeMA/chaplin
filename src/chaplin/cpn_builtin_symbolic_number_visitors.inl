
#include "cpn_builtin_symbolic_number_factory.h"

namespace cpn
{

TEMPLATE(typename T)
REQUIRED(IS_NOT_SAME_CLASS(T,sum_symbolic_number))
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::operator()(const T& i_lhs,const sum_symbolic_number& i_rhs) const
{
	typename sum_symbolic_number::summand_list newSummands = i_rhs.get_summands();

	newSummands.push_front(share(i_lhs));

	return ddk::make_inherited_value<sum_symbolic_number>(newSummands);
}
TEMPLATE(typename T)
REQUIRED(IS_NOT_SAME_CLASS(T,sum_symbolic_number))
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs, const T& i_rhs) const
{
	typename sum_symbolic_number::summand_list newSummands = i_lhs.get_summands();

	newSummands.push_front(share(i_rhs));

	return ddk::make_inherited_value<sum_symbolic_number>(newSummands);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_NOT_SAME_CLASS(T,sum_symbolic_number),IS_NOT_SAME_CLASS(TT,sum_symbolic_number))
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::operator()(const T& i_lhs,const TT& i_rhs,...) const
{
	return ddk::make_inherited_value<sum_symbolic_number>(share(i_lhs),share(i_rhs));
}

TEMPLATE(typename T)
REQUIRED(IS_NOT_SAME_CLASS(T,prod_symbolic_number))
typename prod_symbolic_number_visitor::return_type prod_symbolic_number_visitor::operator()(T&& i_lhs,const prod_symbolic_number& i_rhs) const
{
	typename prod_symbolic_number::prod_list newProds = i_rhs.get_prods();

	newProds.push_front(share(i_lhs));

	return ddk::make_inherited_value<prod_symbolic_number>(newProds);
}
TEMPLATE(typename T)
REQUIRED(IS_NOT_SAME_CLASS(T,prod_symbolic_number))
typename prod_symbolic_number_visitor::return_type prod_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs,T&& i_rhs) const
{
	typename prod_symbolic_number::prod_list newProds = i_lhs.get_prods();

	newProds.push_front(share(i_rhs));

	return ddk::make_inherited_value<prod_symbolic_number>(newProds);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_NOT_SAME_CLASS(T,prod_symbolic_number),IS_NOT_SAME_CLASS(TT,prod_symbolic_number))
typename prod_symbolic_number_visitor::return_type prod_symbolic_number_visitor::operator()(const T& i_lhs,const TT& i_rhs,...) const
{
	return ddk::make_inherited_value<prod_symbolic_number>(share(i_lhs),share(i_rhs));
}

}