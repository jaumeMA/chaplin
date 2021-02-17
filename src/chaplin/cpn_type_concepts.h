#pragma once


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

#define EXPAND_TYPE_PACK_ARGS_CONCEPTS(_NUM_ARGS) \
template<typename T> concept type_pack_args_more_or_equal_to_##_NUM_ARGS = ddk::mpl::is_type_pack<T>::value && ddk::mpl::is_type_pack<T>::num_types >= _NUM_ARGS; \
template<typename T> concept type_pack_args_equal_to_##_NUM_ARGS = ddk::mpl::is_type_pack<T>::value && ddk::mpl::is_type_pack<T>::num_types == _NUM_ARGS;

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