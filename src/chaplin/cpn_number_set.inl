
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

}
