#pragma once

#include "cpn_module.h"

namespace cpn
{

template<module_type T, size_t Rank>
struct canonical_basis_operation
{
    PUBLISH_OPERATION_PROPERTIES(canonical_basis_operation,basis_operation);

    typedef typename T::set_traits set_traits;
    typedef typename T::ring_t basis_ring;

    static inline constexpr size_t rank = Rank;
    static inline set_traits basis(size_t i_index);
};

template<typename BasisOperation, size_t ... SpecializedComponents>
struct sub_basis_operation
{
    PUBLISH_OPERATION_PROPERTIES(sub_basis_operation,basis_operation);

    typedef typename BasisOperation::basis_ring basis_ring;
    typedef pow_set<basis_ring,BasisOperation::rank() - ddk::mpl::num_ranks<SpecializedComponents...>> set_traits;

    static inline constexpr size_t rank = BasisOperation::rank - ddk::mpl::num_ranks<SpecializedComponents...>;
    static inline set_traits basis(size_t i_index);
};

template<module_type T, typename BasisOperation>
using free_module = typename algebraic_structure<pow_set<ring_as_module<module_ring<T>>,BasisOperation::rank>>::template equip_with<BasisOperation,pow_add_operation<forget_add_inverse<forget_mult<ring_as_module<module_ring<T>>>>,BasisOperation::rank>,pow_add_inverse_operation<forget_mult<ring_as_module<module_ring<T>>>,BasisOperation::rank>,pow_mod_operation<ring_as_module<module_ring<T>>,BasisOperation::rank>>;

template<free_module_type T, size_t ... SpecializedComponents>
using free_sub_module = typename forget_basis<T>::template equip_with<sub_basis_operation<typename T::basis_operation,SpecializedComponents...>>;

}

#include "cpn_free_module.inl"
