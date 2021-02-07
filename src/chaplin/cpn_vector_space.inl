
namespace cpn
{
namespace detail
{

template<typename Ring, size_t Rank>
Ring identity_prod_matrix<Ring,Rank>::operator()(size_t i_row, size_t i_col) const
{
    return (i_row == i_col) ? Ring::mult_operation::identity : Ring::mult_operation::annihilator;
}

}

template<typename Free_Module, typename InnerProdMatrix>
vector_mult_operation<Free_Module,InnerProdMatrix>::operator Free_Module() const
{
    typedef typename Free_Module::template equip_with<vector_mult_operation> vector_space_t;

    return Free_Module(static_cast<const vector_space_t&>(*this));
}

}
