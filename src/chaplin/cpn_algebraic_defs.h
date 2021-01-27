#pragma once

#define PUBLISH_OPERATION_PROPERTIES(_Operation,_Tag,...) \
    typedef _Operation _Tag; \
    template<typename TT> \
    friend inline typename ddk::mpl::static_if<ddk::mpl::is_among_type_pack<TT,##__VA_ARGS__>,std::true_type,std::false_type>::type resolve_operation_property(const _Operation&);

namespace cpn
{

struct associative;
struct distributive;
struct commutative;
struct linear;
struct conjugate;
struct positive_definite;

template<typename T>
std::false_type resolve_operation_property(T&&, ...);

}
