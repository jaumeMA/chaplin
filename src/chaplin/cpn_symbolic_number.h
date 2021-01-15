#pragma once

#include "cpn_symbolic_number_interface.h"
#include "ddkFramework/ddk_function.h"

namespace cpn
{

class symbolic_number
{
    friend inline inherited_symbolic_number share(const symbolic_number& thisNumber)
    {
        return thisNumber.m_impl;
    }

public:
	symbolic_number(const inherited_symbolic_number& i_number);
    TEMPLATE(typename T)
    REQUIRES(IS_BASE_OF(symbolic_number_interface,T))
    symbolic_number(ddk::inherited_value<T>&& i_impl);
    symbolic_number(const symbolic_number&) = default;
    symbolic_number(symbolic_number&&) = default;

    symbolic_number& operator=(const inherited_symbolic_number&);
    TEMPLATE(typename T)
    REQUIRES(IS_BASE_OF(symbolic_number_interface,T))
    symbolic_number& operator=(ddk::inherited_value<T>&& i_impl);
    symbolic_number& operator=(const symbolic_number&) = default;
    symbolic_number& operator=(symbolic_number&&) = default;
	double resolve(unsigned char i_accuracy) const;

private:
	inherited_symbolic_number m_impl;
};

}

#include "cpn_symbolic_number.inl"
#include "cpn_builtin_symbolic_number_factory.h"
