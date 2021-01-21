#pragma once

#include "cpn_symbolic_number_interface.h"
#include "ddk_inherited_value.h"
#include <list>

namespace cpn
{

class integer_symbolic_number : public symbolic_number_interface
{
public:
	integer_symbolic_number(int i_number);

	int number() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	int m_number;

} PUBLISH_RTTI_INHERITANCE(integer_symbolic_number,symbolic_number_interface);

class rational_symbolic_number : public symbolic_number_interface
{
public:
	rational_symbolic_number(inherited_symbolic_number i_numerator, inherited_symbolic_number i_denominator,bool i_sign = true);

	inherited_symbolic_number numerator() const;
	inherited_symbolic_number denominator() const;
    bool sign() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	inherited_symbolic_number m_numerator;
	inherited_symbolic_number m_denominator;
    bool m_sign;

} PUBLISH_RTTI_INHERITANCE(rational_symbolic_number,symbolic_number_interface);

class root_symbolic_number : public symbolic_number_interface
{
public:
	root_symbolic_number(inherited_symbolic_number i_number, inherited_symbolic_number i_degree,bool i_sign = true);

	bool sign() const;
	inherited_symbolic_number number() const;
	inherited_symbolic_number degree() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	inherited_symbolic_number m_number;
	inherited_symbolic_number m_degree;

} PUBLISH_RTTI_INHERITANCE(root_symbolic_number,symbolic_number_interface);

class log_symbolic_number : public symbolic_number_interface
{
public:
	log_symbolic_number(inherited_symbolic_number i_number, inherited_symbolic_number i_logBase,bool i_sign = true);

	bool sign() const;
	inherited_symbolic_number number() const;
	inherited_symbolic_number base() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	inherited_symbolic_number m_number;
	inherited_symbolic_number m_base;

} PUBLISH_RTTI_INHERITANCE(log_symbolic_number,symbolic_number_interface);

class sum_symbolic_number : public symbolic_number_interface
{
public:
	typedef std::list<inherited_symbolic_number> summand_list;
	typedef typename summand_list::const_iterator const_iterator;

	sum_symbolic_number(const inherited_symbolic_number& i_lhs,const inherited_symbolic_number& i_rhs,bool i_sign = true);
	sum_symbolic_number(summand_list i_summands,bool i_sign = true);

	bool sign() const;
	const summand_list& summands() const;
	const_iterator begin_summands() const;
	const_iterator end_summands() const;
    size_t size() const;
	bool empty() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	summand_list m_summands;

} PUBLISH_RTTI_INHERITANCE(sum_symbolic_number,symbolic_number_interface);

class prod_symbolic_number: public symbolic_number_interface
{
public:
	typedef std::list<inherited_symbolic_number> prod_list;
	typedef typename prod_list::const_iterator const_iterator;

	prod_symbolic_number(const inherited_symbolic_number& i_lhs,const inherited_symbolic_number& i_rhs,bool i_sign = true);
	prod_symbolic_number(prod_list i_prods,bool i_sign = true);

	bool sign() const;
	const prod_list& prods() const;
	const_iterator begin_prods() const;
	const_iterator end_prods() const;
    size_t size() const;
	bool empty() const;

private:
	double resolve(unsigned char i_accuracy) const override;

	bool m_sign;
	prod_list m_prods;

} PUBLISH_RTTI_INHERITANCE(prod_symbolic_number,symbolic_number_interface);

}
