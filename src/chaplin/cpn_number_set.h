#pragma once

#include "cpn_algebraic_structure.h"
#include "cpn_set.h"
#include "cpn_symbolic_number.h"
#include <utility>

namespace cpn
{

struct integer_set
{
public:
	constexpr integer_set() = default;
	constexpr integer_set(int i_num);
	constexpr integer_set(const integer_set&) = default;

	constexpr int number() const;
	int resolve(unsigned char i_accuracy) const;
    bool operator==(const integer_set& other) const;

private:
	int m_value = 0;
};

struct rational_set
{
public:
	rational_set() = default;
	constexpr rational_set(const integer_set& i_value);
	constexpr rational_set(int i_num, unsigned int i_den = 1);
	constexpr rational_set(double i_value);
	constexpr rational_set(const rational_set&) = default;

	int numerator() const;
	unsigned int denominator() const;
	double resolve(unsigned char i_accuracy) const;
    bool operator==(const rational_set& other) const;

private:
	std::pair<int,unsigned int> m_value = {0,1};
};

struct real_set
{
public:
    real_set(const rational_set& i_value = rational_set());
	real_set(const symbolic_number& i_number);
    TEMPLATE(typename T)
    REQUIRES(IS_BASE_OF(symbolic_number_interface,T))
    real_set(const ddk::inherited_value<const T>& i_number);
    real_set(const real_set&) = default;

	symbolic_number number() const;
	double resolve(unsigned char i_accuracy = 8) const;
	bool operator==(const real_set& other) const;

private:
	symbolic_number m_number;
};

}

#include "cpn_number_set.inl"
