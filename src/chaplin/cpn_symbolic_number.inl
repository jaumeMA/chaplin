
namespace cpn
{

TEMPLATE(typename T)
REQUIRES(IS_BASE_OF(symbolic_number_interface,T))
symbolic_number::symbolic_number(ddk::inherited_value<T>&& i_impl)
: m_impl(i_impl)
{
}
TEMPLATE(typename T)
REQUIRES(IS_BASE_OF(symbolic_number_interface,T))
symbolic_number& symbolic_number::operator=(ddk::inherited_value<T>&& i_impl)
{
    m_impl = i_impl;

    return *this;
}

}
