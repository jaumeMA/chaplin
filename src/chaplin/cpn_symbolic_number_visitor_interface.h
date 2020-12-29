#pragma once

#include "ddkFramework/ddk_dynamic_visitor.h"

namespace cpn
{

template<typename>
class sum_symbolic_numbers;
template<typename>
class prod_symbolic_numbers;
template<typename>
class rational_symbolic_number;
template<typename>
class root_symbolic_number;
template<typename>
class log_symbolic_number;

template<typename T>
class symbolic_number_visitor_interface : public ddk::dynamic_visitor
{
public:
	virtual ddk::any_value visit(const sum_symbolic_numbers<T>&) const = 0;
	virtual ddk::any_value visit(const prod_symbolic_numbers<T>&) const = 0;
	virtual ddk::any_value visit(const rational_symbolic_number<T>&) const = 0;
	virtual ddk::any_value visit(const root_symbolic_number<T>&) const = 0;
	virtual ddk::any_value visit(const log_symbolic_number<T>&) const = 0;
};

}