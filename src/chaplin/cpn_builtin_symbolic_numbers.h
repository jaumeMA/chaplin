#pragma once

#include "cpn_symbolic_number_interface.h"
#include "ddk_inherited_value.h"
#include "ddk_visitable_type.h"
#include <forward_list>

namespace cpn
{

class rational_symbolic_number : public symbolic_number_interface
{
	DECLARE_TYPE_VISITABLE(rational_symbolic_number,symbolic_number_interface)

public:
	rational_symbolic_number(int i_numerator, unsigned int i_denominator);

	int numerator() const;
	unsigned int denominator() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	int m_numerator;
	unsigned int m_denominator;
};

class root_symbolic_number : public symbolic_number_interface
{
	DECLARE_TYPE_VISITABLE(root_symbolic_number,symbolic_number_interface)

public:
	root_symbolic_number(int i_number, int i_degree,bool i_sign = true);

	bool get_sign() const;
	int get_number() const;
	int get_degree() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	int m_number;
	int m_degree;
};

class log_symbolic_number : public symbolic_number_interface
{
	DECLARE_TYPE_VISITABLE(log_symbolic_number,symbolic_number_interface)

public:
	log_symbolic_number(unsigned int i_number, unsigned int i_logBase,bool i_sign = true);

	bool get_sign() const;
	unsigned int get_number() const;
	unsigned int get_base() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	unsigned int m_number;
	unsigned int m_logBase;
};

class sum_symbolic_number : public symbolic_number_interface
{
	DECLARE_TYPE_VISITABLE(sum_symbolic_number,symbolic_number_interface)

public:
	typedef std::forward_list<ddk::inherited_value<const symbolic_number_interface>> summand_list;
	typedef typename summand_list::const_iterator const_iterator;

	sum_symbolic_number(const ddk::inherited_value<const symbolic_number_interface>& i_lhs,const ddk::inherited_value<const symbolic_number_interface>& i_rhs,bool i_sign = true);
	sum_symbolic_number(summand_list i_summands,bool i_sign = true);

	bool get_sign() const;
	const summand_list& get_summands() const;
	const_iterator begin_summands() const;
	const_iterator end_summands() const;
	bool empty() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	summand_list m_summands;
};

class prod_symbolic_number: public symbolic_number_interface
{
	DECLARE_TYPE_VISITABLE(prod_symbolic_number,symbolic_number_interface)

public:
	typedef std::forward_list<ddk::inherited_value<const symbolic_number_interface>> prod_list;
	typedef typename prod_list::const_iterator const_iterator;

	prod_symbolic_number(const ddk::inherited_value<const symbolic_number_interface>& i_lhs,const ddk::inherited_value<const symbolic_number_interface>& i_rhs,bool i_sign = true);
	prod_symbolic_number(prod_list i_prods,bool i_sign = true);

	bool get_sign() const;
	const prod_list& get_prods() const;
	const_iterator begin_prods() const;
	const_iterator end_prods() const;
	bool empty() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	prod_list m_prods;
};

}