
namespace cpn
{
namespace detail
{

template<typename Functor, typename ImSet, typename DomSet>
template<typename ... Args>
functor_impl(Args&& ... i_args)
: m_functor(std::forward<Args>(i_args) ...)
{
}
template<typename Functor, typename ImSet, typename DomSet>
template<typename ... Args>
ImSet(Args&& ... i_args) const
{
    return m_functor(std::forward<Args>(i_args) ...);
}

}
}
