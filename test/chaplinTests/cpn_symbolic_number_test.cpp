#include <gtest/gtest.h>
#include "cpn_number_group.h"
#include <utility>

using namespace testing;

class CPNSymbolicNumberTest : public Test
{
};

TEST(CPNSymbolicNumberTest, defaultConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group fooReal1 = cpn::symbolic_number(cpn::integer(10));
	cpn::real_group fooReal2 = cpn::symbolic_number(cpn::integer(20));

	cpn::real_group fooReal3 = fooReal1 + fooReal2;
}