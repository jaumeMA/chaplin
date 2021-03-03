#pragma once

#include "cpn_free_module.h"
#include "cpn_vector_space.h"
#include "cpn_number_module.h"

namespace cpn
{

template<size_t Dim>
using real_free_module_n = free_module<real_module,canonical_basis_operation<real_module,Dim>>;

typedef real_free_module_n<1> real_free_module_1;
typedef real_free_module_n<2> real_free_module_2;
typedef real_free_module_n<3> real_free_module_3;
typedef real_free_module_n<4> real_free_module_4;

template<size_t Dim>
using R_n = vector_space<real_free_module_n<Dim>>;

typedef R_n<1> R1;
typedef R_n<2> R2;
typedef R_n<3> R3;
typedef R_n<4> R4;

}
