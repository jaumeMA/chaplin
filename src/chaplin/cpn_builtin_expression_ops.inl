
namespace cpn
{

template<typename T>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_exp)
{
	if constexpr (inverse_additive_type<T>)
	{
		return builtin_numeric_expression(-i_exp.get());
	}
	else
	{
		return builtin_inverted_expression(i_exp);
	}
}
template<size_t Comp>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_exp)
{
	return builtin_inverted_expression(i_exp);
}
template<typename ... Expressions>
constexpr  auto operator-(const add_nary_expression<Expressions...>& i_exp)
{
	return i_exp.apply([](auto&& i_value){ return -i_value;});
}
template<typename ... Expressions>
constexpr  auto operator-(const prod_nary_expression<Expressions...>& i_exp)
{
	return i_exp.apply([](auto&& i_value) { return -i_value; });
}
TEMPLATE(typename T)
REQUIRED(IS_INSTANTIABLE(T))
constexpr auto operator-(const T& i_exp)
{
	return builtin_inverted_expression(i_exp);
}

template<typename T>
constexpr auto operator+(const builtin_numeric_expression<T>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	if constexpr (closed_additive_type<T>)
	{
		return builtin_numeric_expression<T>{i_lhs.get() + i_rhs.get()};
	}
	else
	{
		return add_nary_expression{i_lhs,i_rhs};
	}
}
TEMPLATE(typename T,typename TT)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr auto operator+(const builtin_numeric_expression<T>& i_lhs,const T& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return builtin_numeric_expression(i_lhs.get() + i_rhs);
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
TEMPLATE(typename T,typename TT)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr auto operator+(const T& i_lhs,const builtin_numeric_expression<TT>& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return builtin_numeric_expression(i_lhs + i_rhs.get());
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
template<typename T,size_t Comp>
constexpr auto operator+(const builtin_numeric_expression<T>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
template<typename T,size_t Comp>
constexpr auto operator+(const component_builtin_expression<Comp>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
template<size_t Comp1,size_t Comp2>
constexpr auto operator+(const component_builtin_expression<Comp1>& i_lhs,const component_builtin_expression<Comp2>& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
TEMPLATE(typename T,size_t Comp)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const T& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	if constexpr (IS_NUMERIC_COND(T))
	{
		return builtin_numeric_expression(i_lhs) + i_rhs;
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
TEMPLATE(typename T,size_t Comp)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const component_builtin_expression<Comp>& i_lhs,const T& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return i_lhs + builtin_numeric_expression(i_rhs);
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const T& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return builtin_numeric_expression(i_lhs) + i_rhs;
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return i_lhs + builtin_numeric_expression(i_rhs);
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr auto operator+(const builtin_numeric_expression<T>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	if constexpr (ddk::mpl::is_among_types<builtin_numeric_expression<T>,Expressions...>)
	{
		return i_rhs.combine<ddk::mpl::nth_pos_of_type<builtin_numeric_expression<T>,Expressions...>>(i_lhs + i_rhs.template get<ddk::mpl::nth_pos_of_type<builtin_numeric_expression<T>,Expressions...>>());
	}
	else
	{
		return i_rhs.combine(i_lhs);
	}
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	if constexpr(ddk::mpl::is_among_types<builtin_numeric_expression<T>,Expressions...>)
	{
		return i_lhs.combine<ddk::mpl::nth_pos_of_type<builtin_numeric_expression<T>,Expressions...>>(i_rhs + i_lhs.template get<ddk::mpl::nth_pos_of_type<builtin_numeric_expression<T>,Expressions...>>());
	}
	else
	{
		return i_lhs.combine(i_lhs);
	}
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const T& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return builtin_numeric_expression(i_lhs) + i_rhs;
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED_COND(IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T))
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T))
	{
		return i_lhs + builtin_numeric_expression(i_rhs);
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const builtin_numeric_expression<T>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr auto operator+(const component_builtin_expression<Comp>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const component_builtin_expression<Comp>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator+(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
template<typename Expression,typename EExpression>
constexpr  auto operator+(const Expression& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
template<typename Expression,typename EExpression>
constexpr  auto operator+(const builtin_inverted_expression<Expression>& i_lhs,const EExpression& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
template<typename Expression,typename EExpression>
constexpr  auto operator+(const builtin_inverted_expression<Expression>& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs)
{
	return add_nary_expression{ i_lhs,i_rhs };
}
TEMPLATE(typename T,typename TT)
REQUIRED_COND((IS_NUMERIC_COND(T) || IS_INSTANTIABLE_COND(T)) && (IS_NUMERIC_COND(TT) || IS_INSTANTIABLE_COND(TT)))
constexpr auto operator+(const T& i_lhs,const TT& i_rhs)
{
	if constexpr(IS_NUMERIC_COND(T) && IS_NUMERIC_COND(TT))
	{
		return builtin_numeric_expression(i_lhs + i_rhs);
	}
	else
	{
		return add_nary_expression{ i_lhs,i_rhs };
	}
}

template<typename T>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	if constexpr(closed_substractive_type<T>)
	{
		return builtin_numeric_expression<T>{i_lhs.get() - i_rhs.get()};
	}
	else
	{
		return add_nary_expression{ i_lhs, -i_rhs };
	}
}
template<typename T,size_t Comp>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return add_nary_expression{ i_lhs,-i_rhs };
}
TEMPLATE(typename T,size_t Comp)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator-(const T& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return builtin_numeric_expression(i_lhs) - i_rhs;
}
TEMPLATE(typename T,size_t Comp)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const T& i_rhs)
{
	return i_lhs - builtin_numeric_expression(i_rhs);
}
template<typename T,size_t Comp>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return add_nary_expression{ i_lhs,-i_rhs };
}
template<size_t Comp1,size_t Comp2>
constexpr  auto operator-(const component_builtin_expression<Comp1>& i_lhs,const component_builtin_expression<Comp2>& i_rhs)
{
	return add_nary_expression{ i_lhs,-i_rhs };
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator-(const T& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return builtin_numeric_expression(i_lhs) - i_rhs;
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs)
{
	return i_lhs - builtin_numeric_expression(i_rhs);
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_lhs + -i_rhs;
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator-(const T& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return builtin_numeric_expression(i_lhs) - i_rhs;
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs)
{
	return i_lhs - builtin_numeric_expression(i_rhs);
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const builtin_numeric_expression<T>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_lhs + -i_rhs;
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_lhs + -i_rhs;
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return (-i_rhs).combine(i_rhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const component_builtin_expression<Comp>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_lhs + -i_rhs;
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator-(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_lhs.combine(-i_rhs);
}
template<typename Expression,typename EExpression>
constexpr  auto operator-(const builtin_inverted_expression<Expression>& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs)
{
	return prod_nary_expression{ i_lhs,i_rhs.get() };
}
template<typename Expression,typename EExpression>
constexpr  auto operator-(const Expression& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs)
{
	return prod_nary_expression{ i_lhs,i_rhs.get() };
}
template<typename Expression,typename EExpression>
constexpr  auto operator-(const builtin_inverted_expression<Expression>& i_lhs,const EExpression& i_rhs)
{
	return prod_nary_expression{ i_lhs,builtin_inverted_expression{i_rhs} };
}

template<typename T>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	if constexpr(closed_multiplicative_type<T>)
	{
		return builtin_numeric_expression<T>{i_lhs.get() * i_rhs.get()};
	}
	else
	{
		return prod_nary_expression{ i_lhs, i_rhs };
	}
}
TEMPLATE(typename T,size_t Comp)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator*(const T& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return builtin_numeric_expression(i_lhs) * i_rhs;
}
TEMPLATE(typename T,size_t Comp)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const T& i_rhs)
{
	return i_lhs * builtin_numeric_expression(i_rhs);
}
template<typename T,size_t Comp>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return prod_nary_expression{ i_lhs, i_rhs };
}
template<typename T,size_t Comp>
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return prod_nary_expression{ i_lhs, i_rhs };
}
template<size_t Comp1,size_t Comp2>
constexpr  auto operator*(const component_builtin_expression<Comp1>& i_lhs,const component_builtin_expression<Comp2>& i_rhs)
{
	return prod_nary_expression{ i_lhs, i_rhs };
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator*(const T& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return builtin_numeric_expression(i_lhs) * i_rhs;
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs)
{
	return i_lhs * builtin_numeric_expression(i_rhs);
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return add_nary_expression{ i_lhs * i_rhs.template get<Indexs>()...};
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return add_nary_expression{ i_lhs.template get<Indexs>() * i_rhs ... };
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator*(const T& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return builtin_numeric_expression(i_lhs) * i_rhs;
}
TEMPLATE(typename T,size_t ... Indexs,typename ... Expressions)
REQUIRED(IS_NUMERIC(T))
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const T& i_rhs)
{
	return i_lhs * builtin_numeric_expression(i_rhs);
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const builtin_numeric_expression<T>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<typename T,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const builtin_numeric_expression<T>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return add_nary_expression{ i_rhs.template get<Indexs>() * i_lhs ... };
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return add_nary_expression{ i_lhs.template get<Indexs>() * i_rhs ... };
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return (add_nary_expression{ i_lhs.template get<Indexs>() * i_rhs } && ...);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return add_nary_expression{ i_lhs.template get<Indexs>() * i_rhs ...};
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const add_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return add_nary_expression{ i_lhs * i_rhs.template get<IIndexs>() ... };
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const component_builtin_expression<Comp>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<size_t Comp,size_t ... Indexs,typename ... Expressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const component_builtin_expression<Comp>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<size_t ... Indexs,typename ... Expressions,size_t ... IIndexs,typename ... EExpressions>
constexpr  auto operator*(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_lhs,const prod_nary_expression<ddk::mpl::sequence<IIndexs...>,EExpressions...>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<typename Expression,typename EExpression>
constexpr  auto operator*(const Expression& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs)
{
	return prod_nary_expression{ i_lhs,i_rhs };
}
template<typename Expression,typename EExpression>
constexpr  auto operator*(const builtin_inverted_expression<Expression>& i_lhs,const EExpression& i_rhs)
{
	return prod_nary_expression{ i_lhs,i_rhs };
}
template<typename Expression,typename EExpression>
constexpr  auto operator*(const builtin_inverted_expression<Expression>& i_lhs,const builtin_inverted_expression<EExpression>& i_rhs)
{
	return prod_nary_expression{ i_lhs,i_rhs };
}

}