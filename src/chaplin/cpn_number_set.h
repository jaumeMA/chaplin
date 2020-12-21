#pragma once

#include <utility>
#include "cpn_set.h"

namespace cpn
{

struct rational_set
{
public:
	rational_set() = default;
	constexpr rational_set(int i_num,int i_den)
	: m_value(i_num,i_den)
	{
	}

	int numerator() const;
	int denomnator() const;
	operator float() const;

private:
	std::pair<int,int> m_value = {0,1};
};

struct irrational_set
{
	//TBD
};

using real_set = sum_set<rational_set,irrational_set>;

}