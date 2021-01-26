
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

template<typename FreeModule, typename InnerProdMatrix>
vector_mult_operation<FreeModule,InnerProdMatrix>::operator FreeModule() const
{
    typedef typename FreeModule::template equip_with<vector_mult_operation> vector_space_t;

    return FreeModule(static_cast<const vector_space_t&>(*this));
}

}
