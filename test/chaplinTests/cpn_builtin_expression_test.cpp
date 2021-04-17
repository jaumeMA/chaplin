#include <gtest/gtest.h>
#include "cpn_builtin_functions.h"
#include "cpn_number.h"
#include <utility>

using namespace testing;

class CPNBuiltinExpressionTest: public Test
{
};

TEST(CPNBuiltinExpressionTest,defaultBuiltinExpression)
{
	constexpr  auto exp0 = -cpn::sin(cpn::x + 3);
	constexpr  auto exp1 = cpn::sin(cpn::x + 3) + exp0;
	//exp1.kk();
	constexpr  auto exp2 = -(cpn::x_0 + cpn::x_1 + cpn::x_2) + exp1;
	const auto res = cpn::instance_as_function<cpn::real,ddk::mpl::type_pack<cpn::real,cpn::real,cpn::real>>(exp2);

	res == res;

	res + res;
}
