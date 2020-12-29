

namespace cpn
{

template<typename Type1,typename Type2>
typename add_symbolic_number_visitor::return_type add_symbolic_number_visitor::visit(const Type1& i_lhs,const Type2& i_rhs)
{
	return ddk::make_inherited_value<sum_symbolic_number>(share(i_lhs),share(i_rhs));
}

}