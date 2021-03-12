#pragma once

#include "cpn_number_field.h"
#include "cpn_metric_space.h"

namespace cpn
{

using real = metric_space<real_field,abs_value_metric<real_field>>;

template<size_t ... Dims>
using real_n = metric_space<pow_field<real,Dims...>,euclidean_metric<pow_field<real,Dims...>>>;

typedef real_n<1> real_1;
typedef real_n<2> real_2;
typedef real_n<3> real_3;
typedef real_n<4> real_4;

}