
namespace cpn
{

constexpr integer_symbolic_literal integer(int i_value)
{
	return { i_value };
}
constexpr rational_symbolic_literal frac(int i_numerator, int i_denominator)
{
	return {i_numerator, i_denominator};
}
constexpr root_symbolic_literal root(int i_number,int i_degree)
{
	return {i_number,i_degree};
}
constexpr log_symbolic_literal log(int i_number,int i_logBase)
{
	return {i_number,i_logBase};
}

}