#pragma once

namespace cpn
{

template<typename Set,typename ... Operators>
class algebraic_structure: public Set, public Operators ...
{
public:
	using Set::Set;

	algebraic_structure(const Set& i_value);

private:

};

}

#include "cpn_algebraic_structure.inl"