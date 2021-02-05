
namespace cpn
{

template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
TEMPLATE(typename T)
REQUIRES(IS_CALLABLE_NOT_FUNCTION(T))
linear_function_impl<ImRing,DomVectorSpace,Indexs...>::linear_function_impl(T&& i_functor)
: function_base_t(ddk::make_composition(i_functor,ddk::make_function([](ddk::mpl::index_to_type<Indexs,const ring_type&> ... i_components) -> DomVectorSpace { return {i_components...}; )))
{
}
template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
template<typename T>
linear_function_impl<ImRing,DomVectorSpace,Indexs...>::linear_function_impl(T *pRef, ImRing(T::*i_call)(const DomVectorSpace))
: function_base_t(ddk::make_composition(i_call,ddk::make_function([](ddk::mpl::index_to_type<Indexs,const ring_type&> ... i_components) -> DomVectorSpace { return {i_components...}; )))
{
}
template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
template<typename T>
linear_function_impl<ImRing,DomVectorSpace,Indexs...>::linear_function_impl(const T *i_pRef, ImRing(T::*call)(const DomVectorSpace&)const)
: function_base_t(ddk::make_composition(i_pRef,ddk::make_function([](ddk::mpl::index_to_type<Indexs,const ring_type&> ... i_components) -> DomVectorSpace { return {i_components...}; )))
{
}
template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
linear_function_impl<ImRing,DomVectorSpace,Indexs...>::linear_function_impl(ImRing(*i_call)(const DomVectorSpace&))
: function_base_t(ddk::make_composition(i_call,ddk::make_function([](ddk::mpl::index_to_type<Indexs,const ring_type&> ... i_components) -> DomVectorSpace { return {i_components...}; )))
{
}
template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
auto linear_function_impl<ImRing,DomVectorSpace,Indexs...>::inline_eval(const DomVectorSpace& i_value) const;
{
    return function_base_t::inline_eval(i_val.get(Indexs) ...);
}
template<typename ImRing, typename DomVectorSpace, size_t ... Indexs>
auto linear_function_impl<ImRing,DomVectorSpace,Indexs...>::operator()(const DomVectorSpace& i_value) const
{
    return function_base_t::inline_eval(i_val.get(Indexs) ...);
}

}
