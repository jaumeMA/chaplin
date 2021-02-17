
namespace cpn
{
namespace detail
{

template<ring_type T, size_t Rank>
T identity_prod_matrix<T,Rank>::operator()(size_t i_row, size_t i_col) const
{
    return (i_row == i_col) ? T::mult_operation::identity : T::mult_operation::annihilator;
}

}

template<free_module_type T, typename InnerProdMatrix>
vector_mult_operation<T,InnerProdMatrix>::operator T() const
{
    typedef typename T::template equip_with<vector_mult_operation> vector_space_t;

    return T(static_cast<const vector_space_t&>(*this));
}

}
