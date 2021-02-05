
namespace cpn
{

template<typename ImSet, typename DomSet>
math_function<ImSet(DomSet)>::math_function(ddk::distributed_pointer_wrapper<function_base_t> i_impl)
: m_impl(i_impl)
{
}



}
