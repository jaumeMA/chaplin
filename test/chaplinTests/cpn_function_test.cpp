#include <gtest/gtest.h>
#include "cpn_number_vector_space.h"
#include "cpn_number.h"
#include "cpn_function_space.h"
#include <utility>

using namespace testing;

class CPNFunctionTest : public Test
{
};

TEST(CPNFunctionTest,defaultLinearFunction)
{
	constexpr  auto exp0 = -cpn::sin(cpn::x + 3);
	constexpr  auto exp1 = cpn::sin(cpn::x + 3) + exp0;
	//exp1.kk();
	constexpr  auto exp2 = -(cpn::x_0 + cpn::x_1 + cpn::x_2) + exp1;
	const cpn::F<cpn::R1,cpn::R3> expFunc1 = cpn::x_0 + cpn::x_1 + cpn::x_2;
	const cpn::LF<cpn::R2,cpn::R3> expFunc2 = { cpn::x_0 + cpn::x_1 + cpn::x_2, cpn::x_0 + cpn::x_1 };

	const cpn::LF<cpn::R2,cpn::R3> _expFunc3 = expFunc2 + expFunc2;
	const cpn::F<cpn::R1,cpn::R3> expFunc3 = expFunc1 + expFunc1;

	cpn::R2 ress = ddk::eval(expFunc2,cpn::integer(10),cpn::frac(10,7),cpn::integer(10));

	static_assert(cpn::inspect_linearity<decltype(cpn::x_0 + cpn::x_1 + cpn::x_2)>,"wtf");
	const auto res = cpn::instance_as_function<cpn::real,ddk::mpl::type_pack<cpn::real,cpn::real,cpn::real>>(exp2);

	res == res;

	res + res;

	//cpn::derivative(expFunc);
}
