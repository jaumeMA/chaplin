#include "cpn_symbolic_number.h"

namespace cpn
{

symbolic_number::symbolic_number(const inherited_symbolic_number& i_number)
: m_impl(i_number)
{
}
double symbolic_number::resolve(unsigned char i_accuracy) const
{
	return m_impl->resolve(i_accuracy);
}

}