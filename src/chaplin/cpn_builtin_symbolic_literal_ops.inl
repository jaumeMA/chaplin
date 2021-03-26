
namespace cpn
{

constexpr bool operator==(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
constexpr bool operator==(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
constexpr bool operator==(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
constexpr bool operator==(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
constexpr bool operator<(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return i_lhs.number() == i_rhs.number();
}
constexpr bool operator<(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return i_lhs.numerator() * i_rhs.denominator() < i_lhs.denominator() * i_rhs.numerator();
}

constexpr integer_symbolic_literal operator-(const integer_symbolic_literal& i_value)
{
	return { -i_value.number() };
}
constexpr rational_symbolic_literal operator-(const rational_symbolic_literal& i_value)
{
	return { -i_value.numerator(), i_value.denominator() };
}
constexpr root_symbolic_literal operator-(const root_symbolic_literal& i_value)
{
	return { i_value.number(),i_value.degree(), false };
}
constexpr log_symbolic_literal operator-(const log_symbolic_literal& i_value)
{
	return { i_value.number(),i_value.base(), false };
}

constexpr integer_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const integer_symbolic_literal& i_rhs)
{
	return { i_lhs.number() + i_rhs.number() };
}
constexpr rational_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const rational_symbolic_literal& i_rhs)
{
	return { i_lhs.number() * i_rhs.denominator() + i_rhs.numerator(), i_rhs.denominator() };
}
constexpr rational_symbolic_literal operator+(const rational_symbolic_literal& i_lhs, const integer_symbolic_literal& i_rhs)
{
	return { i_lhs.denominator() * i_rhs.number() + i_lhs.numerator(), i_lhs.denominator() };
}
constexpr rational_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs.numerator() * i_rhs.denominator() + i_rhs.numerator() * i_lhs.denominator(), i_lhs.denominator() * i_rhs.denominator() };
}

constexpr integer_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs.number() * i_rhs.number() };
}
constexpr rational_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs.number() * i_rhs.numerator(), i_rhs.denominator() };
}
constexpr rational_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_rhs.number() * i_lhs.numerator(), i_lhs.denominator() };
}
constexpr rational_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs.numerator() * i_rhs.numerator(), i_lhs.denominator() * i_rhs.denominator() };
}

constexpr rational_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs.number(),i_rhs.number() };
}
constexpr rational_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs.number() * i_rhs.denominator() ,i_rhs.numerator() };
}
constexpr rational_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs.numerator() ,i_rhs.number() * i_lhs.denominator() };
}
constexpr rational_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs.numerator() * i_rhs.denominator() ,i_lhs.denominator() * i_rhs.denominator() };
}

}