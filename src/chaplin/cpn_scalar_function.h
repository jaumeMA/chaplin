#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
#include "cpn_set.h"
#include "cpn_function_template_helper.h"
#include "cpn_space_ops.h"

namespace cpn
{
namespace detail
{

template<set_type,typename>
class scalar_function;
template<set_type ImSet, set_type ... DomSet>
class scalar_function<ImSet,ddk::mpl::type_pack<DomSet...>> : public function_impl<ImSet(ddk::mpl::type_pack<DomSet...>)>
{
    typedef function_impl<ImSet(ddk::mpl::type_pack<DomSet...>)> function_base_t;

public:
    scalar_function() = default;
    scalar_function(const function_base_t& i_function);
    TEMPLATE(typename Callable)
    REQUIRES(IS_INSTANTIABLE_BY(Callable,ImSet,ddk::mpl::type_pack<DomSet...>))
    scalar_function(const Callable& i_callable);
};

template<coordinate_type,typename>
class vector_function;
template<coordinate_type ImSet,set_type ... DomSet>
class vector_function<ImSet,ddk::mpl::type_pack<DomSet...>> : public function_impl<ImSet(ddk::mpl::type_pack<DomSet...>)>
{
    typedef function_impl<ImSet(ddk::mpl::type_pack<DomSet...>)> function_base_t;

public:
    vector_function() = default;
    vector_function(const function_base_t& i_function);
    TEMPLATE(typename ... Callables)
    REQUIRES(IS_INSTANTIABLE_BY(Callables,ImSet,ddk::mpl::type_pack<DomSet...>)...)
    vector_function(const Callables& ... i_callables);
};

template<bool,set_type ImSet,set_type DomSet>
struct function_impl_resolver;

template<set_type Im,set_type Dom>
struct function_impl_resolver<true,Im,Dom>
{
    typedef vector_function<Im,mpl::terse_function_dominion<Dom>> type;
};
template<set_type Im,set_type Dom>
struct function_impl_resolver<false,Im,Dom>
{
    typedef scalar_function<Im,mpl::terse_function_dominion<Dom>> type;
};

}

template<typename>
class function;

template<set_type ImSet, set_type DomSet>
class function<ImSet(DomSet)> : public detail::function_impl_resolver<IS_INDEXED_COND(ImSet),ImSet,DomSet>::type
{
    typedef typename detail::function_impl_resolver<IS_INDEXED_COND(ImSet),ImSet,DomSet>::type function_base_t;

public:
    typedef ImSet im_t;
    typedef DomSet dom_t;
    using function_base_t::function_base_t;

    function() = default;
};

}

#include "cpn_scalar_function.inl"
