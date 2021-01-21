#pragma once

namespace cpn
{

template<typename,typename ...>
struct forgetful_functor;

template<typename Set, typename ... Operators, typename ... Operations>
struct forgetful_functor<algebraic_structure<Set,Operators...>,Operations...>
{
    typedef detail::algebraic_structure_impl<Set,typename ddk::mpl::type_pack<Operators...>::template drop<Operations...>::type> type;
};

template<typename Structure>
using forget_add = typename forgetful_functor<Structure,typename Structure::add_operation>::type;
template<typename Structure>
using forget_add_inverse = typename forgetful_functor<Structure,typename Structure::add_inverse_operation>::type;
template<typename Structure>
using forget_mult = typename forgetful_functor<Structure,typename Structure::mult_operation>::type;
template<typename Structure>
using forget_div = typename forgetful_functor<Structure,typename Structure::div_operation>::type;
template<typename Structure>
using forget_mod = typename forgetful_functor<Structure,typename Structure::mod_operation>::type;

}
