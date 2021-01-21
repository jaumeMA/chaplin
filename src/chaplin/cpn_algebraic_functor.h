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
using forget_add = forgetful_functor<Structure,typename Structure::add_operation>;
template<typename Structure>
using forget_add_inverse = forgetful_functor<Structure,typename Structure::add_inverse_operation>;
template<typename Structure>
using forget_addition = forgetful_functor<Structure,typename Structure::add_operation,typename Structure::add_inverse_operation>;
template<typename Structure>
using forget_mult = forgetful_functor<Structure,typename Structure::mult_operation>;
template<typename Structure>
using forget_div = forgetful_functor<Structure,typename Structure::div_operation>;
template<typename Structure>
using forget_mod = forgetful_functor<Structure,typename Structure::mod_operation>;

}
