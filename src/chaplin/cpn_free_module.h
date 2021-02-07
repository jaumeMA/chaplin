#pragma once

#include "cpn_module.h"

namespace cpn
{

template<typename Module, size_t Rank>
struct canonical_basis_operation
{
    PUBLISH_OPERATION_PROPERTIES(canonical_basis_operation,basis_operation);

    typedef typename Module::set_traits set_traits;
    typedef typename Module::ring_type ring_type;

    static inline constexpr size_t rank = Rank;
    static inline set_traits basis(size_t i_index);
};

template<typename BasisOperation, size_t ... SpecializedComponents>
struct sub_basis_operation
{
    PUBLISH_OPERATION_PROPERTIES(sub_basis_operation,basis_operation);

    typedef typename BasisOperation::ring_type ring_type;
    typedef ddk::high_order_array<ring_type,BasisOperation::rank() - ddk::mpl::num_ranks<SpecializedComponents...>> set_traits;

    static inline constexpr size_t rank = BasisOperation::rank - ddk::mpl::num_ranks<SpecializedComponents...>;
    static inline set_traits basis(size_t i_index);
};

template<typename Module, typename BasisOperation>
using free_module = typename algebraic_structure<ddk::high_order_array<module_ring<Module>,BasisOperation::rank>>::template equip_with<BasisOperation,pow_add_operation<forget_add_inverse<forget_mult<module_ring<Module>>>,BasisOperation::rank>,pow_add_inverse_operation<forget_add_inverse<forget_mult<module_ring<Module>>>,BasisOperation::rank>>;

template<typename FreeModule, size_t ... SpecializedComponents>
using free_sub_module = typename forget_basis<FreeModule>::template equip_with<sub_basis_operation<typename FreeModule::basis_operation,SpecializedComponents...>>;

}

#include "cpn_free_module.inl"
