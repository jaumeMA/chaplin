#pragma once

namespace cpn
{

class commutative
{};

template<typename Set,typename ... Operators>
class algebraic_structure: virtual public Set, public Operators ...
{
public:
    typedef Set set_traits;
	using Set::Set;

	algebraic_structure(const Set& i_value);

private:

};

}

#include "cpn_algebraic_structure.inl"
