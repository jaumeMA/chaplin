#pragma once

namespace cpn
{

template<typename Set,typename ... Operators>
class algebraic_structure: public Set, public Operators ...
{
public:
	using Set::Set;

private:

};

}