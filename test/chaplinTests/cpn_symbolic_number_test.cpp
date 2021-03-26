
#if defined(WIN32)

#define _ENABLE_EXTENDED_ALIGNED_STORAGE

#endif

#include <gtest/gtest.h>
#include "cpn_set.h"
#include "cpn_number_set.h"
#include "cpn_number_group.h"
#include "cpn_number_ring.h"
#include "cpn_number_module.h"
#include "cpn_number_field.h"
#include "cpn_number_vector_space.h"
#include "cpn_number.h"
#include "cpn_linear_function.h"
#include "cpn_scalar_function.h"
#include "ddk_rtti.h"
#include "ddk_static_counter.h"
#include "cpn_function_space.h"
#include "cpn_function_ops.h"
#include <utility>

#include <string>
#include <cstddef>

using namespace testing;

class CPNSymbolicNumberTest : public Test
{
};

template<cpn::set_type T>
void foo(const T& value)
{
}

TEST(CPNSymbolicNumberTest,defaultRationalSetConstruction)
{
	cpn::rational_group fooReal1 = cpn::frac(10,7);
	cpn::rational_group fooReal2 = cpn::frac(7,10);

	cpn::rational_group fooReal3 = fooReal1 + fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultRationalGroupConstruction)
{
	cpn::rational_group fooReal1 = cpn::frac(10,7);
	cpn::rational_group fooReal2 = cpn::frac(7,10);

	cpn::rational_group fooReal3 = fooReal1 + fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultGroupConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group fooReal1 = cpn::integer(10);
	cpn::real_group fooReal2 = cpn::integer(20);

	cpn::real_group fooReal3(fooReal1 + fooReal2);
}

TEST(CPNSymbolicNumberTest, defaultRingConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring fooReal1 = cpn::integer(10);
	cpn::real_ring fooReal2 = cpn::integer(20);

	cpn::real_ring fooReal3(fooReal1 + fooReal2);
	cpn::real_ring fooReal4(fooReal1 * fooReal2);

	cpn::real_ring kk2(0);
	cpn::real_group kk1 = kk2;
}

TEST(CPNSymbolicNumberTest, defaultModuleConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_field fooReal0 = cpn::integer(10);
	cpn::real_module fooReal1 = cpn::integer(10);
	cpn::real_module fooReal2 = cpn::integer(20);

	cpn::real_module fooReal3(fooReal1 + fooReal2);
	cpn::real_module fooReal4(fooReal0 ^ fooReal2);
}

TEST(CPNSymbolicNumberTest, defaultFieldConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real fooReal0 = cpn::integer(10);
	cpn::real fooReal1 = cpn::integer(10);

	cpn::real_module fooReal3 = fooReal0 + fooReal1;
	cpn::real_module fooReal4 = fooReal0 * fooReal1;
	cpn::real_module fooReal5 = fooReal0 / fooReal1;
}

TEST(CPNSymbolicNumberTest, defaultPowGroupConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group_3 fooReal1(0,0,0);//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_group_3 fooReal2(0,0,0);//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

//	cpn::real_ring_3 fooReal4 = fooReal2;
	cpn::real_group_3 fooReal3 = fooReal1 + fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultPowRingConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring_3 fooReal1(0,0,0);//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_ring_3 fooReal2(0,0,0);//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

	cpn::real_ring_3 fooReal3 = fooReal1 + fooReal2;
	cpn::real_ring_3 fooReal4 = fooReal1 * fooReal2;
	cpn::real_group_3 fooReal0 = fooReal4;
}

template<typename...>
struct my_class;
template<typename ImSet, typename ... Dom>
struct my_class<ImSet,ddk::mpl::type_pack<Dom...>> : public ddk::detail::inherited_functor_impl<ImSet,Dom...>
{
};

TEST(CPNSymbolicNumberTest, defaultPowModuleConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring fooReal0 = cpn::frac(10,5);
	cpn::real_field fooReal1(0);//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_module_3 fooReal2(0,0,0);//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

	auto my_var = cpn::x_0 * cpn::x_1 + cpn::x_1 * 2;// + cpn::sin(cpn::cos(cpn::x_0) + cpn::x_2 * 5);
	try
	{
		cpn::F<cpn::R2,cpn::R3> prova_0 = {my_var,my_var};

		cpn::F<cpn::R2,cpn::R3> prova_1 = prova_0 + prova_0;

		prova_0 == prova_1;

		cpn::F<cpn::R1,cpn::R3> prova1 = my_var;

		prova1 = prova1 + prova1;

		//cpn::derivative(prova_0);
	}
	catch(...)
	{
	}



	cpn::real_module_3 fooReal3 = fooReal1 ^ fooReal2;
    cpn::real_group_3 fooReal4 = fooReal2 + fooReal2;

    cpn::real_module_3 fooReal5 = fooReal2;

}

TEST(CPNSymbolicNumberTest, defaultPowFieldConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_field_3 fooReal0(0,0,0);// = cpn::symbolic_number(cpn::integer(10));
	cpn::real_field_3 fooReal1(0,0,0);// = cpn::symbolic_number(cpn::integer(10));

	cpn::real_field_3 fooReal3 = fooReal0 + fooReal1;
	cpn::real_field_3 fooReal4 = fooReal0 * fooReal1;
	cpn::real_field_3 fooReal5 = fooReal0 / fooReal1;
}

TEST(CPNSymbolicNumberTest, defaultVectorSpaceConstruction)
{
	cpn::R3 fooRes1(0,0,0);
	cpn::R3 fooRes2(0,0,0);
	cpn::real_ring res = fooRes1 * fooRes2;
}
