#pragma once

#include "cpn_builtin_symbolic_literals.h"
#include "ddk_type_concepts.h"
#include "ddk_concepts.h"

namespace cpn
{

//comparison operators
constexpr bool operator==(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr bool operator==(const rational_symbolic_literal& i_lhs, const rational_symbolic_literal& i_rhs);
constexpr bool operator==(const root_symbolic_literal& i_lhs, const root_symbolic_literal& i_rhs);
constexpr bool operator==(const log_symbolic_literal& i_lhs, const log_symbolic_literal& i_rhs);
bool operator==(const sum_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs);
bool operator==(const prod_symbolic_literal& i_lhs, const prod_symbolic_literal& i_rhs);

constexpr bool operator<(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr bool operator<(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
bool operator<(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
bool operator<(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
bool operator<(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
bool operator<(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);

// - operator

constexpr integer_symbolic_literal operator-(const integer_symbolic_literal& i_value);
constexpr rational_symbolic_literal operator-(const rational_symbolic_literal& i_value);
constexpr root_symbolic_literal operator-(const root_symbolic_literal& i_value);
constexpr log_symbolic_literal operator-(const log_symbolic_literal& i_value);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_value);
prod_symbolic_literal operator-(const prod_symbolic_literal& i_value);

// + operator

constexpr integer_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const rational_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator+(const rational_symbolic_literal& i_lhs, const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs, const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);

//  operator -

constexpr integer_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);

// operator*

constexpr integer_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
sum_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);

// opèrator/
constexpr rational_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
constexpr rational_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
prod_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
sum_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
prod_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs);
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs);

}

#include "cpn_builtin_symbolic_literal_ops.inl"