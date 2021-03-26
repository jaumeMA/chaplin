#pragma once

#include "cpn_builtin_symbolic_literals.h"

namespace cpn
{

constexpr integer_symbolic_literal integer(int i_value);
constexpr rational_symbolic_literal frac(int i_numerator, int i_denominator);
constexpr root_symbolic_literal root(int i_number,int i_degree);
constexpr log_symbolic_literal log(int i_number,int i_logBase);

}

#include "cpn_builtin_symbolic_literal_factory.inl"