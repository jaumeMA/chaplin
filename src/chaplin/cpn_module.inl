
namespace cpn
{

template<typename ring>
const typename module_from_ring_traits<ring>::set_traits module_from_ring_traits<ring>::identity = ring::identity;

template<typename ring, typename ... modules>
sum_module_traits<ring,modules...>::module_prod_operation::module_prod_operation(const ring& i_ring)
: m_ring(i_ring)
{
}
template<typename ring, typename ... modules>
template<typename T>
typename sum_module_traits<ring,modules...>::sum_set_traits_t sum_module_traits<ring,modules...>::module_prod_operation::operator()(T&& i_value) const
{
    return m_ring ^ i_value;
}

}
