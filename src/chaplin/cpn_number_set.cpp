#include "cpn_number_set.h"

namespace cpn
{

real_number::real_number(const symbolic_number& i_number)
: m_number(i_number)
{
}
real_number& real_number::operator=(const real_number& other)
{
	return *this;
}
symbolic_number real_number::number() const
{
	return m_number;
}
double real_number::resolve(unsigned char i_accuracy) const
{
    return m_number.resolve(i_accuracy);
}

}
