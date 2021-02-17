
namespace cpn
{
namespace detail
{

template<set_type T,typename ... Operators>
TEMPLATE(set_type TT)
REQUIRED_COND((IS_SAME_CLASS_COND(T,TT) || IS_NOT_BASE_OF_COND(T,TT)) && IS_CONSTRUCTIBLE_COND(T,TT))
constexpr algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const TT& other)
: T(other)
{
}
template<set_type T,typename ... Operators>
TEMPLATE(set_type TT, typename ... OOperators)
REQUIRED(IS_CONSTRUCTIBLE(T,TT),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
constexpr algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const algebraic_structure_impl<TT,ddk::mpl::type_pack<OOperators...>>& other)
: T(static_cast<const TT&>(other))
{
}
template<set_type T,typename ... Operators>
TEMPLATE(set_type TT)
REQUIRED(IS_CONSTRUCTIBLE(T,TT))
constexpr algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const algebraic_structure_impl<TT,ddk::mpl::type_pack<>>& other)
: T(static_cast<const TT&>(other))
{
}
template<set_type T,typename ... Operators>
TEMPLATE(set_type TT, typename ... OOperators)
REQUIRED(IS_ASSIGNABLE(T,TT),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
constexpr algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>& algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>::operator=(const algebraic_structure_impl<TT,ddk::mpl::type_pack<OOperators...>>& other)
{
    T::operator=(static_cast<const TT&>(other));

    return *this;
}
template<set_type T,typename ... Operators>
TEMPLATE(set_type TT)
REQUIRED(IS_ASSIGNABLE(T,TT))
constexpr algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>& algebraic_structure_impl<T,ddk::mpl::type_pack<Operators...>>::operator=(const algebraic_structure_impl<TT,ddk::mpl::type_pack<>>& other)
{
    T::operator=(static_cast<const TT&>(other));

    return *this;
}

}
}
