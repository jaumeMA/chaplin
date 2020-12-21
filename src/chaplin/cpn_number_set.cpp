#include "cpn_number_set.h"

namespace cpn
{

int rational_set::numerator() const
{
	return m_value.first;
}
int rational_set::denomnator() const
{
	return m_value.second;
}
rational_set::operator float() const
{
	return static_cast<float>(m_value.first) / static_cast<float>(m_value.second);
}

}