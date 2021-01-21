#pragma once

#include "cpn_builtin_symbolic_numbers.h"
#include "ddk_inherited_value.h"
#include "ddk_concepts.h"
#include "ddk_type_concepts.h"

namespace cpn
{

ddk::inherited_value<const integer_symbolic_number> integer(int i_number);
ddk::inherited_value<const rational_symbolic_number> rational(inherited_symbolic_number i_numerator, inherited_symbolic_number i_denominator, bool i_sign = true);
ddk::inherited_value<const root_symbolic_number> root(inherited_symbolic_number i_number, inherited_symbolic_number i_degree, bool i_sign = true);
ddk::inherited_value<const log_symbolic_number> log(inherited_symbolic_number i_number, inherited_symbolic_number i_base = ddk::make_inherited_value<const integer_symbolic_number>(10), bool i_sign = true);
template<typename ... Summands>
inline ddk::inherited_value<const sum_symbolic_number> symbolic_sum(bool i_sign, Summands&& ... i_summands);
template<typename Iterator>
inline ddk::inherited_value<const sum_symbolic_number> symbolic_sum(Iterator itBegin,Iterator itEnd,bool i_sign = true);
template<typename ... Prods>
inline ddk::inherited_value<const prod_symbolic_number> symbolic_prod(bool i_sign, Prods&& ... i_prods);
template<typename Iterator>
inline ddk::inherited_value<const prod_symbolic_number> symbolic_prod(Iterator itBegin, Iterator itEnd,bool i_sign = true);

}

#include "cpn_builtin_symbolic_number_factory.inl"
