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

template<typename Set, typename SumOperator, typename ProdOperator>
using ring = algebraic_structure<Set,SumOperator,ProdOperator>;

template<typename Set, typename SumOperator, typename ProdOperator, typename InverseOperator>
using field = algebraic_structure<Set,SumOperator,ProdOperator,InverseOperator>;

template<typename Set, typename SumOperator, typename ProdOperator, typename InverseOperator, typename ModuleOperator>
using module = algebraic_structure<Set,SumOperator,ProdOperator,InverseOperator,ModuleOperator>;

}