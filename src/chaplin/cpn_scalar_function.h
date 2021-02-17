#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
#include "cpn_set.h"
#include "cpn_function_template_helper.h"

namespace cpn
{

template<typename>
class function;

template<set_type ImSet, set_type DomSet>
class function<ImSet(DomSet)> : public function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>
{
    typedef function_impl<ImSet(mpl::terse_function_dominion<DomSet>)> function_base_t;

public:
    TEMPLATE(typename T)
    REQUIRES(IS_INSTANTIABLE_BY(T,ImSet,DomSet))
    function(T&& i_callable);

    using function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>::m_functionImpl;
};

}

#include "cpn_scalar_function.inl"