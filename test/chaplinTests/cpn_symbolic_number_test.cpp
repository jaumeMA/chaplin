#include <gtest/gtest.h>
#include "cpn_number_group.h"
#include "cpn_number_ring.h"
#include "cpn_number_module.h"
#include "cpn_number_field.h"
#include <utility>

using namespace testing;

class CPNSymbolicNumberTest : public Test
{
};

TEST(CPNSymbolicNumberTest, defaultGroupConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group fooReal1 = cpn::symbolic_number(cpn::integer(10));
	cpn::real_group fooReal2 = cpn::symbolic_number(cpn::integer(20));

	cpn::real_group fooReal3 = fooReal1 + fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultRingConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring fooReal1 = cpn::symbolic_number(cpn::integer(10));
	cpn::real_ring fooReal2 = cpn::symbolic_number(cpn::integer(20));

	cpn::real_ring fooReal3 = fooReal1 + fooReal2;
	cpn::real_ring fooReal4 = fooReal1 * fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultModuleConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring fooReal0 = cpn::symbolic_number(cpn::integer(10));
	cpn::real_module fooReal1 = cpn::symbolic_number(cpn::integer(10));
	cpn::real_module fooReal2 = cpn::symbolic_number(cpn::integer(20));

	cpn::real_module fooReal3 = fooReal1 + fooReal2;
	cpn::real_module fooReal4 = fooReal0 ^ fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultFieldConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real fooReal0 = cpn::symbolic_number(cpn::integer(10));
	cpn::real fooReal1 = cpn::symbolic_number(cpn::integer(10));

	cpn::real_module fooReal3 = fooReal0 + fooReal1;
	cpn::real_module fooReal4 = fooReal0 * fooReal1;
	cpn::real_module fooReal5 = fooReal0 / fooReal1;
}

TEST(CPNSymbolicNumberTest, defaultPowGroupConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group_3 fooReal1;//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_group_3 fooReal2;//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

	cpn::real_group_3 fooReal3 = fooReal1 + fooReal2;
}
//
//TEST(CPNSymbolicNumberTest, defaultPowRingConstruction)
//{
//	cpn::symbolic_number foo = cpn::integer(10);
//	cpn::real_ring_3 fooReal1;//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
//	cpn::real_ring_3 fooReal2;//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));
//
//	cpn::real_ring_3 fooReal3 = fooReal1 + fooReal2;
//	cpn::real_ring_3 fooReal4 = fooReal1 * fooReal2;
//}
//
//TEST(CPNSymbolicNumberTest, defaultPowModuleConstruction)
//{
//	cpn::symbolic_number foo = cpn::integer(10);
//	cpn::real_ring fooReal1;//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
//	cpn::real_module_3 fooReal2;//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));
//
//	cpn::real_ring_3 fooReal3 = fooReal1 ^ fooReal2;
//    cpn::real_group_3 fooReal4 = fooReal2 + fooReal2;
//}
