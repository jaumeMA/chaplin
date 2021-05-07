#pragma once

#include "ddk_high_order_array.h"
#include "ddk_container_concepts.h"

#define FULFILLS_CONCEPT_COMPONENT_WISE(_CONCEPT) \
template<typename T> \
struct fulfills_concept_##_CONCEPT##_component_wise \
{ \
private: \
    template<typename TT, typename TTT = typename TT::place_type> \
    static typename ddk::mpl::static_if<_CONCEPT<TTT>,std::true_type,std::false_type>::type resolve(TT&); \
    template<typename TT> \
    static typename ddk::mpl::static_if<_CONCEPT<TT>,std::true_type,std::false_type>::type resolve(const TT& ...); \
 \
public: \
    static const bool value = decltype(resolve(std::declval<T&>()))::value; \
};

#define EXPAND_TYPE_PACK_ARGS_CONCEPTS(_NUM_ARGS) \
template<typename T> \
concept type_pack_args_more_or_equal_to_##_NUM_ARGS = ddk::mpl::is_type_pack<T>::num_types >= _NUM_ARGS; \
template<typename T> \
concept type_pack_args_equal_to_##_NUM_ARGS = ddk::mpl::is_type_pack<T>::num_types == _NUM_ARGS;

namespace cpn
{

template<typename T>
concept equally_comparable_type = requires (T i_lhs, T i_rhs) { i_lhs == i_rhs; };

template<typename T>
concept inverse_additive_type = requires (T i_lhs) { -i_lhs; };

template<typename T>
concept additive_type = requires (T i_lhs, T i_rhs) { i_lhs + i_rhs; };

template<typename T>
concept closed_additive_type = requires (T i_lhs,T i_rhs, T& res) { res = i_lhs + i_rhs; };

template<typename T>
concept substractive_type = requires (T i_lhs,T i_rhs) { i_lhs - i_rhs; };

template<typename T>
concept closed_substractive_type = requires (T i_lhs,T i_rhs, T& res) { res = i_lhs - i_rhs; };

template<typename T>
concept multiplicative_type = requires (T i_lhs,T i_rhs) { i_lhs * i_rhs; };

template<typename T>
concept closed_multiplicative_type = requires (T i_lhs,T i_rhs, T& res) { res = i_lhs * i_rhs; };

template<typename T>
concept divisible_type = requires (T i_lhs,T i_rhs) { i_lhs / i_rhs; };

template<typename T>
concept closed_divisible_type = requires (T i_lhs,T i_rhs, T& res) { res = i_lhs / i_rhs; };

template<typename T>
concept fundamental_type = IS_INDEXED_COND(T) == false;

template<typename T>
concept coordinate_type = IS_INDEXED_COND(T);

namespace concepts
{

FULFILLS_CONCEPT_COMPONENT_WISE(additive_type)
FULFILLS_CONCEPT_COMPONENT_WISE(inverse_additive_type)
FULFILLS_CONCEPT_COMPONENT_WISE(substractive_type)
FULFILLS_CONCEPT_COMPONENT_WISE(multiplicative_type)
FULFILLS_CONCEPT_COMPONENT_WISE(divisible_type)

}

template<typename T>
concept additive_component_wise_type = concepts::fulfills_concept_additive_type_component_wise<typename T::set_traits>::value;
template<typename T>
concept inverse_additive_component_wise_type = additive_component_wise_type<T> && concepts::fulfills_concept_inverse_additive_type_component_wise<typename T::set_traits>::value;
template<typename T>
concept substractive_component_wise_type = additive_component_wise_type<T> && inverse_additive_component_wise_type<typename T::set_traits>;
template<typename T>
concept multiplicative_component_wise_type = inverse_additive_component_wise_type<T> && concepts::fulfills_concept_multiplicative_type_component_wise<typename T::set_traits>::value;
template<typename T>
concept divisible_component_wise_type = multiplicative_component_wise_type<T> && concepts::fulfills_concept_divisible_type_component_wise<typename T::set_traits>::value;

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
