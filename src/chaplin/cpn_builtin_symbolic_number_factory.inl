
namespace cpn
{

template<typename ... Summands>
ddk::inherited_value<sum_symbolic_number> symbolic_sum(bool i_sign, Summands&& ... i_summands)
{
	typedef typename sum_symbolic_number::summand_list summand_list;

	return ddk::make_inherited_value<sum_symbolic_number>(summand_list{std::forward<Summands>(i_summands)...},i_sign);
}
template<typename Iterator>
ddk::inherited_value<sum_symbolic_number> symbolic_sum(Iterator itBegin,Iterator itEnd,bool i_sign)
{
	typedef typename sum_symbolic_number::summand_list summand_list;

	return ddk::make_inherited_value<sum_symbolic_number>(summand_list{itBegin,itEnd},i_sign);
}
template<typename ... Prods>
ddk::inherited_value<prod_symbolic_number> symbolic_prod(bool i_sign, Prods&& ... i_prods)
{
	typedef typename prod_symbolic_number::prod_list prod_list;

	return ddk::make_inherited_value<prod_symbolic_number>(prod_list{std::forward<Prods>(i_prods)...},i_sign);
}
template<typename Iterator>
ddk::inherited_value<prod_symbolic_number> symbolic_prod(Iterator itBegin,Iterator itEnd,bool i_sign)
{
	typedef typename prod_symbolic_number::prod_list prod_list;

	return ddk::make_inherited_value<prod_symbolic_number>(prod_list{itBegin,itEnd},i_sign);
}

}