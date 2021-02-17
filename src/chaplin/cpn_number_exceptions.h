#pragma once

#include "ddk_scoped_enum.h"
#include <exception>
#include <string>

namespace cpn
{

SCOPED_ENUM_DECL(BadNumErrorCode,
				DivByZero,
				RepresentationError);

struct bad_number : public std::exception
{
public:
	bad_number(BadNumErrorCode i_errorCode, const std::string& i_reason);

	BadNumErrorCode get_code() const noexcept;
	const char* what() const noexcept;

private:
	BadNumErrorCode m_errorCode;
	std::string m_reason;
};

}