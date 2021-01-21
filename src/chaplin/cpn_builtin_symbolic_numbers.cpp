#include "cpn_builtin_symbolic_numbers.h"

namespace cpn
{

integer_symbolic_number::integer_symbolic_number(int i_number)
: m_number(i_number)
{
}
int integer_symbolic_number::number() const
{
    return m_number;
}
double integer_symbolic_number::resolve(unsigned char i_accuracy) const
{
    TODO("Pending");
    return 0.f;
}

rational_symbolic_number::rational_symbolic_number(inherited_symbolic_number i_numerator, inherited_symbolic_number i_denominator,bool i_sign)
: m_numerator(i_numerator)
, m_denominator(i_denominator)
, m_sign(i_sign)
{
}
inherited_symbolic_number rational_symbolic_number::numerator() const
{
    return m_numerator;
}
inherited_symbolic_number rational_symbolic_number::denominator() const
{
    return m_denominator;
}
bool rational_symbolic_number::sign() const
{
    return m_sign;
}
double rational_symbolic_number::resolve(unsigned char i_accuracy) const
{
    TODO("Pending");
    return 0.f;
}

root_symbolic_number::root_symbolic_number(inherited_symbolic_number i_number, inherited_symbolic_number i_degree,bool i_sign)
: m_number(i_number)
, m_degree(i_degree)
, m_sign(i_sign)
{
}
bool root_symbolic_number::sign() const
{
    return m_sign;
}
inherited_symbolic_number root_symbolic_number::number() const
{
    return m_number;
}
inherited_symbolic_number root_symbolic_number::degree() const
{
    return m_degree;
}
double root_symbolic_number::resolve(unsigned char i_accuracy) const
{
    TODO("Pending");
    return 0.f;
}

log_symbolic_number::log_symbolic_number(inherited_symbolic_number i_number, inherited_symbolic_number i_logBase,bool i_sign)
: m_number(i_number)
, m_base(i_logBase)
, m_sign(i_sign)
{
}
bool log_symbolic_number::sign() const
{
    return m_sign;
}
inherited_symbolic_number log_symbolic_number::number() const
{
    return m_number;
}
inherited_symbolic_number log_symbolic_number::base() const
{
    return m_base;
}
double log_symbolic_number::resolve(unsigned char i_accuracy) const
{
    TODO("Pending");
    return 0.f;
}

sum_symbolic_number::sum_symbolic_number(const inherited_symbolic_number& i_lhs,const inherited_symbolic_number& i_rhs,bool i_sign)
{
    m_summands.emplace_back(i_lhs);
    m_summands.emplace_back(i_rhs);
}
sum_symbolic_number::sum_symbolic_number(summand_list i_summands,bool i_sign)
: m_sign(i_sign)
{
    m_summands = std::move(i_summands);
}
bool sum_symbolic_number::sign() const
{
    return m_sign;
}
const typename sum_symbolic_number::summand_list& sum_symbolic_number::summands() const
{
    return m_summands;
}
typename sum_symbolic_number::const_iterator sum_symbolic_number::begin_summands() const
{
    return m_summands.begin();
}
typename sum_symbolic_number::const_iterator sum_symbolic_number::end_summands() const
{
    return m_summands.end();
}
size_t sum_symbolic_number::size() const
{
    return m_summands.size();
}
bool sum_symbolic_number::empty() const
{
    return m_summands.empty();
}
double sum_symbolic_number::resolve(unsigned char i_accuracy) const
{
    TODO("Pending");
    return 0.f;
}

prod_symbolic_number::prod_symbolic_number(const inherited_symbolic_number& i_lhs,const inherited_symbolic_number& i_rhs,bool i_sign)
{
    m_prods.emplace_back(i_lhs);
    m_prods.emplace_back(i_rhs);
}
prod_symbolic_number::prod_symbolic_number(prod_list i_prods,bool i_sign)
{
    m_prods = std::move(i_prods);
}
bool prod_symbolic_number::sign() const
{
    return m_sign;
}
const typename prod_symbolic_number::prod_list& prod_symbolic_number::prods() const
{
    return m_prods;
}
typename prod_symbolic_number::const_iterator prod_symbolic_number::begin_prods() const
{
    return m_prods.begin();
}
typename prod_symbolic_number::const_iterator prod_symbolic_number::end_prods() const
{
    return m_prods.end();
}
size_t prod_symbolic_number::size() const
{
    return m_prods.size();
}
bool prod_symbolic_number::empty() const
{
    return m_prods.empty();
}
double prod_symbolic_number::resolve(unsigned char i_accuracy) const
{
    TODO("Pending");
    return 0.f;
}

}
