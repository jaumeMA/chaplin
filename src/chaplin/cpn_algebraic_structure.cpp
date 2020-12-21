#include "cpn_algebraic_structure.h"
#include <string>
#include <array>

namespace cpn
{



template<size_t Dim>
struct rn_set
{
public:
	rn_set() = default;

	float& operator[](size_t i_index)
	{
		return m_value[i_index];
	}
	float operator[](size_t i_index) const
	{
		return m_value[i_index];
	}

private:
	std::array<float,Dim> m_value = { 0.f };
};

struct string_set
{
	string_set() = default;
	string_set(const std::string& i_value)
	: m_value(i_value)
	{
	}

	std::string m_value;
};

struct real_sum
{
	friend inline real_set operator+(const real_set& i_lhs, const real_set& i_rhs)
	{
		return i_lhs.m_value + i_rhs.m_value;
	}
};

struct real_prod
{
	friend inline real_set operator*(const real_set& i_lhs,const real_set& i_rhs)
	{
		return i_lhs.m_value * i_rhs.m_value;
	}
};


template<size_t Dim>
struct rn_sum
{
	friend inline rn_set<Dim> operator+(const rn_set<Dim>& i_lhs, const rn_set<Dim>& i_rhs)
	{
		rn_set<Dim> res;

		for(size_t index=0;index<Dim;index++)
		{
			res[index] = i_lhs[index] + i_rhs[index];			
		}

		return res;
	}
};

struct string_sum
{
	friend inline string_set operator+(const string_set& i_lhs, const string_set& i_rhs)
	{
		return i_lhs.m_value + i_rhs.m_value;
	}

};

void prova()
{
	typedef ring<real_set,real_sum,real_prod> real_ring;
	typedef group<rational_set,rational_sum> rational_group;
	typedef group<string_set,string_sum> string_group;
	typedef rn_set<3> r3_set;
	typedef group<r3_set,rn_sum<3>> r3_group;

	real_ring kk1, kk2;
	kk1 + kk2;
	kk1 * kk2;

	string_group kk3, kk4;
	kk3 + kk4;

	r3_group kk5, kk6;
	kk5 + kk6;

	rational_group kk7,kk8;
	float res = kk7 + kk8;
}

}