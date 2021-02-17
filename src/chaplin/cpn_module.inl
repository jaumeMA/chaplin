
namespace cpn
{

template<module_type ... T>
template<typename T1, typename T2>
typename sum_mod_operation<T...>::sum_set_traits_t sum_mod_operation<T...>::module_prod_operation::operator()(T1&& i_lhs, T2&& i_rhs) const
{
    return i_lhs ^ i_rhs;
}

}
