#include "cpn_number_set.h"
#include "cpn_builtin_symbolic_number_visitors.h"

namespace cpn
{

int integer_set::resolve(unsigned char i_accuracy) const
{
    return m_value;
}
bool integer_set::operator==(const integer_set& other) const
{
    return m_value == other.m_value;
}

int rational_set::numerator() const
{
	return m_value.first;
}
unsigned int rational_set::denominator() const
{
	return m_value.second;
}
double rational_set::resolve(unsigned char i_accuracy) const
{
	return static_cast<float>(m_value.first) / static_cast<float>(m_value.second);
}
bool rational_set::operator==(const rational_set& other) const
{
    return (m_value.first == other.m_value.first) && (m_value.second == other.m_value.second);
}

real_set::real_set(const symbolic_number& i_number)
: m_number(i_number)
{
}
real_set::real_set(inherited_symbolic_number&& i_number)
: m_number(std::move(i_number))
{
}
symbolic_number real_set::get_number() const
{
	return m_number;
}
bool real_set::operator==(const real_set& other) const
{
    const comparison_symbolic_number_visitor compVisitor;

    return ddk::visit(compVisitor,share(m_number),share(other.m_number));
}

}
