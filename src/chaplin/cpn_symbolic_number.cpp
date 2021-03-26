#include "cpn_symbolic_number.h"
#include "ddk_static_visitor.h"

namespace cpn
{
namespace
{

struct symbolic_number_hash_visitor : public ddk::static_visitor<size_t>
{
	template<typename T>
	size_t operator()(const T& i_number) const
	{
		return hash(i_number);
	}
};

}

size_t hash(const symbolic_number& i_number)
{
	return ddk::visit<symbolic_number_hash_visitor>(i_number.m_number);
}

double symbolic_number::resolve(unsigned char i_accuracy) const
{
	//pending
	return 0;
}

}
