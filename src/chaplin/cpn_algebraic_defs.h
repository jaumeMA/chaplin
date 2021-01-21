#pragma once

#define PUBLISH_OPERATION_PROPERTIES(Operation,...) \
    template<typename TT> \
    friend inline typename ddk::mpl::static_if<ddk::mpl::is_among_type_pack<TT,__VA_ARGS__>,std::true_type,std::false_type>::type resolve_operation_property(const Operation&);

namespace cpn
{

struct associative;
struct distributive;
struct commutative;

template<typename T>
std::false_type resolve_operation_property(T&&, ...);

}
