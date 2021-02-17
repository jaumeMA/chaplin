#include "cpn_math_functions.h"
#include <cmath>

namespace cpn
{
namespace detail
{

real_set sin(const real_set& i_number)
{
	return { std::sin(i_number.resolve()) };
}
real_set cos(const real_set& i_number)
{
	return { std::cos(i_number.resolve()) };
}
real_set tan(const real_set& i_number)
{
	return { std::tan(i_number.resolve()) };
}

}
}