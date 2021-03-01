#pragma once

#include "cpn_linear_function.h"

namespace cpn
{

template<set_type Im, set_type Dom>
using function_set = function<Im(Dom)>;

template<free_module_type Im,free_module_type Dom>
using linear_function_set = linear_function<Im(Dom)>;

}