#pragma once

#include "ddk_type_concepts.h"
#include "ddk_concepts.h"
#include "ddk_variant.h"
#include "ddk_variant_concepts.h"
#include "ddk_scoped_enum.h"
#include "ddk_hash.h"
#include <vector>

namespace cpn
{

SCOPED_ENUM_DECL(SymbolicLiteralType,
		Integer,
		Rational,
		Root,
		Log,
		Sum,
		Prod
);

namespace detail
{

template<size_t Type>
struct symbolic_literal
{
public:
	static inline SymbolicLiteralType get_type();
};

template<typename T>
struct symbolic_literal_operand
{
	template<typename Callable>
	friend inline void nested_enumerate(const symbolic_literal_operand& i_value,const Callable& i_callable)
	{
		typename std::vector<T>::const_iterator it = i_value.m_operand.begin();
		for(; it != i_value.m_operand.end(); ++it)
		{
			i_callable(*it);
		}
	}
	friend inline size_t hash(const symbolic_literal_operand& i_number)
	{
		ddk::commutative_builtin_hasher _hasher;
		size_t combinedHash = 0;

		for(const auto& item : i_number.m_operand)
		{
			combinedHash = _hasher(hash(item));
		}

		return combinedHash;
	}

public:
	typedef typename std::vector<T>::iterator iterator;
	typedef typename std::vector<T>::const_iterator const_iterator;

	symbolic_literal_operand() = default;
	symbolic_literal_operand(const symbolic_literal_operand&) = default;
	symbolic_literal_operand(symbolic_literal_operand&&) = default;
	TEMPLATE(typename ... Args)
	REQUIRES(IS_CONSTRUCTIBLE(T,Args...))
	symbolic_literal_operand(Args&& ... i_args);

	template<typename ... Args>
	bool emplace(Args&& ... i_args);
	iterator begin();
	const_iterator begin() const;
	template<typename ... Args>
	iterator insert(iterator itPos,Args&& ... i_args);
	iterator end();
	const_iterator end() const;

private:
	std::vector<T> m_operand;
};

}

struct integer_symbolic_literal : public detail::symbolic_literal<SymbolicLiteralType::Integer>
{
	friend constexpr size_t hash(const integer_symbolic_literal& i_number)
	{
		return ddk::hash_combine(SymbolicLiteralType::Integer,i_number.m_number);
	}

public:
	constexpr integer_symbolic_literal(int i_number);
	constexpr integer_symbolic_literal(const integer_symbolic_literal& other);

	constexpr int number() const;

private:
	const int m_number = 0;
};

struct rational_symbolic_literal : public detail::symbolic_literal<SymbolicLiteralType::Rational>
{
	friend constexpr size_t hash(const rational_symbolic_literal& i_number)
	{
		return ddk::hash_combine(SymbolicLiteralType::Rational,i_number.m_numerator,i_number.m_denominator);
	}

public:
	constexpr rational_symbolic_literal(int i_numerator, int i_denominator);

	constexpr int numerator() const;
	constexpr int denominator() const;

private:
	const int m_numerator = 0;
	const int m_denominator = 1;
};

struct root_symbolic_literal : public detail::symbolic_literal<SymbolicLiteralType::Root>
{
	friend constexpr size_t hash(const root_symbolic_literal& i_number)
	{
		return ddk::hash_combine(SymbolicLiteralType::Root,i_number.m_number,i_number.m_degree);
	}

public:
	constexpr root_symbolic_literal(int i_number, int i_degree, bool i_positive = true);

	constexpr int number() const;
	constexpr int degree() const;
	constexpr bool positive() const;

private:
	const int m_number = 0;
	const int m_degree = 0;
	const bool m_sign = true;
};

struct log_symbolic_literal : public detail::symbolic_literal<SymbolicLiteralType::Log>
{
	friend constexpr size_t hash(const log_symbolic_literal& i_number)
	{
		return ddk::hash_combine(SymbolicLiteralType::Log,i_number.m_number,i_number.m_base);
	}

public:
	constexpr log_symbolic_literal(int i_number, int i_logBase, bool i_positive = true);

	constexpr int number() const;
	constexpr int base() const;
	constexpr bool positive() const;

private:
	const int m_number = 0;
	const int m_base = 0;
	const bool m_sign = true;
};

template<size_t Type, typename ... BuildingBlocks>
struct grouped_symbolic_literal : public detail::symbolic_literal<Type>
{
	template<typename Hasher>
	struct operand_visitor: public ddk::static_visitor<bool>
	{
		operand_visitor(const Hasher& i_callable);
		template<typename T,typename = decltype(nested_enumerate(std::declval<T>(),std::declval<Hasher>()))>
		return_type operator()(T&& i_value) const;
		return_type operator()(...) const;

	private:
		const Hasher& m_hasher;
	};
	friend inline size_t hash(const grouped_symbolic_literal& i_number)
	{
		ddk::commutative_builtin_hasher _hasher(Type);

		const auto hasher = [&_hasher](const auto& i_value)
		{
			_hasher(i_value);
		};

		for(const auto& operand : i_number.m_operands)
		{
			static const operand_visitor<ddk::commutative_builtin_hasher> hasherVisitor(_hasher);

			ddk::visit(hasherVisitor,operand.second);
		}

		return _hasher.get();
	}

	typedef ddk::variant<BuildingBlocks...> symbolic_literal_t;
	template<typename T>
	static constexpr bool is_symbolic_literal_operand = ddk::concepts::is_among_variant_types<detail::symbolic_literal_operand<T>,symbolic_literal_t>;
public:
	TEMPLATE(typename ... T)
	REQUIRES(IS_CONSTRUCTIBLE(symbolic_literal_t,T)...)
	explicit grouped_symbolic_literal(const T& ... i_operands);
	grouped_symbolic_literal(const grouped_symbolic_literal&) = default;
	grouped_symbolic_literal(grouped_symbolic_literal&&) = default;

	template<typename T>
	grouped_symbolic_literal& emplace(const T& i_value);
	size_t size() const;
	bool empty() const;
	TEMPLATE(typename T,typename Callable)
	REQUIRES(IS_CLASS(Callable))
	void enumerate(const Callable & i_callable) const;
	TEMPLATE(typename Callable)
	REQUIRES(IS_CLASS(Callable))
	void enumerate(const Callable & i_callable) const;

private:
	std::map<SymbolicLiteralType,symbolic_literal_t> m_operands;
};

typedef grouped_symbolic_literal<SymbolicLiteralType::Sum,integer_symbolic_literal,rational_symbolic_literal,detail::symbolic_literal_operand<root_symbolic_literal>,detail::symbolic_literal_operand<log_symbolic_literal>> prod_symbolic_literal;
typedef grouped_symbolic_literal<SymbolicLiteralType::Prod,integer_symbolic_literal,rational_symbolic_literal,detail::symbolic_literal_operand<root_symbolic_literal>,detail::symbolic_literal_operand<log_symbolic_literal>,detail::symbolic_literal_operand<prod_symbolic_literal>> sum_symbolic_literal;
typedef grouped_symbolic_literal<SymbolicLiteralType::Prod,integer_symbolic_literal,rational_symbolic_literal,detail::symbolic_literal_operand<root_symbolic_literal>,detail::symbolic_literal_operand<log_symbolic_literal>,detail::symbolic_literal_operand<prod_symbolic_literal>,detail::symbolic_literal_operand<sum_symbolic_literal>> div_symbolic_literal;

}

#include "cpn_builtin_symbolic_literals.inl"
#include "cpn_builtin_symbolic_literal_factory.h"
#include "cpn_builtin_symbolic_literal_ops.h"
