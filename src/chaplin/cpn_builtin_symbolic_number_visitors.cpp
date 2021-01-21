#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

bool comparison_symbolic_number_visitor::operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const
{
    return i_lhs.number() == i_rhs.number();
}
bool comparison_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs, const rational_symbolic_number& i_rhs) const
{
    return ddk::visit(*this,i_lhs.numerator(),i_rhs.numerator()) && ddk::visit(*this,i_lhs.denominator(),i_rhs.denominator());
}
bool comparison_symbolic_number_visitor::operator()(const log_symbolic_number& i_lhs,const log_symbolic_number& i_rhs) const
{
    return ddk::visit(*this,i_lhs.number(),i_rhs.number()) && ddk::visit(*this,i_lhs.base(),i_rhs.base());
}
bool comparison_symbolic_number_visitor::operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const
{
    return ddk::visit(*this,i_lhs.number(),i_rhs.number()) && ddk::visit(*this,i_lhs.degree(),i_rhs.degree());
}
bool comparison_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const
{
    if(i_lhs.size() == i_rhs.size())
    {
        sum_symbolic_number::const_iterator itLhs = i_lhs.begin_summands();
        sum_symbolic_number::const_iterator itRhs = i_rhs.begin_summands();
        const sum_symbolic_number::const_iterator itLhsEnd = i_lhs.end_summands();
        const sum_symbolic_number::const_iterator itRhsEnd = i_rhs.end_summands();

        for(;itLhs!=itLhsEnd&&itRhs!=itRhsEnd;++itLhs,++itRhs)
        {
            if(ddk::visit(*this,*itLhs,*itRhs) == false)
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}
bool comparison_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const
{
    if(i_lhs.size() == i_rhs.size())
    {
        prod_symbolic_number::const_iterator itLhs = i_lhs.begin_prods();
        prod_symbolic_number::const_iterator itRhs = i_rhs.begin_prods();
        const prod_symbolic_number::const_iterator itLhsEnd = i_lhs.end_prods();
        const prod_symbolic_number::const_iterator itRhsEnd = i_rhs.end_prods();

        for(;itLhs!=itLhsEnd&&itRhs!=itRhsEnd;++itLhs,++itRhs)
        {
            if(ddk::visit(*this,*itLhs,*itRhs) == false)
            {
                return false;
            }
        }

        return true;
    }
    else
    {
        return false;
    }
}

inherited_symbolic_number neg_symbolic_number_visitor::operator()(const integer_symbolic_number& i_lhs) const
{
    return integer(-i_lhs.number());
}
inherited_symbolic_number neg_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs) const
{
	return rational(i_lhs.numerator(),i_lhs.denominator(),!i_lhs.sign());
}
inherited_symbolic_number neg_symbolic_number_visitor::operator()(const root_symbolic_number& i_lhs) const
{
	return root(i_lhs.number(),i_lhs.degree(),!i_lhs.sign());
}
inherited_symbolic_number neg_symbolic_number_visitor::operator()(const log_symbolic_number& i_lhs) const
{
	return log(i_lhs.number(),i_lhs.base(),!i_lhs.sign());
}
inherited_symbolic_number neg_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs) const
{
	return symbolic_sum(i_lhs.begin_summands(),i_lhs.end_summands(),!i_lhs.sign());
}
inherited_symbolic_number neg_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs) const
{
	return symbolic_prod(i_lhs.begin_prods(),i_lhs.end_prods(),!i_lhs.sign());
}

inherited_symbolic_number add_symbolic_number_visitor::operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const
{
    return integer(i_lhs.number() + i_rhs.number());
}
inherited_symbolic_number add_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const
{
    const prod_symbolic_number_visitor prodVisitor;

	return rational(ddk::visit(*this,ddk::visit(prodVisitor,i_lhs.numerator(),i_rhs.denominator()),ddk::visit(prodVisitor,i_lhs.denominator(),i_rhs.numerator())),ddk::visit(prodVisitor,i_lhs.denominator(),i_rhs.denominator()));
}
inherited_symbolic_number add_symbolic_number_visitor::operator()(const log_symbolic_number& i_lhs,const log_symbolic_number& i_rhs) const
{
	const inherited_symbolic_number lhsBase = i_lhs.base();
	const inherited_symbolic_number rhsBase = i_rhs.base();

    const comparison_symbolic_number_visitor compVisitor;
	if(ddk::visit(compVisitor,lhsBase,rhsBase))
	{
        const prod_symbolic_number_visitor prodVisitor;

		return log(ddk::visit(prodVisitor,i_lhs.number(),i_rhs.number()),lhsBase);
	}
	else
	{
		return symbolic_sum(share(i_lhs),share(i_rhs));
	}
}
inherited_symbolic_number add_symbolic_number_visitor::operator()(const sum_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const
{
	typename sum_symbolic_number::summand_list lhsSummands = i_lhs.summands();
	typename sum_symbolic_number::summand_list rhsSummands = i_rhs.summands();

	lhsSummands.insert(lhsSummands.end(),rhsSummands.begin(),rhsSummands.end());

	return ddk::make_inherited_value<sum_symbolic_number>(lhsSummands);
}

inherited_symbolic_number prod_symbolic_number_visitor::operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const
{
    return integer(i_lhs.number() * i_rhs.number());
}
inherited_symbolic_number prod_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const
{
    const prod_symbolic_number_visitor prodVisitor;

	return rational(ddk::visit(prodVisitor,i_lhs.numerator(),i_rhs.numerator()),ddk::visit(prodVisitor,i_lhs.denominator(),i_rhs.denominator()));
}
inherited_symbolic_number prod_symbolic_number_visitor::operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const
{
	const inherited_symbolic_number lhsNumber = i_lhs.number();
	const inherited_symbolic_number rhsNumber = i_rhs.number();

    const comparison_symbolic_number_visitor compVisitor;
	if(ddk::visit(compVisitor,lhsNumber,rhsNumber))
	{
        const add_symbolic_number_visitor addVisitor;

		return root(lhsNumber,ddk::visit(addVisitor,i_lhs.degree(),i_rhs.degree()));
	}
	else
	{
		return symbolic_sum(share(i_lhs),share(i_rhs));
	}
}
inherited_symbolic_number prod_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const
{
	typename prod_symbolic_number::prod_list lhsProds = i_lhs.prods();
	typename prod_symbolic_number::prod_list rhsProds = i_rhs.prods();

	lhsProds.insert(lhsProds.end(),rhsProds.begin(),rhsProds.end());

	return ddk::make_inherited_value<sum_symbolic_number>(lhsProds);
}

inherited_symbolic_number div_symbolic_number_visitor::operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const
{
    return rational(share(i_lhs),share(i_rhs));
}
inherited_symbolic_number div_symbolic_number_visitor::operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const
{
    const prod_symbolic_number_visitor prodVisitor;

    return rational(ddk::visit(prodVisitor,i_lhs.numerator(),i_rhs.denominator()),ddk::visit(prodVisitor,i_lhs.denominator(),i_rhs.numerator()));
}
inherited_symbolic_number div_symbolic_number_visitor::operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const
{
    const neg_symbolic_number_visitor negVisitor;

    return symbolic_prod(true,share(i_lhs),root(i_rhs.number(),ddk::visit(negVisitor,i_rhs.degree())));
}
inherited_symbolic_number div_symbolic_number_visitor::operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const
{
    return rational(share(i_lhs),share(i_rhs));
}

}
