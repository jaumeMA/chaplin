
namespace cpn
{

constexpr bool linearity_inspection(...)
{
	return false;
}
template<size_t ... Indexs,typename ... Expressions>
constexpr bool linearity_inspection(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp)
{
	return (linearity_inspection(i_exp.template get<Indexs>()) && ...);
}
template<size_t ... Indexs,typename ... Expressions>
constexpr bool linearity_inspection(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp)
{
	const size_t numConstant = (static_cast<size_t>(constant_inspection(i_exp.template get<Indexs>())) + ...);

	return (numConstant >= (ddk::mpl::num_types<Expressions...> - 1)) && (linearity_inspection(i_exp.template get<Indexs>()) && ...);
}
template<typename LhsFunction,typename RhsFunction>
constexpr bool linearity_inspection(const builtin_composed_expression<LhsFunction,RhsFunction>& i_exp)
{
	return linearity_inspection(i_exp.get_lhs()) && linearity_inspection(i_exp.get_rhs());
}
template<typename Expression>
constexpr bool linearity_inspection(const builtin_inverted_expression<Expression>& i_exp)
{
	return linearity_inspection(i_exp.get());
}
template<typename T,typename TT>
constexpr bool linearity_inspection(const T&)
{
	return T::__expression_properties::template contains<cnstant>() || T::__expression_properties::template contains<linear>();
}

constexpr bool constant_inspection(...)
{
	return false;
}
template<size_t ... Indexs,typename ... Expressions>
constexpr bool constant_inspection(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp)
{
	return (constant_inspection(i_exp.template get<Indexs>()) && ...);
}
template<size_t ... Indexs,typename ... Expressions>
constexpr bool constant_inspection(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp)
{
	return (constant_inspection(i_exp.template get<Indexs>()) && ...);
}
template<typename LhsFunction,typename RhsFunction>
constexpr bool constant_inspection(const builtin_composed_expression<LhsFunction,RhsFunction>& i_exp)
{
	return constant_inspection(i_exp.get_lhs()) && constant_inspection(i_exp.get_rhs());
}
template<typename Expression>
constexpr bool constant_inspection(const builtin_inverted_expression<Expression>& i_exp)
{
	return constant_inspection(i_exp.get());
}
template<typename T,typename TT>
constexpr bool constant_inspection(const T&)
{
	return T::__expression_properties::template contains<cnstant>();
}

}