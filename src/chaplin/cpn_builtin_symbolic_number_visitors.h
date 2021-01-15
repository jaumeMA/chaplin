#pragma once

#include "cpn_builtin_symbolic_numbers.h"
#include "ddk_concepts.h"
#include "ddk_type_concepts.h"

namespace cpn
{

class neg_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef inherited_symbolic_number return_type;

	return_type operator()(const rational_symbolic_number& i_lhs) const;
	return_type operator()(const root_symbolic_number& i_lhs) const;
	return_type operator()(const log_symbolic_number& i_lhs) const;
	return_type operator()(const sum_symbolic_number& i_lhs) const;
	return_type operator()(const prod_symbolic_number& i_lhs) const;
	template<typename T>
	return_type operator()(T&&) const;
};

class add_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef symbolic_number_interface type_interface;
	typedef inherited_symbolic_number return_type;

	return_type operator()(const rational_symbolic_number& i_lhs, const rational_symbolic_number& i_rhs) const;
	return_type operator()(const log_symbolic_number& i_lhs,const log_symbolic_number& i_rhs) const;
	return_type operator()(const sum_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_SAME_CLASS(T,sum_symbolic_number))
	return_type operator()(const T& i_lhs, const sum_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_SAME_CLASS(T,sum_symbolic_number))
	return_type operator()(const sum_symbolic_number& i_lhs, const T& i_rhs) const;
	TEMPLATE(typename T,typename TT)
	REQUIRES(IS_NOT_SAME_CLASS(T,sum_symbolic_number),IS_NOT_SAME_CLASS(TT,sum_symbolic_number))
	return_type operator()(const T& i_lhs, const TT& i_rhs,...) const;
};

class prod_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef symbolic_number_interface type_interface;
	typedef inherited_symbolic_number return_type;

	return_type operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const;
	return_type operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const;
	return_type operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_SAME_CLASS(T,prod_symbolic_number))
	return_type operator()(T&& i_lhs,const prod_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_NOT_SAME_CLASS(T,prod_symbolic_number))
	return_type operator()(const prod_symbolic_number& i_lhs,T&& i_rhs) const;
	TEMPLATE(typename T,typename TT)
	REQUIRES(IS_NOT_SAME_CLASS(T,prod_symbolic_number),IS_NOT_SAME_CLASS(TT,prod_symbolic_number))
	return_type operator()(const T& i_lhs,const TT& i_rhs,...) const;
};

}

#include "cpn_builtin_symbolic_number_visitors.inl"
