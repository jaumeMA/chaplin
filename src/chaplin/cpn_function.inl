
namespace cpn
{

template<set_type Im,set_type ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)>::function_impl(const function_impl& other)
: function_base_t(other)
{
}
template<set_type Im,set_type ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)>::function_impl(function_impl&& other)
: function_base_t(std::move(other))
{
}

}
