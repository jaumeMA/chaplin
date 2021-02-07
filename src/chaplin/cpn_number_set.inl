
namespace cpn
{

constexpr integer_set::integer_set(int i_num)
: m_value(i_num)
{
}
constexpr int integer_set::number() const
{
    return m_value;
}

constexpr rational_set::rational_set(const integer_set& i_value)
: m_value(i_value.number(),1)
{
}
constexpr rational_set::rational_set(int i_num, unsigned int i_den)
: m_value(i_num,i_den)
{
}

TEMPLATE(typename T)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T))
real_set::real_set(const ddk::inherited_value<const T>& i_number)
: m_number(i_number)
{
}

}
