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

template<typename,size_t>
struct CartesianCoordinates;
template<typename,size_t>
struct SphericalCoordinates;
template<typename,size_t>
struct CylindricalCoordinates;

template<typename T, size_t Dims>
struct CartesianCoordinates
{
    template<typename Coordinates>
    ddk::high_order_array<T,Dims> transform(const ddk::high_order_array<T,Dims>&);

    template<>
    inline ddk::high_order_array<T,Dims> transform<SphericalCoordinates<T,Dims>>(const ddk::high_order_array<T,Dims>& i_vector);
    template<>
    inline ddk::high_order_array<T,Dims> transform<CylindricalCoordinates<T,Dims>>(const ddk::high_order_array<T,Dims>& i_vector);
};

template<typename T,size_t Dims>
struct SphericalCoordinates
{
    template<typename Coordinates>
    ddk::high_order_array<T,Dims> transform(const T&);

    template<>
    inline ddk::high_order_array<T,Dims> transform<CartesianCoordinates<T,Dims>>(const ddk::high_order_array<T,Dims>& i_vector);
    template<>
    inline ddk::high_order_array<T,Dims> transform<CylindricalCoordinates<T,Dims>>(const ddk::high_order_array<T,Dims>& i_vector);
};

template<typename T,size_t Dims>
struct CylindricalCoordinates
{
    template<typename Coordinates>
    ddk::high_order_array<T,Dims> transform(const ddk::high_order_array<T,Dims>&);

    template<>
    inline ddk::high_order_array<T,Dims> transform<CartesianCoordinates<T,Dims>>(const ddk::high_order_array<T,Dims>& i_vector);
    template<>
    inline ddk::high_order_array<T,Dims> transform<SphericalCoordinates<T,Dims>>(const ddk::high_order_array<T,Dims>& i_vector);
};

}

template<free_module_type T, typename Coordinates = detail::CartesianCoordinates<typename T::ring_t,T::rank>>
struct coordinate_transform
{
    PUBLISH_OPERATION_PROPERTIES(coordinate_transform,coordinate_transform_operation);

    //ToDo: Define coordinate transformations
    template<typename CCoordinates>
    T transform(const T& i_vector)
    {
    }
};

template<free_module_type T, typename InnerProdMatrix>
struct vector_mult_operation
{
    PUBLISH_OPERATION_PROPERTIES(vector_mult_operation,mult_operation,linear,conjugate,positive_definite);

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

template<vector_space_type T>
struct metric_from_vector_multiplication
{
    inline double operator()(const T& i_lhs,const T& i_rhs) const
    {
        return std::sqrt((i_lhs - i_rhs) * (i_lhs - i_rhs));
    }
};

template<free_module_type T, typename Coordinates = detail::CartesianCoordinates<typename T::ring_t, T::rank>, typename InnerProdMatrix = detail::identity_prod_matrix<typename T::ring_t,T::rank>>
using vector_space = typename T::template equip_with<coordinate_transform<T,Coordinates>,vector_mult_operation<T,InnerProdMatrix>>;

template<typename VectorSpace>
using vector_sub_space = typename forget_vector_prod<free_sub_module<VectorSpace>>::template equip_withequip_with<vector_mult_operation<forget_vector_prod<free_sub_module<VectorSpace>>,typename VectorSpace::inner_prod_matrix_t>>;

}

#include "cpn_vector_space.inl"
