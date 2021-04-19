#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_function_concepts.h"
#include "cpn_set.h"
#include "cpn_function_impl.h"
#include "cpn_function_template_helper.h"
#include "cpn_space_ops.h"
#include "ddk_concepts.h"

namespace cpn
{
namespace detail
{

template<set_type,typename>
class scalar_function;
template<set_type Im, set_type ... Dom>
class scalar_function<Im,ddk::mpl::type_pack<Dom...>> : public function_impl<Im(ddk::mpl::type_pack<Dom...>)>
{
    typedef function_impl<Im(ddk::mpl::type_pack<Dom...>)> function_base_t;

public:
    scalar_function() = default;
    scalar_function(const function_base_t& i_function);
    TEMPLATE(typename Callable)
    REQUIRES(IS_INSTANTIABLE_BY(Callable,Im,ddk::mpl::type_pack<Dom...>))
    scalar_function(const Callable& i_callable);
};

template<coordinate_type,typename>
class vector_function;
template<coordinate_type Im,set_type ... Dom>
class vector_function<Im,ddk::mpl::type_pack<Dom...>> : public function_impl<Im(ddk::mpl::type_pack<Dom...>)>
{
    typedef function_impl<Im(ddk::mpl::type_pack<Dom...>)> function_base_t;

public:
    vector_function() = default;
    vector_function(const function_base_t& i_function);
    TEMPLATE(typename ... Callables)
    REQUIRES(IS_INSTANTIABLE_BY(Callables,typename Im::place_type,ddk::mpl::type_pack<Dom...>)...)
    vector_function(const Callables& ... i_callables);
};

template<bool,set_type Im,set_type Dom>
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

template<set_type Im, set_type Dom>
class function<Im(Dom)> : public detail::function_impl_resolver<IS_INDEXED_COND(Im),Im,Dom>::type
{
    typedef typename detail::function_impl_resolver<IS_INDEXED_COND(Im),Im,Dom>::type function_base_t;

public:
    typedef Im im_t;
    typedef Dom dom_t;
    using function_base_t::function_base_t;

    function() = default;
};

}

#include "cpn_builtin_functions.h"
#include "cpn_scalar_function.inl"