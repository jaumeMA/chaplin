
namespace cpn
{

template<typename ... Modules>
template<typename T1, typename T2>
typename sum_mod_operation<Modules...>::sum_set_traits_t sum_mod_operation<Modules...>::module_prod_operation::operator()(T1&& i_lhs, T2&& i_rhs) const
{
    return i_lhs ^ i_rhs;
}

}
