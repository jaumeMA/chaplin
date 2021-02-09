#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
#include "cpn_set.h"
#include "cpn_function.h"

namespace cpn
{

//CONCEPTS!
template<typename>
class scalar_function;

template<typename ImSet, typename DomSet>
class scalar_function<ImSet(DomSet)> : public function<ImSet(DomSet)>
{
    //static_assert(IS_SET(ImSet), "You shall provide Set as image");
    //static_assert(IS_SET(ImSet), "You shall provide Set as dominion");

public:
    TEMPLATE(typename T)
    REQUIRES(IS_INSTANTIABLE_BY(T,ImSet,DomSet))
    scalar_function(T&& i_callable);
};

}

#include "cpn_scalar_function.inl"