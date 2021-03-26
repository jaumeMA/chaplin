
#include "cpn_function_derivative_visitor.h"

namespace cpn
{

template<metric_space_type Im,metric_space_type Dom, size_t ... RankDomIndexs>
inline ddk::high_order_array<function<Im(Dom)>,get_rank<Im>(),get_rank<Dom>()> _derivative(const function<Im(Dom)>& i_function, const ddk::mpl::sequence<RankDomIndexs...>&)
{
	auto kk = { visit<cpn::derivative_visitor<Im,Dom,RankDomIndexs>>(i_function) ... };

	return {};
}

template<function_type Func>
ddk::high_order_array<Func,get_rank<typename Func::im_t>(),get_rank<typename Func::dom_t>()> derivative(const Func& i_func)
{
	return _derivative<typename Func::im_t,typename Func::dom_t>(i_func,typename ddk::mpl::make_sequence<0,get_rank<typename Func::dom_t>()>::type{});
}

}