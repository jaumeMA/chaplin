
#include "cpn_number_exceptions.h"

namespace cpn
{

TEMPLATE(typename ... Args)
REQUIRED(IS_CONSTRUCTIBLE(rational_symbolic_literal,Args...))
constexpr integer_number::integer_number(Args&& ... i_args)
: m_number(std::forward<Args>(i_args)...)
{
}
constexpr integer_symbolic_literal integer_number::number() const
{
	return m_number;
}

TEMPLATE(typename ... Args)
REQUIRED(IS_CONSTRUCTIBLE(rational_symbolic_literal,Args...))
constexpr rational_number::rational_number(Args&& ... i_args)
: m_number(std::forward<Args>(i_args)...)
{
}
constexpr rational_symbolic_literal rational_number::number() const
{
	return m_number;
}

}
