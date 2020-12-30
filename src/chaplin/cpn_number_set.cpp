#include "cpn_number_set.h"

namespace cpn
{

int rational_set::numerator() const
{
	return m_value.first;
}
int rational_set::denominator() const
{
	return m_value.second;
}
double rational_set::resolve(unsigned char i_accuracy) const
{
	return static_cast<float>(m_value.first) / static_cast<float>(m_value.second);
}

irrational_set::irrational_set(const symbolic_number& i_number)
: m_number(i_number)
{
}
symbolic_number irrational_set::get_number() const
{
	return m_number;
}

}