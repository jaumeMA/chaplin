
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
//template<set_type Im,set_type ... Dom>
//TEMPLATE(typename Callable)
//REQUIRED(IS_BUILTIN_FUNCTION(Callable))
//function_impl<Im(ddk::mpl::type_pack<Dom...>)>::function_impl(const Callable& i_callable)
//: function_base_t(i_callable)
//{
//}

}