#pragma once

#include "cpn_builtin_symbolic_numbers.h"
#include "ddk_concepts.h"
#include "ddk_type_concepts.h"

namespace cpn
{

class comparison_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef bool return_type;

	bool operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const;
	bool operator()(const rational_symbolic_number& i_lhs, const rational_symbolic_number& i_rhs) const;
	bool operator()(const log_symbolic_number& i_lhs,const log_symbolic_number& i_rhs) const;
	bool operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const;
	bool operator()(const sum_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const;
	bool operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const;
    TEMPLATE(typename T, typename TT)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_BASE_OF(symbolic_number_interface,TT))
    bool operator()(const T& i_lhs, const TT& i_rhs,...) const;
};

class neg_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef inherited_symbolic_number return_type;

	return_type operator()(const integer_symbolic_number& i_lhs) const;
	return_type operator()(const rational_symbolic_number& i_lhs) const;
	return_type operator()(const root_symbolic_number& i_lhs) const;
	return_type operator()(const log_symbolic_number& i_lhs) const;
	return_type operator()(const sum_symbolic_number& i_lhs) const;
	return_type operator()(const prod_symbolic_number& i_lhs) const;
};

class add_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef inherited_symbolic_number return_type;

	return_type operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const;
	return_type operator()(const rational_symbolic_number& i_lhs, const rational_symbolic_number& i_rhs) const;
	return_type operator()(const log_symbolic_number& i_lhs,const log_symbolic_number& i_rhs) const;
	return_type operator()(const sum_symbolic_number& i_lhs,const sum_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,sum_symbolic_number))
	return_type operator()(const T& i_lhs, const sum_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,sum_symbolic_number))
	return_type operator()(const sum_symbolic_number& i_lhs, const T& i_rhs) const;
	TEMPLATE(typename T,typename TT)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_BASE_OF(symbolic_number_interface,TT),IS_NOT_SAME_CLASS(T,sum_symbolic_number),IS_NOT_SAME_CLASS(TT,sum_symbolic_number))
	return_type operator()(const T& i_lhs, const TT& i_rhs,...) const;

private:
    mutable bool m_speculative = false;
};

class prod_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef inherited_symbolic_number return_type;

	return_type operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const;
	return_type operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const;
	return_type operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const;
	return_type operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,prod_symbolic_number))
	return_type operator()(const T& i_lhs,const prod_symbolic_number& i_rhs) const;
	TEMPLATE(typename T)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_NOT_SAME_CLASS(T,prod_symbolic_number))
	return_type operator()(const prod_symbolic_number& i_lhs,const T& i_rhs) const;
	TEMPLATE(typename T,typename TT)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_BASE_OF(symbolic_number_interface,TT),IS_NOT_SAME_CLASS(T,prod_symbolic_number),IS_NOT_SAME_CLASS(TT,prod_symbolic_number))
	return_type operator()(const T& i_lhs,const TT& i_rhs,...) const;

private:
    mutable bool m_speculative = false;
};

class div_symbolic_number_visitor : public ddk::dynamic_visitor<symbolic_number_interface>
{
public:
	typedef inherited_symbolic_number return_type;

	return_type operator()(const integer_symbolic_number& i_lhs, const integer_symbolic_number& i_rhs) const;
	return_type operator()(const rational_symbolic_number& i_lhs,const rational_symbolic_number& i_rhs) const;
	return_type operator()(const root_symbolic_number& i_lhs,const root_symbolic_number& i_rhs) const;
	return_type operator()(const prod_symbolic_number& i_lhs,const prod_symbolic_number& i_rhs) const;
	TEMPLATE(typename T,typename TT)
	REQUIRES(IS_BASE_OF(symbolic_number_interface,T),IS_BASE_OF(symbolic_number_interface,TT))
	return_type operator()(const T& i_lhs,const TT& i_rhs,...) const;
};


}

#include "cpn_builtin_symbolic_number_visitors.inl"
