#include "cpn_symbolic_number.h"
#include "ddk_static_visitor.h"

namespace cpn
{

size_t hash(const symbolic_number& i_number)
{
	return ddk::visit<detail::symbolic_number_hash_visitor>(i_number.m_number);
}

double symbolic_number::resolve(unsigned char i_accuracy) const
{
	//pending
	return 0;
}

}
