#include "cpn_number_set.h"
#include "cpn_builtin_symbolic_number_visitors.h"

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

}
