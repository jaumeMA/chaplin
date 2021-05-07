
#include "cpn_function_derivative_visitor.h"
#include "ddk_iterable.h"

namespace cpn
{

template<template<typename> typename Function, metric_space_type Im,metric_space_type Dom, size_t ... RankDomIndexs>
ddk::high_order_array<Function<space_fundamental_type<Im>(Dom)>,get_rank<Im>(),get_rank<Dom>()> _derivative(const Function<Im(Dom)>& i_function, const ddk::mpl::sequence<RankDomIndexs...>&)
{
	ddk::high_order_array<Function<space_fundamental_type<Im>(Dom)>,get_rank<Im>(),get_rank<Dom>()> res;

	//for some unknown reason,msvc compiler complains about mismatching constness when deducing iterables container returned by visitor,so use an intermediate variable as tenporal workaround
	const ddk::high_order_array<Function<space_fundamental_type<Im>(Dom)>,get_rank<Im>()> derivateRes[get_rank<Dom>()] = { visit(derivative_visitor<Function,Im,Dom,RankDomIndexs>{},i_function) ... };

	ddk::concat(derivateRes[RankDomIndexs] ...);

	return res;
}

template<function_type Func>
auto derivative(const Func& i_func)
{
	static const auto rangeSeq = typename ddk::mpl::make_sequence<0,get_rank<typename Func::dom_t>()>::type{};

	return _derivative<typename Func::im_t,typename Func::dom_t>(i_func,rangeSeq);
}

}
