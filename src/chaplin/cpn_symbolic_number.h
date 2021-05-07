#pragma once

#include "cpn_builtin_symbolic_literals.h"
#include "ddk_variant.h"

namespace cpn
{
namespace detail
{

struct symbolic_number_hash_visitor : public ddk::static_visitor<size_t>
{
    symbolic_number_hash_visitor() = default;
    template<typename T>
    inline size_t operator()(const T& i_number) const;
};

}

class symbolic_number
{
    typedef ddk::variant<integer_symbolic_literal,rational_symbolic_literal,root_symbolic_literal,log_symbolic_literal,sum_symbolic_literal,prod_symbolic_literal,div_symbolic_literal> nested_number_t;

    friend inline size_t hash(const symbolic_number& i_number);
    friend bool operator<(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
    friend bool operator==(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
    friend symbolic_number operator-(const symbolic_number& i_number);
    friend symbolic_number operator+(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
    friend symbolic_number operator-(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
    friend symbolic_number operator*(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
    friend symbolic_number operator/(const symbolic_number& i_lhs,const symbolic_number& i_rhs);

public:
    symbolic_number() = default;
    TEMPLATE(typename Arg, typename ... Args)
    REQUIRES(IS_CONSTRUCTIBLE(nested_number_t,Arg,Args...))
    symbolic_number(Arg&& i_arg, Args&& ... i_args);
    symbolic_number(const symbolic_number&) = default;
    symbolic_number(symbolic_number&&) = default;

    TEMPLATE(typename T)
    REQUIRES(IS_ASSIGNABLE(nested_number_t,T))
    symbolic_number& operator=(T&& i_number);
    symbolic_number& operator=(const symbolic_number&) = default;
    symbolic_number& operator=(symbolic_number&&) = default;
	double resolve(unsigned char i_accuracy) const;

private:
    nested_number_t m_number;
};

}

#include "cpn_symbolic_number.inl"
