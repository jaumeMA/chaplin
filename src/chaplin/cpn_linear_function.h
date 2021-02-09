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
    
template<typename ImFreeModule, typename DomFreeModule, size_t ... Indexs>
class linear_function_impl<ImFreeModule,DomFreeModule,ddk::mpl::sequence<Indexs...>> : public function<ImFreeModule(const ddk::mpl::index_to_type<Indexs,typename DomFreeModule::ring_type>& ...)>
{
    //static_assert(IS_RING(ImFreeModule), "You shall provide Set as image");
    //static_assert(IS_VECTOR_SPACE(DomFreeModule), "You shall provide Vector Space as dominion");

    typedef function<ImFreeModule(const ddk::mpl::index_to_type<Indexs,typename DomFreeModule::ring_type>& ...)> function_base_t;

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(linear_function_impl,sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(linear_function_impl,subs,-)

public:
    linear_function_impl(const ddk::constant_callable<ImFreeModule>& i_constValue);
    template<size_t Component>
    linear_function_impl(const ddk::projection_callable<Component>& i_component);

	inline auto inline_eval(const DomFreeModule& i_value) const;
    inline auto operator()(const DomFreeModule& i_value) const;
};

}

template<typename>
class linear_function;
template<typename ImFreeModule, typename DomFreeModule>
class linear_function<ImFreeModule(const DomFreeModule&)> : detail::linear_function_impl<ImFreeModule,DomFreeModule,typename ddk::mpl::make_sequence<0,DomFreeModule::rank>::type>
{
    typedef detail::linear_function_impl<ImFreeModule,DomFreeModule,typename ddk::mpl::make_sequence<0,DomFreeModule::rank>::type> base_t;

public:
    using base_t::base_t;
};

}

#include "cpn_linear_function.inl"