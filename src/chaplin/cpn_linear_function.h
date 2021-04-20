#pragma once

#include "cpn_algebraic_concepts.h"
#include "cpn_vector_space.h"
#include "cpn_scalar_function.h"
#include "cpn_function_concepts.h"
#include "ddk_concepts.h"
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
class linear_function_impl<Im,Dom,ddk::mpl::sequence<Indexs...>> : public function<Im(Dom)>
{
    typedef function<Im(Dom)> function_base_t;

public:
    using function_base_t::operator();

    TEMPLATE(typename ... Callables)
    REQUIRES(IS_LINEAR_INSTANTIABLE(Callables)...)
    explicit linear_function_impl(Callables&& ... i_callables);

	inline auto inline_eval(const Dom& i_value) const;
    inline auto operator()(const Dom& i_value) const;

protected:
    linear_function_impl(const function_impl<Im(mpl::terse_function_dominion<Dom>)>& i_callable);
};

}

template<typename>
class linear_function;
template<free_module_type Im, free_module_type Dom>
class linear_function<Im(Dom)> : public detail::linear_function_impl<Im,Dom,typename ddk::mpl::make_sequence<0,Dom::rank>::type>
{
    typedef detail::linear_function_impl<Im,Dom,typename ddk::mpl::make_sequence<0,Dom::rank>::type> base_t;

    template<set_type IIm,typename DDom>
    friend inline linear_function<IIm(DDom)> operator+(const linear_function<IIm(DDom)>& i_lhs,const linear_function<IIm(DDom)>& i_rhs);
    template<set_type IIm,typename DDom>
    friend inline linear_function<IIm(DDom)> operator-(const linear_function<IIm(DDom)>& i_lhs,const linear_function<IIm(DDom)>& i_rhs);

public:
    using base_t::base_t;
    using base_t::operator();
};

}

#include "cpn_linear_function.inl"
