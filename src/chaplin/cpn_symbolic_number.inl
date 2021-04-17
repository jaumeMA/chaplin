
namespace cpn
{
namespace detail
{

template<typename T>
size_t symbolic_number_hash_visitor::operator()(const T& i_number) const
{
	return hash(i_number);
}

}

TEMPLATE(typename Arg, typename ... Args)
REQUIRED(IS_CONSTRUCTIBLE(nested_number_t,Arg,Args...))
symbolic_number::symbolic_number(Arg&& i_arg, Args&& ... i_args)
: m_number(std::forward<Arg>(i_arg),std::forward<Args>(i_args)...)
{
}
TEMPLATE(typename T)
REQUIRED(IS_ASSIGNABLE(nested_number_t,T))
symbolic_number& symbolic_number::operator=(T&& i_number)
{
    m_number = std::forward<T>(i_number);

    return *this;
}

}
