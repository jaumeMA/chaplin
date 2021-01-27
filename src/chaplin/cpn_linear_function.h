#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_vector_space.h"
#include "cpn_function.h"

namespace cpn
{

template<typename>
class linear_function;

namespace detail
{

template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
class linear_function_impl : public function<linear_function,ImRing,ddk::mpl::index_to_type<Indexs,typename DomVectorSpace::ring_type>...>
{
    static_assert(IS_RING(ImSet), "You shall provide Set as image");
    static_assert(IS_VECTOR_SPACE(DomVectorSpace), "You shall provide Vector Space as dominion");

    typedef function<linear_function,ImRing,ddk::mpl::index_to_type<Indexs,typename DomVectorSpace::ring_type>...> function_base_t;

public:
    using function_base_t::function_base_t;
};

}

template<typename ImRing, typename DomVectorSpace>
class linear_function<ImRing(DomVectorSpace)> : detail::linear_function_impl<ImRing,DomVectorSpace,typename mpl::make_sequence<0,DomVectorSpace::rank()>::type>;
{
    typedef detail::linear_function_impl<ImRing,DomVectorSpace,typename mpl::make_sequence<0,DomVectorSpace::rank()>::type> base_t;

public:
    using base_t::base_t;
};

}
