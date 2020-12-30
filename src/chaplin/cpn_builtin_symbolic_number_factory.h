#pragma once

#include "cpn_builtin_symbolic_numbers.h"
#include "ddk_inherited_value.h"
#include "ddk_concepts.h"
#include "ddk_type_concepts.h"

namespace cpn
{

ddk::inherited_value<rational_symbolic_number> integer(int i_number);
ddk::inherited_value<rational_symbolic_number> rational(int i_numerator, unsigned int i_denominator);
ddk::inherited_value<root_symbolic_number> root(unsigned int i_number, int i_degree, bool i_sign = true);
ddk::inherited_value<log_symbolic_number> log(unsigned int i_number,int i_logBase = 10, bool i_sign = true);
template<typename ... Summands>
inline ddk::inherited_value<sum_symbolic_number> symbolic_sum(bool i_sign, Summands&& ... i_summands);
template<typename Iterator>
inline ddk::inherited_value<sum_symbolic_number> symbolic_sum(Iterator itBegin,Iterator itEnd,bool i_sign = true);
template<typename ... Prods>
inline ddk::inherited_value<prod_symbolic_number> symbolic_prod(bool i_sign, Prods&& ... i_prods);
template<typename Iterator>
inline ddk::inherited_value<prod_symbolic_number> symbolic_prod(Iterator itBegin, Iterator itEnd,bool i_sign = true);

}

#include "cpn_builtin_symbolic_number_factory.inl"