
#include "cpn_number_exceptions.h"

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
constexpr rational_set::rational_set(double i_value)
: m_value(1,1)
{
    const int maxNum = 1000;
    const double fail_number = 0x7FFFFFFF;
    
    int first_column[2] = { 1,0 };
    unsigned int second_column[2] = { 0,1 };
    int ai = 0;

    while(second_column[0] * (ai = static_cast<int>(i_value)) + second_column[1] <= maxNum)
    {
        if(i_value == static_cast<double>(ai))
        {
            throw bad_number{ BadNumErrorCode::DivByZero, "Error while Converting float to rational number" };
        }
        if(i_value > fail_number)
        {
            throw bad_number{ BadNumErrorCode::RepresentationError, "Error while Converting float to rational number" };
        }

        int temp = first_column[0] * ai + first_column[1];
        first_column[1] = first_column[0];
        first_column[0] = temp;
        temp = second_column[0] * std::abs(ai) + second_column[1];
        second_column[1] = second_column[0];
        second_column[0] = static_cast<unsigned int>(temp);


        i_value = 1 / (i_value - static_cast<double>(ai));
    }

    /* now try other possibility */
    ai = (maxNum - first_column[1]) / first_column[0];
    m_value.first = first_column[0] * ai + first_column[1];
    m_value.second = second_column[0] * ai + second_column[1];
}

TEMPLATE(typename T)
REQUIRED(IS_BASE_OF(symbolic_number_interface,T))
real_set::real_set(const ddk::inherited_value<const T>& i_number)
: m_number(i_number)
{
}

}
