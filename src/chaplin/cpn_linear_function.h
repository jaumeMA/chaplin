#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_vector_space.h"
#include "cpn_function.h"
#include "ddk_constant_callable.h"
#include "ddk_projection_callable.h"

namespace cpn
{

template<typename>
class linear_function;

namespace detail
{

template<typename,typename,typename>
class linear_function_impl;
    
template<free_module_type Im, free_module_type Dom, size_t ... Indexs>
class linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>> : public function_impl<Im(ddk::mpl::type_pack<const ddk::mpl::index_to_type<Indexs,typename Dom::ring_type>&...>)>
{
    typedef function_impl<Im(ddk::mpl::type_pack<const ddk::mpl::index_to_type<Indexs,typename Dom::ring_type>&...>)> function_base_t;

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(linear_function_impl,sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(linear_function_impl,subs,-)

public:
    TEMPLATE(typename T)
    REQUIRES(IS_LINEAR_INSTANTIABLE_BY(T,ImSet,DomSet))
    linear_function_impl(T&& i_callable);

	inline auto inline_eval(const Dom& i_value) const;
    inline auto operator()(const Dom& i_value) const;
};

}

template<typename>
class linear_function;
template<free_module_type Im, free_module_type Dom>
class linear_function<Im(const Dom&)> : detail::linear_function_impl<Im,Dom,typename ddk::mpl::make_sequence<0,Dom::rank>::type>
{
    typedef detail::linear_function_impl<Im,Dom,typename ddk::mpl::make_sequence<0,Dom::rank>::type> base_t;

public:
    using base_t::base_t;
};

}

#include "cpn_linear_function.inl"