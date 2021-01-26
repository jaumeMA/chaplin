#pragma once

#include "cpn_free_module.h"
#include "cpn_vector_space.h"

namespace cpn
{

template<size_t ... Dims>
using real_free_module_n = free_module<pow_module<real_module,Dims...>>;

typedef real_free_module_n<1> real_free_module_1;
typedef real_free_module_n<2> real_free_module_2;
typedef real_free_module_n<3> real_free_module_3;
typedef real_free_module_n<4> real_free_module_4;

template<size_t Dim>
using real_vector_space_n = vector_space<real_free_module_n<Dim>>;

typedef real_vector_space_n<1> real_vector_space_1;
typedef real_vector_space_n<2> real_vector_space_2;
typedef real_vector_space_n<3> real_vector_space_3;
typedef real_vector_space_n<4> real_vector_space_4;

}
