
namespace cpn
{
namespace detail
{

template<typename Set,typename ... Operators>
TEMPLATE(typename T)
REQUIRED_COND((IS_SAME_CLASS_COND(Set,T) || IS_NOT_BASE_OF_COND(Set,T)) && IS_CONSTRUCTIBLE_COND(Set,T))
constexpr algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const T& other)
: Set(other)
{
}
template<typename Set,typename ... Operators>
TEMPLATE(typename SSet, typename ... OOperators)
REQUIRED(IS_CONSTRUCTIBLE(Set,SSet),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
constexpr algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<OOperators...>>& other)
: Set(static_cast<const SSet&>(other))
{
}
template<typename Set,typename ... Operators>
TEMPLATE(typename SSet)
REQUIRED(IS_CONSTRUCTIBLE(Set,SSet))
constexpr algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<>>& other)
: Set(static_cast<const SSet&>(other))
{
}
template<typename Set,typename ... Operators>
TEMPLATE(typename SSet, typename ... OOperators)
REQUIRED(IS_ASSIGNABLE(Set,SSet),IS_SUPERSTRUCTURE_OF(ddk::mpl::type_pack<OOperators...>,operators_pack))
constexpr algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>& algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::operator=(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<OOperators...>>& other)
{
    Set::operator=(static_cast<const SSet&>(other));

    return *this;
}
template<typename Set,typename ... Operators>
TEMPLATE(typename SSet)
REQUIRED(IS_ASSIGNABLE(Set,SSet))
constexpr algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>& algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::operator=(const algebraic_structure_impl<SSet,ddk::mpl::type_pack<>>& other)
{
    Set::operator=(static_cast<const SSet&>(other));

    return *this;
}

}
}
