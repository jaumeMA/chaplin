
namespace cpn
{
namespace detail
{

template<typename Set,typename ... Operators>
algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::algebraic_structure_impl(const Set& i_value)
: Set(i_value)
{
}
template<typename Set,typename ... Operators>
TEMPLATE(typename T)
REQUIRED(IS_SUPERSTRUCTURE_OF(T,algebraic_structure_impl))
algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>& algebraic_structure_impl<Set,ddk::mpl::type_pack<Operators...>>::operator=(T&& other)
{
    Set::operator=(std::forward<T>(other));

    return *this;
}

}
}
