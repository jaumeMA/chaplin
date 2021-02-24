
#if defined(WIN32)

#define _ENABLE_EXTENDED_ALIGNED_STORAGE

#endif

#include <gtest/gtest.h>
#include "cpn_number_group.h"
#include "cpn_number_ring.h"
#include "cpn_number_module.h"
#include "cpn_number_field.h"
#include "cpn_number_vector_space.h"
#include "cpn_linear_function.h"
#include "cpn_scalar_function.h"
#include "ddk_rtti.h"
#include "ddk_static_counter.h"
#include "cpn_function_derivative_visitor.h"
#include <utility>

#include <string>
#include <cstddef>

using namespace testing;

class CPNSymbolicNumberTest : public Test
{
};

TEST(CPNSymbolicNumberTest, defaultRationalGroupConstruction)
{
	cpn::rational_group fooReal1 = cpn::rational_set(10,7);
	cpn::rational_group fooReal2 = cpn::rational_set(7,10);

	cpn::rational_group fooReal3 = fooReal1 + fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultGroupConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group fooReal1 = cpn::real_set(cpn::integer(10));
	cpn::real_group fooReal2 = cpn::real_set(cpn::integer(20));

	cpn::real_group fooReal3(fooReal1 + fooReal2);
}

TEST(CPNSymbolicNumberTest, defaultRingConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring fooReal1 = cpn::real_set(cpn::integer(10));
	cpn::real_ring fooReal2 = cpn::real_set(cpn::integer(20));

	cpn::real_ring fooReal3(fooReal1 + fooReal2);
	cpn::real_ring fooReal4(fooReal1 * fooReal2);

	cpn::real_ring kk2;
	cpn::real_group kk1 = kk2;
}

TEST(CPNSymbolicNumberTest, defaultModuleConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring fooReal0 = cpn::real_set(cpn::integer(10));
	cpn::real_module fooReal1 = cpn::real_set(cpn::integer(10));
	cpn::real_module fooReal2 = cpn::real_set(cpn::integer(20));

	cpn::real_module fooReal3(fooReal1 + fooReal2);
	cpn::real_module fooReal4(fooReal0 ^ fooReal2);
}

TEST(CPNSymbolicNumberTest, defaultFieldConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real fooReal0 = cpn::real_set(cpn::integer(10));
	cpn::real fooReal1 = cpn::real_set(cpn::integer(10));

	cpn::real_module fooReal3 = fooReal0 + fooReal1;
	cpn::real_module fooReal4 = fooReal0 * fooReal1;
	cpn::real_module fooReal5 = fooReal0 / fooReal1;
}

TEST(CPNSymbolicNumberTest, defaultPowGroupConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_group_3 fooReal1;//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_group_3 fooReal2;//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

//	cpn::real_ring_3 fooReal4 = fooReal2;
	cpn::real_group_3 fooReal3 = fooReal1 + fooReal2;
}

TEST(CPNSymbolicNumberTest, defaultPowRingConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_ring_3 fooReal1;//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_ring_3 fooReal2;//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

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
	cpn::real_ring fooReal0 = cpn::rational_set(10,5);
	cpn::real_ring fooReal1;//(cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)),cpn::symbolic_number(cpn::integer(10)));
	cpn::real_module_3 fooReal2;//(cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)),cpn::symbolic_number(cpn::integer(20)));

	constexpr auto my_var = 2 * cpn::x_0 + cpn::x_1 + cpn::sin(cpn::x_0 + cpn::x_2 * 5);
	try
	{
		cpn::function<cpn::real_free_module_2(cpn::real_free_module_3)> prova{ my_var, my_var };

//		cpn::function<cpn::real_ring(cpn::real_free_module_3)> prova2 = prova + my_var;
//
//		cpn::derivative_visitor<cpn::real_ring,cpn::real_free_module_3> multiVisitor;
//
//		cpn::function<cpn::real_ring(cpn::real_free_module_3)> prova_prima = ddk::visit(multiVisitor,prova.m_functionImpl);
	}
	catch(...)
	{
	}



	cpn::real_ring_3 fooReal3 = fooReal1 ^ fooReal2;
    cpn::real_group_3 fooReal4 = fooReal2 + fooReal2;

    cpn::real_free_module_3 fooReal5 = fooReal2;

}

TEST(CPNSymbolicNumberTest, defaultPowFieldConstruction)
{
	cpn::symbolic_number foo = cpn::integer(10);
	cpn::real_field_3 fooReal0;// = cpn::symbolic_number(cpn::integer(10));
	cpn::real_field_3 fooReal1;// = cpn::symbolic_number(cpn::integer(10));

	cpn::real_field_3 fooReal3 = fooReal0 + fooReal1;
	cpn::real_field_3 fooReal4 = fooReal0 * fooReal1;
	cpn::real_field_3 fooReal5 = fooReal0 / fooReal1;
}

TEST(CPNSymbolicNumberTest, defaultVectorSpaceConstruction)
{
	cpn::real_vector_space_3 fooRes1;
	cpn::real_vector_space_3 fooRes2;
	cpn::real_ring res = fooRes1 * fooRes2;
}
