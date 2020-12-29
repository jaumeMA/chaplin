#include <gtest/gtest.h>
#include "cpn_symbolic_number.h"
#include <utility>

using namespace testing;

class CPNSymbolicNumberTest : public Test
{
};

TEST(CPNSymbolicNumberTest, defaultConstruction)
{
	cpn::symbolic_number_f foo = cpn::integer(10);

}