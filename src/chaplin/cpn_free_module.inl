
namespace cpn
{

template<typename Module>
typename canonical_basis_operation<Module>::set_traits canonical_basis_operation<Module>::basis(size_t i_index)
{
    set_traits res;

    res[i_index] = Module::identity;

    return res;
}

}
