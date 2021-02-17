#pragma once

#include "cpn_free_module.h"

namespace cpn
{
namespace detail
{

template<ring_type T, size_t Rank>
struct identity_prod_matrix
{
    inline T operator()(size_t i_row, size_t i_col) const;
};

}

template<free_module_type T, typename InnerProdMatrix>
struct vector_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(vector_mult_operation,vector_prod_operation,linear,conjugate,positive_definite);

    typedef typename T::ring_t ring_t;
    typedef InnerProdMatrix inner_prod_matrix_t;

    friend inline ring_t operator*(const T& i_lhs, const T& i_rhs)
    {
        static const inner_prod_matrix_t s_prodMatrix;

        ring_t res;

        for(size_t rowIndex = 0;rowIndex < T::rank;rowIndex++)
        {
            ring_t partialProd = ring_t::mult_operation::identity;

            for(size_t colIndex=0;colIndex<T::rank;colIndex++)
            {
                partialProd = partialProd + static_cast<const ring_t&>(i_lhs[colIndex]) * s_prodMatrix(colIndex,rowIndex);
            }

            partialProd = partialProd * static_cast<const ring_t&>(i_rhs[rowIndex]);

            res = res + partialProd;
        }

        return res;
    }
    inline operator T() const;
};

template<free_module_type T, typename InnerProdMatrix = detail::identity_prod_matrix<typename T::ring_t,T::rank>>
using vector_space = typename T::template equip_with<vector_mult_operation<T,InnerProdMatrix>>;

template<typename VectorSpace>
using vector_sub_space = typename forget_vector_prod<free_sub_module<VectorSpace>>::template equip_withequip_with<vector_mult_operation<forget_vector_prod<free_sub_module<VectorSpace>>,typename VectorSpace::inner_prod_matrix_t>>;

}

#include "cpn_vector_space.inl"
