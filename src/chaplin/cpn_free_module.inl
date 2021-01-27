
namespace cpn
{

template<typename Module>
typename canonical_basis_operation<Module>::set_traits canonical_basis_operation<Module>::basis(size_t i_index)
{
    set_traits res;

    res[i_index] = ring_type::mult_operation::identity;

    return res;
}

template<typename BasisOperation, size_t ... SpecializedComponents>
typename sub_basis_operation<BasisOperation,SpecializedComponents...>::set_traits sub_basis_operation<BasisOperation,SpecializedComponents...>::basis(size_t i_index)
{
    set_traits res;

    res[i_index] = ring_type::mult_operation::identity;

    return res;
}

}
