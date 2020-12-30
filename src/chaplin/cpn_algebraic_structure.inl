
namespace cpn
{

template<typename Set,typename ... Operators>
algebraic_structure<Set,Operators...>::algebraic_structure(const Set& i_value)
: Set(i_value)
{
}

}