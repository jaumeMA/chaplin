#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_vector_space.h"
#include "cpn_function.h"

#define DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(NAME,OP) \
friend inline linear_function_impl operator OP(const linear_function& i_lhs, const linear_function& i_rhs) \
{ \
    return static_cast<const base_function&>(i_lhs) OP static_cast<const base_function&>(i_rhs); \
}

namespace cpn
{

template<typename>
class linear_function;

namespace detail
{

template<typename ImFreeModule, typename DomFreeModule, size_t ... Indexs>
class linear_function_impl : public function<linear_function,ImFreeModule,ddk::mpl::index_to_type<Indexs,typename DomFreeModule::ring_type>...>
{
    static_assert(IS_RING(ImSet), "You shall provide Set as image");
    static_assert(IS_VECTOR_SPACE(DomFreeModule), "You shall provide Vector Space as dominion");

    typedef function<linear_function,ImFreeModule,ddk::mpl::index_to_type<Indexs,typename DomFreeModule::ring_type>...> function_base_t;

    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(sum,+)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION(subs,-)
    DEFINE_MATH_HIGHER_ORDER_BINARY_FRIEND_FUNCTION_CONSTANT(prod,*)

public:
    linear_function_impl(const ddk::constant_function<ImFreeModule>& i_constValue);
    template<size_t Component>
    linear_function_impl(const ddk::projection_callable<Component>& i_component);

	inline auto inline_eval(const DomFreeModule& i_value) const;
    inline auto operator()(const DomFreeModule& i_value) const;
};

}

template<typename ImFreeModule, typename DomFreeModule>
class linear_function<ImFreeModule(DomFreeModule)> : detail::linear_function_impl<ImFreeModule,DomFreeModule,typename mpl::make_sequence<0,DomFreeModule::rank()>::type>;
{
    typedef detail::linear_function_impl<ImFreeModule,DomFreeModule,typename mpl::make_sequence<0,DomFreeModule::rank()>::type> base_t;

public:
    using base_t::base_t;
};

}
