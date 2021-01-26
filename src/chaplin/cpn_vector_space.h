#pragma once

#include "cpn_free_module.h"

namespace cpn
{
namespace detail
{

template<typename Ring, size_t Rank>
struct identity_prod_matrix
{
    inline Ring operator()(size_t i_row, size_t i_col) const;
};

}

template<typename FreeModule, typename InnerProdMatrix>
struct vector_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(vector_mult_operation,vector_prod_operation,linear,conjugate,positive_definite);

    typedef typename FreeModule::ring_type ring_type;

    friend inline ring_type operator*(const FreeModule& i_lhs, const FreeModule& i_rhs)
    {
        static const InnerProdMatrix s_prodMatrix;

        ring_type res;

        for(size_t rowIndex = 0;rowIndex < FreeModule::rank();rowIndex++)
        {
            ring_type partialProd = ring_type::mult_operation::identity;

            for(size_t colIndex=0;colIndex<FreeModule::rank();colIndex++)
            {
                partialProd = partialProd + static_cast<const ring_type&>(i_lhs[colIndex]) * s_prodMatrix(colIndex,rowIndex);
            }

            partialProd = partialProd * static_cast<const ring_type&>(i_rhs[rowIndex]);

            res = res + partialProd;
        }

        return res;
    }
    inline operator FreeModule() const;
};

template<typename FreeModule, typename InnerProdMatrix = detail::identity_prod_matrix<typename FreeModule::ring_type,FreeModule::rank()>>
using vector_space = typename FreeModule::template equip_with<vector_mult_operation<FreeModule,InnerProdMatrix>>;

}

#include "cpn_vector_space.inl"
