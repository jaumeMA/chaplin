#pragma once

#include "cpn_symbolic_number_interface.h"
#include "ddkFramework/ddk_function.h"

namespace cpn
{

class symbolic_number
{
public:
	symbolic_number(const inherited_symbolic_number& i_number);

	double resolve(unsigned char i_accuracy) const;
	inherited_symbolic_number get_impl() const;

private:
	inherited_symbolic_number m_impl;
};

}

#include "cpn_builtin_symbolic_number_factory.h"