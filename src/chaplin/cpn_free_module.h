#pragma once

#include "cpn_module.h"

namespace cpn
{

template<typename Module>
struct canonical_basis_operation
{
    typedef typename Module::set_traits set_traits;
    typedef typename Module::ring_type ring_type;

    static constexpr size_t rank()
    {
        const size_t modRank = Module::mod_operation::rank();
        const ddk::high_order_array<size_t,modRank> modDim = Module::mod_operation::dimension();

        return modDim.at(0);
    }
    static inline set_traits basis(size_t i_dimension);
};

template<typename Module, typename BasisOperation = canonical_basis_operation<Module>>
using free_module = typename algebraic_structure<ddk::high_order_array<module_ring<Module>,BasisOperation::rank()>>::template equip_with<BasisOperation,pow_add_operation<module_ring<Module>,BasisOperation::rank()>,pow_add_inverse_operation<module_ring<Module>,BasisOperation::rank()>>;

}

#include "cpn_free_module.inl"
