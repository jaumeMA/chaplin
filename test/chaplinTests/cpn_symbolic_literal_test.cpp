#include <gtest/gtest.h>
#include "cpn_builtin_symbolic_literals.h"
#include <utility>

using namespace testing;

class CPNSymbolicLiteralTest: public Test
{
};

TEST(CPNSymbolicLiteralTest,defaultLinearFunction)
{
	constexpr cpn::integer_symbolic_literal symInt1 = 10;
	constexpr cpn::integer_symbolic_literal symInt2 = 10;
	constexpr cpn::integer_symbolic_literal symInt3 = symInt1 + symInt2;

	const auto kk = ddk::mpl::static_number<symInt3.number()>{};

	static_assert(symInt3.number() == 20, "wtf");

	constexpr cpn::integer_symbolic_literal symInt4 = 11;
	constexpr cpn::integer_symbolic_literal symInt44 = 12;
	constexpr cpn::rational_symbolic_literal symFrac1 = cpn::frac(10,2);
	constexpr cpn::root_symbolic_literal symRoot1 = cpn::root(10,2);
	cpn::sum_symbolic_literal symSum1 = 10 + 2 * cpn::root(10,2) + 10;

	cpn::sum_symbolic_literal symSum2 = symInt3 + symSum1;
	cpn::sum_symbolic_literal symSum3 = symSum2 + symRoot1;
	////constexpr cpn::sum_symbolic_literal kk{};
	//constexpr cpn::sum_symbolic_literal symSum4 = symSum2 + symSum1;
}
