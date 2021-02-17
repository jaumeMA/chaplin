#pragma once

#include "cpn_algebraic_defs.h"
#include "cpn_type_concepts.h"

#define IS_ALGEBRAIC_STRUCTURE(_TYPE) \
    typename _TYPE::operators_pack
#define CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,_STRUCTURE) \
    typename _TYPE::_STRUCTURE
#define IS_SET(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE)
#define IS_SEMI_GROUP(_TYPE) \
    IS_SET(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,add_operation)
#define IS_GROUP(_TYPE) \
    IS_SEMI_GROUP(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,add_inverse_operation)
#define IS_SEMI_RING(_TYPE) \
    IS_SEMI_GROUP(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,mult_operation)
#define IS_RING(_TYPE) \
    IS_GROUP(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,mult_operation)
#define IS_MODULE(_TYPE) \
    IS_GROUP(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,mod_operation)
#define IS_FREE_MODULE(_TYPE) \
    IS_MODULE(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,basis_operation)
#define IS_VECTOR_SPACE(_TYPE) \
    IS_FREE_MODULE(_TYPE),CONTAINS_ALGEBRAIC_STRUCTURE(_TYPE,vector_prod_operation)

#define IS_SUPERSTRUCTURE_OF(_SUPER_TYPE_OPERATORS,_SUB_TYPE_OPERATORS) \
    typename std::enable_if<_SUPER_TYPE_OPERATORS::template contains(_SUB_TYPE_OPERATORS{})>::type

#define IS_NOT_SUPERSTRUCTURE_OF(_SUPER_TYPE_OPERATORS,_SUB_TYPE_OPERATORS) \
    typename std::enable_if<_SUPER_TYPE_OPERATORS::template contains(_SUB_TYPE_OPERATORS{}) == false>::type

#define IS_SUBSTRUCTURE_OF(_SUPER_TYPE_OPERATORS,_SUB_TYPE_OPERATORS) \
    typename std::enable_if<_SUB_TYPE_OPERATORS::template contains(_SUPER_TYPE_OPERATORS{})>::type

#define IS_NOT_SUBSTRUCTURE_OF(_SUPER_TYPE_OPERATORS,_SUB_TYPE_OPERATORS) \
    typename std::enable_if<_SUB_TYPE_OPERATORS::template contains(_SUPER_TYPE_OPERATORS{}) == false>::type

#define HOLDS_TYPE_OPERATION_PROPERTY(_TYPE,_OPERATION,_PROPERTY) \
    decltype(resolve_operation_property<_PROPERTY>(std::declval<typename _TYPE::_OPERATION>()))::value

namespace cpn
{
namespace concepts
{

template<typename,template<typename,typename...>typename>
struct contains_algebraic_structure_resolver;

template<typename,template<typename,typename...>typename>
struct contains_algebraic_structure_resolver
{
    static const bool value = false;
};

template<typename Set, typename ... Operations,template<typename,typename...>typename Structure>
struct contains_algebraic_structure_resolver<Structure<Set,Operations...>,Structure>
{
    static const bool value = true;
};

template<typename Type,template<typename,typename...>typename Structure>
inline constexpr bool contains_algebraic_structure = contains_algebraic_structure_resolver<Type,Structure>::value;

}

template<typename T>
concept set_type = requires (const T& i_lhs, const T& i_rhs){ { i_lhs == i_rhs}; };
template<typename T>
concept semi_group_type = set_type<T> && additive_type<T> && requires { { T::add_operation }; };
template<typename T>
concept group_type = semi_group_type<T> && substractive_type<T> && requires { { T::add_inverse_operation }; };
template<typename T>
concept semi_ring_type = semi_group_type<T> && multiplicative_type<T> && requires { { T::mult_operation }; };
template<typename T>
concept ring_type = group_type<T> && multiplicative_type<T> && requires { { T::mult_operation }; };
template<typename T>
concept field_type = ring_type<T> && divisible_type<T> && requires { { T::div_operation }; };
template<typename T>
concept module_type = group_type<T> && requires { { T::mod_operation }; };
template<typename T>
concept free_module_type = module_type<T> && requires { { T::basis_operation }; };
template<typename T>
concept vector_space_type = free_module_type<T> && requires { { T::vector_prod_operation }; };

}
