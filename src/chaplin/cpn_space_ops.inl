
namespace cpn
{

template<set_type T>
constexpr size_t get_rank()
{
	return 1;
}

template<free_module_type T>
constexpr size_t get_rank()
{
	return T::rank;
}

}