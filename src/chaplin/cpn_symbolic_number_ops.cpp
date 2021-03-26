#include "cpn_symbolic_number.h"
#include "cpn_symbolic_number_ops.h"


#define SYMBOLIC_NUMBER_UNARY_OPERATOR_VISITOR(_NAME,_OP,_RETURN) \
struct _NAME##_symbolic_number_operator_visitor : public ddk::static_visitor<_RETURN> \
{ \
	template<typename T> \
	_RETURN operator()(T&& i_value) const \
	{ \
		return _OP i_value; \
	} \
};
#define SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(_NAME,_OP,_RETURN) \
struct _NAME##_symbolic_number_operator_visitor : public ddk::static_visitor<_RETURN> \
{ \
	template<typename T, typename TT> \
	_RETURN operator()(T&& i_lhs, TT&& i_rhs) const \
	{ \
		return i_lhs _OP i_rhs; \
	} \
};


namespace cpn
{
namespace
{

SYMBOLIC_NUMBER_UNARY_OPERATOR_VISITOR(add_inv,-,symbolic_number);
SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(less_than,<,bool);
SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(equal_to,==,bool);
SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(add,+,symbolic_number);
SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(subs,-,symbolic_number);
SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(prod,*,symbolic_number);
SYMBOLIC_NUMBER_BINARY_OPERATOR_VISITOR(div,/,symbolic_number);

}

bool operator<(const symbolic_number& i_lhs,const symbolic_number& i_rhs)
{
	return ddk::visit<less_than_symbolic_number_operator_visitor>(i_lhs.m_number,i_rhs.m_number);
}
bool operator==(const symbolic_number& i_lhs,const symbolic_number& i_rhs)
{
	return ddk::visit<equal_to_symbolic_number_operator_visitor>(i_lhs.m_number,i_rhs.m_number);
}
symbolic_number operator-(const symbolic_number& i_number)
{
	return ddk::visit<add_inv_symbolic_number_operator_visitor>(i_number.m_number);
}
symbolic_number operator+(const symbolic_number& i_lhs,const symbolic_number& i_rhs)
{
	return ddk::visit<add_symbolic_number_operator_visitor>(i_lhs.m_number,i_rhs.m_number);
}
symbolic_number operator-(const symbolic_number& i_lhs,const symbolic_number& i_rhs)
{
	return ddk::visit<subs_symbolic_number_operator_visitor>(i_lhs.m_number,i_rhs.m_number);
}
symbolic_number operator*(const symbolic_number& i_lhs,const symbolic_number& i_rhs)
{
	return ddk::visit<prod_symbolic_number_operator_visitor>(i_lhs.m_number,i_rhs.m_number);
}
symbolic_number operator/(const symbolic_number& i_lhs,const symbolic_number& i_rhs)
{
	return ddk::visit<div_symbolic_number_operator_visitor>(i_lhs.m_number,i_rhs.m_number);
}

}