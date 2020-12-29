#pragma once

#include "cpn_builtin_symbolic_numbers.h"
#include "ddk_inherited_value.h"

namespace cpn
{

inline ddk::inherited_value<rational_symbolic_number> integer(int i_number);
inline ddk::inherited_value<rational_symbolic_number> rational(int i_numerator, unsigned int i_denominator);
inline ddk::inherited_value<root_symbolic_number> root(unsigned int i_number, int i_rootNum, unsigned int i_rootDen = 1);
inline ddk::inherited_value<log_symbolic_number> log(unsigned int i_number,int i_logBase = 10);

}