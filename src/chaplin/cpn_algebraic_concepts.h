#pragma once

#include "cpn_algebraic_defs.h"

#define IS_ALGEBRAIC_STRUCTURE(_TYPE,_STRUCTURE) \
    cpn::concepts::is_algebraic_structure<_TYPE,_STRUCTURE>
#define IS_SET(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE,set)
#define IS_SEMI_GROUP(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE,semi_group)
#define IS_GROUP(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE,group)
#define IS_SEMI_RING(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE,semi_ring)
#define IS_RING(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE,ring)
#define IS_MODULE(_TYPE) \
    IS_ALGEBRAIC_STRUCTURE(_TYPE,module)

#define IS_SUPERSTRUCTURE_OF(_SUPER_TYPE,_SUB_TYPE) \
    typename std::enable_if<_SUPER_TYPE::operators_pack::template contains(std::declval<typename _SUB_TYPE::operators_pack>())>::type

#define HOLDS_TYPE_OPERATION_PROPERTY(_TYPE,_OPERATION,_PROPERTY) \
    decltype(resolve_operation_property<_PROPERTY>(std::declval<typename _TYPE::_OPERATION>()))::value

namespace cpn
{
namespace concepts
{

template<typename,template<typename,typename...>typename>
struct is_algebraic_structure_resolver;

template<typename,template<typename,typename...>typename>
struct is_algebraic_structure_resolver
{
    static const bool value = false;
};

template<typename Set, typename ... Operations,template<typename,typename...>typename Structure>
struct is_algebraic_structure_resolver<Structure<Set,Operations...>,Structure>
{
    static const bool value = true;
};

template<typename Type,template<typename,typename...>typename Structure>
inline constexpr bool is_algebraic_structure = is_algebraic_structure_resolver<Type,Structure>::value;

}
}
