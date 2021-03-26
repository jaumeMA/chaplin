
namespace cpn
{
namespace detail
{

template<size_t Type>
cpn::SymbolicLiteralType symbolic_literal<Type>::get_type()
{
	return SymbolicLiteralType{Type};
}

template<typename T>
constexpr bool symbolic_literal_operand<T>::summand_less::operator()(const T& i_lhs,const T& i_rhs) const
{
	return hash(i_lhs) < hash(i_rhs);
}

template<typename T>
TEMPLATE(typename ... Args)
REQUIRED(IS_CONSTRUCTIBLE(T,Args...))
symbolic_literal_operand<T>::symbolic_literal_operand(Args&& ... i_args)
{
	m_operand.emplace(std::forward<Args>(i_args)...);
}
template<typename T>
template<typename ... Args>
bool symbolic_literal_operand<T>::emplace(Args&& ... i_args)
{
	m_operand.emplace(std::forward<Args>(i_args)...);

	return true;
}
template<typename T>
typename symbolic_literal_operand<T>::iterator symbolic_literal_operand<T>::begin()
{
	return m_operand.begin();
}
template<typename T>
typename symbolic_literal_operand<T>::const_iterator symbolic_literal_operand<T>::begin() const
{
	return m_operand.begin();
}
template<typename T>
template<typename ... Args>
typename symbolic_literal_operand<T>::iterator symbolic_literal_operand<T>::insert(iterator itPos,Args&& ... i_args)
{
	return m_operand.insert(itPos,T{ std::forward<Args>(i_args) ... });
}
template<typename T>
typename symbolic_literal_operand<T>::iterator symbolic_literal_operand<T>::end()
{
	return m_operand.end();
}
template<typename T>
typename symbolic_literal_operand<T>::const_iterator symbolic_literal_operand<T>::end() const
{
	return m_operand.end();
}

}

constexpr integer_symbolic_literal::integer_symbolic_literal(int i_number)
: m_number(i_number)
{
}
constexpr integer_symbolic_literal::integer_symbolic_literal(const integer_symbolic_literal& other)
: m_number(other.m_number)
{
}
constexpr int integer_symbolic_literal::number() const
{
	return m_number;
}

constexpr rational_symbolic_literal::rational_symbolic_literal(int i_numerator, int i_denominator)
: m_numerator(i_numerator)
, m_denominator(i_denominator)
{
}
constexpr int rational_symbolic_literal::numerator() const
{
	return m_numerator;
}
constexpr int rational_symbolic_literal::denominator() const
{
	return m_denominator;
}

constexpr root_symbolic_literal::root_symbolic_literal(int i_number,int i_degree, bool i_positive)
: m_number(i_number)
, m_degree(i_degree)
, m_sign(i_positive)
{
}
constexpr int root_symbolic_literal::number() const
{
	return m_number;
}
constexpr int root_symbolic_literal::degree() const
{
	return m_degree;
}
constexpr bool root_symbolic_literal::positive() const
{
	return m_sign;
}

constexpr log_symbolic_literal::log_symbolic_literal(int i_number,int i_logBase, bool i_positive)
: m_number(i_number)
, m_base(i_logBase)
, m_sign(i_positive)
{
}
constexpr int log_symbolic_literal::number() const
{
	return m_number;
}
constexpr int log_symbolic_literal::base() const
{
	return m_base;
}
constexpr bool log_symbolic_literal::positive() const
{
	return m_sign;
}

template<size_t Type,typename ... BuildingBlocks>
template<typename Callable>
grouped_symbolic_literal<Type,BuildingBlocks...>::operand_visitor<Callable>::operand_visitor(const Callable& i_callable)
: m_callable(i_callable)
{
}
template<size_t Type,typename ... BuildingBlocks>
template<typename Callable>
template<typename T,typename>
bool grouped_symbolic_literal<Type,BuildingBlocks...>::operand_visitor<Callable>::operator()(T&& i_value) const
{
	nested_enumerate(std::forward<T>(i_value),m_callable);

	return true;
}
template<size_t Type,typename ... BuildingBlocks>
template<typename Callable>
bool grouped_symbolic_literal<Type,BuildingBlocks...>::operand_visitor<Callable>::operator()(...) const
{
	//do nothing
	return true;
}

template<size_t Type, typename ... BuildingBlocks>
TEMPLATE(typename ... T)
REQUIRED(IS_CONSTRUCTIBLE(sum_symbolic_literal::symbolic_literal_t,T)...)
grouped_symbolic_literal<Type,BuildingBlocks...>::grouped_symbolic_literal(const T& ... i_lhs)
{
	( m_operands.emplace(T::get_type(),i_lhs).second && ...);
}
template<size_t Type, typename ... BuildingBlocks>
template<typename T>
grouped_symbolic_literal<Type,BuildingBlocks...>& grouped_symbolic_literal<Type,BuildingBlocks...>::emplace(const T& i_value)
{
	if constexpr (std::is_same<T,grouped_symbolic_literal<Type,BuildingBlocks...>>::value)
	{
		i_value.enumerate([this](const auto& ii_value)
		{
			emplace(ii_value);
		});
	}
	else
	{
		if constexpr (is_symbolic_literal_operand<T>)
		{
			m_operands[T::get_type()].template get<detail::symbolic_literal_operand<T>>().emplace(i_value);
		}
		else
		{
			m_operands.insert(std::make_pair(T::get_type(),i_value));
		}
	}

	return *this;
}
template<size_t Type, typename ... BuildingBlocks>
TEMPLATE(typename T,typename Callable)
REQUIRED(IS_CALLABLE(Callable))
void grouped_symbolic_literal<Type,BuildingBlocks...>::enumerate(const Callable& i_callable) const
{
	if constexpr(is_symbolic_literal_operand<T>)
	{
		typename std::map<SymbolicLiteralType,symbolic_literal_t>::const_iterator itOperand = m_operands.find(T::get_type());
		if(itOperand != m_operands.end())
		{
			nested_enumerate(itOperand->second.template get<detail::symbolic_literal_operand<T>>(),i_callable);
		}
	}
	else
	{
		typename std::map<SymbolicLiteralType,symbolic_literal_t>::const_iterator itOperand = m_operands.find(T::get_type());
		if(itOperand != m_operands.end())
		{
			i_callable(itOperand->second.template get<T>());
		}
	}

	return false;
}
template<size_t Type, typename ... BuildingBlocks>
TEMPLATE(typename Callable)
REQUIRED(IS_CALLABLE(Callable))
void grouped_symbolic_literal<Type,BuildingBlocks...>::enumerate(const Callable& i_callable) const
{
	for(const auto& operand : m_operands)
	{
		const operand_visitor visitor(i_callable);

		ddk::visit(visitor,operand.second);
	}
}
template<size_t Type, typename ... BuildingBlocks>
size_t grouped_symbolic_literal<Type,BuildingBlocks...>::size() const
{
	return m_operands.size();
}
template<size_t Type, typename ... BuildingBlocks>
bool grouped_symbolic_literal<Type,BuildingBlocks...>::empty() const
{
	return m_operands.empty();
}

}