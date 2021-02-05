#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_set.h"
#include "cpn_function.h"

namespace cpn
{

//CONCEPTS!
template<typename>
class scalar_function;

template<typename ImSet, typename DomSet>
class scalar_function<ImSet(DomSet)> : public function<scalar_function,ImSet,DomSet>
{
    static_assert(IS_SET(ImSet), "You shall provide Set as image");
    static_assert(IS_SET(ImSet), "You shall provide Set as dominion");

    typedef function<scalar_function,ImSet,DomSet> function_base_t;

public:
    using function_base_t::function_base_t;
};

}
