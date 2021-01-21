
#include "cpn_builtin_symbolic_number_factory.h"

namespace cpn
{

TEMPLATE(typename T)
REQUIRED(IS_BASE_OF(T,symbolic_number_interface),IS_NOT_SAME_CLASS(T,sum_symbolic_number))
inherited_symbolic_number add_symbolic_number_visitor::operator()(const T& i_lhs,const sum_symbolic_number& i_rhs) const
{
	typename sum_symbolic_number::summand_list newSummands = i_rhs.summands();

    this->m_speculative = true;

    sum_symbolic_number::const_iterator itSummand = newSummands.begin();
    sum_symbolic_number::const_iterator itEnd = newSummands.end();
    for(;itSummand!=itEnd;++itSummand)
    {
        if(inherited_symbolic_number newSummand = ddk::visit(ddk::specialize(*this,i_lhs),*itSummand))
        {
            newSummands.emplace_front(newSummand);

            return ddk::make_inherited_value<sum_symbolic_number>(newSummands);
        }
    }

	newSummands.emplace_back(share(i_lhs));

    this->m_speculative = false;

	return ddk::make_inherited_value<sum_symbolic_number>(newSummands);
}
TEMPLATE(typename T)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,sum_symbolic_number))
inherited_symbolic_number add_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs, const T& i_rhs) const
{
	typename sum_symbolic_number::summand_list newSummands = i_lhs.summands();

    this->m_speculative = true;

    sum_symbolic_number::const_iterator itSummand = newSummands.begin();
    sum_symbolic_number::const_iterator itEnd = newSummands.end();
    for(;itSummand!=itEnd;++itSummand)
    {
        if(inherited_symbolic_number newSummand = ddk::visit(ddk::specialize(*this,i_rhs),*itSummand))
        {
            newSummands.emplace_front(newSummand);

            return ddk::make_inherited_value<sum_symbolic_number>(newSummands);
        }
    }

	newSummands.emplace_back(share(i_rhs));

    this->m_speculative = false;

	return ddk::make_inherited_value<sum_symbolic_number>(newSummands);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,sum_symbolic_number),IS_NOT_SAME_CLASS(TT,sum_symbolic_number))
inherited_symbolic_number add_symbolic_number_visitor::operator()(const T& i_lhs,const TT& i_rhs,...) const
{
	return (this->m_speculative) ? ddk::inherited_value<sum_symbolic_number>() : ddk::make_inherited_value<sum_symbolic_number>(share(i_lhs),share(i_rhs));
}

TEMPLATE(typename T)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,prod_symbolic_number))
inherited_symbolic_number prod_symbolic_number_visitor::operator()(const T& i_lhs,const prod_symbolic_number& i_rhs) const
{
	typename prod_symbolic_number::prod_list newProds = i_rhs.prods();

    this->m_speculative = true;

    prod_symbolic_number::const_iterator itProd = newProds.begin();
    prod_symbolic_number::const_iterator itEnd = newProds.end();
    for(;itProd!=itEnd;++itProd)
    {
        if(inherited_symbolic_number newProd = ddk::visit(ddk::specialize(*this,i_lhs),*itProd))
        {
            newProds.emplace_front(newProd);

            return ddk::make_inherited_value<sum_symbolic_number>(newProds);
        }
    }

	newProds.emplace_back(share(i_lhs));

    this->m_speculative = false;

	return ddk::make_inherited_value<prod_symbolic_number>(newProds);
}
TEMPLATE(typename T)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,prod_symbolic_number))
inherited_symbolic_number prod_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs,const T& i_rhs) const
{
	typename prod_symbolic_number::prod_list newProds = i_lhs.prods();

    this->m_speculative = true;

    prod_symbolic_number::const_iterator itProd = newProds.begin();
    prod_symbolic_number::const_iterator itEnd = newProds.end();
    for(;itProd!=itEnd;++itProd)
    {
        if(inherited_symbolic_number newProd = ddk::visit(ddk::specialize(*this,i_rhs),*itProd))
        {
            newProds.emplace_front(newProd);

            return ddk::make_inherited_value<sum_symbolic_number>(newProds);
        }
    }

	newProds.emplace_back(share(i_rhs));

    this->m_speculative = false;

	return ddk::make_inherited_value<prod_symbolic_number>(newProds);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,prod_symbolic_number),IS_NOT_SAME_CLASS(TT,prod_symbolic_number))
inherited_symbolic_number prod_symbolic_number_visitor::operator()(const T& i_lhs,const TT& i_rhs,...) const
{
	return (this->m_speculative) ? ddk::inherited_value<prod_symbolic_number>() : ddk::make_inherited_value<prod_symbolic_number>(share(i_lhs),share(i_rhs));
}

TEMPLATE(typename T,typename TT)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T))
inherited_symbolic_number div_symbolic_number_visitor::operator()(const T& i_lhs,const TT& i_rhs,...) const
{
	return ddk::make_inherited_value<rational_symbolic_number>(share(i_lhs),share(i_rhs));
}

}
