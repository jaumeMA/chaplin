
namespace cpn
{

irrational_set mixed_module_operation(const rational_set& i_lhs,const irrational_set& i_rhs)
{
    prod_symbolic_number_visitor prodVisitor;

    return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(integer(i_lhs.numerator()),integer(i_lhs.denominator()))),share(i_rhs.get_number()));
}
irrational_set mixed_module_operation(const irrational_set& i_lhs, const rational_set& i_rhs)
{
    prod_symbolic_number_visitor prodVisitor;

    return ddk::visit(ddk::specialize(prodVisitor,rational_symbolic_number(integer(i_rhs.numerator()),integer(i_rhs.denominator()))),share(i_lhs.get_number()));
}

}
