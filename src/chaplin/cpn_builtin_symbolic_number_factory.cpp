#include "cpn_builtin_symbolic_number_factory.h"


namespace cpn
{

ddk::inherited_value<rational_symbolic_number> integer(int i_number)
{
	return ddk::make_inherited_value<rational_symbolic_number>(i_number,1);
}
ddk::inherited_value<rational_symbolic_number> rational(int i_numerator,unsigned int i_denominator)
{
	return ddk::make_inherited_value<rational_symbolic_number>(i_numerator,i_denominator);
}
ddk::inherited_value<root_symbolic_number> root(unsigned int i_number,int i_rootNum,unsigned int i_rootDen)
{
	return ddk::make_inherited_value<root_symbolic_number>(i_number,i_rootNum,i_rootDen);
}
ddk::inherited_value<log_symbolic_number> log(unsigned int i_number,int i_logBase)
{
	return ddk::make_inherited_value<log_symbolic_number>(i_number,i_logBase);
}

}