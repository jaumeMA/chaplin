
namespace cpn
{

template<typename Expression>
constexpr builtin_inverted_expression<Expression>::builtin_inverted_expression(const Expression& i_exp)
: m_exp(i_exp)
{
}
template<typename Expression>
constexpr const Expression& builtin_inverted_expression<Expression>::get() const
{
    return m_exp;
}

template<typename LhsFunction,typename RhsFunction>
constexpr builtin_composed_expression<LhsFunction,RhsFunction>::builtin_composed_expression(const LhsFunction& i_lhs,const RhsFunction& i_rhs)
: m_lhs(i_lhs)
, m_rhs(i_rhs)
{
}
template<typename LhsFunction,typename RhsFunction>
constexpr const LhsFunction& builtin_composed_expression<LhsFunction,RhsFunction>::get_lhs() const
{
    return m_lhs;
}
template<typename LhsFunction,typename RhsFunction>
constexpr const RhsFunction& builtin_composed_expression<LhsFunction,RhsFunction>::get_rhs() const
{
    return m_rhs;
}

template<typename T>
constexpr builtin_numeric_expression<T>::builtin_numeric_expression(const T& i_number)
: m_number(i_number)
{
}
template<typename T>
constexpr const T& builtin_numeric_expression<T>::get() const
{
    return m_number;
}

//template<size_t Comp>
//template<typename Type,typename ... Types>
//constexpr inline ddk::detail::component_builtin_function<Type,mpl::type_pack<Types...>> component_builtin_expression<Comp>::instance() const
//{
//    return {};
//}
template<size_t Comp>
TEMPLATE(typename T)
REQUIRED(IS_INSTANTIABLE(T))
constexpr builtin_composed_expression<component_builtin_expression<Comp>,T> component_builtin_expression<Comp>::operator()(const T& other) const
{
    return { *this, other };
}

}