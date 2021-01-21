#pragma once

#include <utility>
#include "cpn_set.h"
#include "cpn_symbolic_number.h"

namespace cpn
{

struct rational_set
{
public:
	rational_set() = default;
	constexpr rational_set(int i_num, unsigned int i_den)
    : m_value(i_num,i_den)
	{
	}

	int numerator() const;
	unsigned int denominator() const;
	double resolve(unsigned char i_accuracy) const;
    bool operator==(const rational_set& other) const;

private:
	std::pair<int,unsigned int> m_value = {0,1};
};

struct irrational_set
{
public:
	irrational_set(const symbolic_number& i_number = integer(0));
    irrational_set(inherited_symbolic_number&& i_number);

	symbolic_number get_number() const;
    bool operator==(const irrational_set& other) const;

private:
	symbolic_number m_number;
};

using real_set = sum_set<rational_set,irrational_set>;

}
