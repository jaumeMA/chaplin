
namespace cpn
{

template<typename ImSet,typename DomSet>
TEMPLATE(typename T)
REQUIRED(IS_INSTANTIABLE_BY(T,ImSet,DomSet))
scalar_function<ImSet(DomSet)>::scalar_function(T&& i_callable)
: function<ImSet(DomSet)>(i_callable.template instance<ImSet,DomSet>())
{
}

}