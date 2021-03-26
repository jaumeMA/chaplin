#include "cpn_builtin_symbolic_number_factory.h"


namespace cpn
{

ddk::inherited_value<const rational_symbolic_number> frac(inherited_symbolic_number i_numerator,inherited_symbolic_number i_denominator, bool i_sign)
{
	return ddk::make_inherited_value<const rational_symbolic_number>(i_numerator,i_denominator,i_sign);
}
ddk::inherited_value<const root_symbolic_number> root(inherited_symbolic_number i_number,inherited_symbolic_number i_degree, bool i_sign)
{
	return ddk::make_inherited_value<const root_symbolic_number>(i_number,i_degree,i_sign);
}
ddk::inherited_value<const log_symbolic_number> log(inherited_symbolic_number i_number,inherited_symbolic_number i_base, bool i_sign)
{
	return ddk::make_inherited_value<const log_symbolic_number>(i_number,i_base,i_sign);
}

}
