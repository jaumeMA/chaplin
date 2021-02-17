#include "cpn_number_exceptions.h"

namespace cpn
{

bad_number::bad_number(BadNumErrorCode i_errorCode,const std::string& i_reason)
: m_errorCode(i_errorCode)
, m_reason(i_reason)
{
}
BadNumErrorCode bad_number::get_code() const noexcept
{
	return m_errorCode;
}
const char* bad_number::what() const noexcept
{
	return m_reason.c_str();
}

}