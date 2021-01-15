#pragma once

#define DECLARE_OPERATION_PROPERTIES(Operation,...) \
    typedef cpn::operation_props<Operation,__VA_ARGS__> __props;

namespace cpn
{

template<typename Operation, typename ... T>
struct operation_props
{
    template<typename TT>
    friend inline ddk::mpl::is_among_types<TT,T...>::value resolve_operation_property(const Operation&);
};

struct associative;
struct distributive;
struct commutative;

template<typename T>
std::false_type resolve_operation_property(T&&, ...);

}
