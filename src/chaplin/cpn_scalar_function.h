#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
#include "cpn_set.h"
#include "cpn_function_template_helper.h"
#include "cpn_space_ops.h"

namespace cpn
{

template<typename>
class function;

template<set_type ImSet, set_type DomSet>
class function<ImSet(DomSet)> : public function_impl<ImSet(mpl::terse_function_dominion<DomSet>)>
{
    typedef function_impl<ImSet(mpl::terse_function_dominion<DomSet>)> function_base_t;

public:
    typedef ImSet im_t;
    typedef DomSet dom_t;

    function() = default;
    function(const function_base_t& i_function);
    TEMPLATE(typename Callable)
    REQUIRES(IS_INSTANTIABLE_BY(Callable,ImSet,mpl::terse_function_dominion<DomSet>))
    function(const Callable& i_callable);
    TEMPLATE(typename ... Callables)
    REQUIRES(IS_NUMBER_OF_ARGS_GREATER(1,Callables...),IS_INSTANTIABLE_BY(Callables,ImSet,mpl::terse_function_dominion<DomSet>)...)
    function(const Callables& ... i_callables);

    bool operator==(const function& other) const;
    bool operator!=(const function& other) const;

protected:
    template<size_t ... Indexs, typename ...Callables>
    function(const ddk::mpl::sequence<Indexs...>&, const Callables& ... i_callables);
};

}

#include "cpn_scalar_function.inl"
