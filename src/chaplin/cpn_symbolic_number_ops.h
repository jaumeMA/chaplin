#pragma once

namespace cpn
{

bool operator<(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
bool operator==(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
symbolic_number operator-(const symbolic_number& i_number);
symbolic_number operator+(const symbolic_number& i_lhs, const symbolic_number& i_rhs);
symbolic_number operator-(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
symbolic_number operator*(const symbolic_number& i_lhs,const symbolic_number& i_rhs);
symbolic_number operator/(const symbolic_number& i_lhs,const symbolic_number& i_rhs);

}