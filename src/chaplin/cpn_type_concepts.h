#pragma once

#include "ddk_high_order_array.h"

#define FULFILLS_CONCEPT_COMPONENT_WISE(_CONCEPT) \
template<typename> \
struct fulfills_concept_##_CONCEPT##_component_wise; \
template<typename T> \
struct fulfills_concept_##_CONCEPT##_component_wise \
{ \
    static const bool value = _CONCEPT<T>; \
}; \
template<typename T, size_t ... Dims> \
struct fulfills_concept_##_CONCEPT##_component_wise<ddk::high_order_array<T,Dims...>> \
{ \
    static const bool value = _CONCEPT<T>; \
};

#define EXPAND_TYPE_PACK_ARGS_CONCEPTS(_NUM_ARGS) \
template<typename T> concept type_pack_args_more_or_equal_to_##_NUM_ARGS = ddk::mpl::is_type_pack<T>::num_types >= _NUM_ARGS; \
template<typename T> concept type_pack_args_equal_to_##_NUM_ARGS = ddk::mpl::is_type_pack<T>::num_types == _NUM_ARGS;

namespace cpn
{

template<typename T>
concept inverse_additive_type = requires (T i_lhs) { -i_lhs; };

template<typename T>
concept additive_type = requires (T i_lhs, T i_rhs) { i_lhs + i_rhs; };

template<typename T>
concept substractive_type = inverse_additive_type<T> && additive_type<T>;

template<typename T>
concept multiplicative_type = requires (T i_lhs,T i_rhs) { i_lhs * i_rhs; };

template<typename T>
concept divisible_type = requires (T i_lhs,T i_rhs) { i_lhs / i_rhs; };

template<typename T>
concept coordinate_type = requires { { T::num_coordinates }; };

namespace concepts
{

FULFILLS_CONCEPT_COMPONENT_WISE(additive_type)
FULFILLS_CONCEPT_COMPONENT_WISE(inverse_additive_type)
FULFILLS_CONCEPT_COMPONENT_WISE(substractive_type)
FULFILLS_CONCEPT_COMPONENT_WISE(multiplicative_type)
FULFILLS_CONCEPT_COMPONENT_WISE(divisible_type)

}

template<typename T>
concept additive_component_wise_type = concepts::fulfills_concept_additive_type_component_wise<T>::value;
template<typename T>
concept inverse_additive_component_wise_type = concepts::fulfills_concept_inverse_additive_type_component_wise<T>::value;
template<typename T>
concept substractive_component_wise_type = concepts::fulfills_concept_substractive_type_component_wise<T>::value;
template<typename T>
concept multiplicative_component_wise_type = concepts::fulfills_concept_multiplicative_type_component_wise<T>::value;
template<typename T>
concept divisible_component_wise_type = concepts::fulfills_concept_divisible_type_component_wise<T>::value;

EXPAND_TYPE_PACK_ARGS_CONCEPTS(1)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(2)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(3)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(4)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(5)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(6)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(7)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(8)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(9)
EXPAND_TYPE_PACK_ARGS_CONCEPTS(10)

}
