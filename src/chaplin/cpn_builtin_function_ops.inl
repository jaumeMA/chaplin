
#include "cpn_function_factor.h"
#include "ddk_function_exceptions.h"
#include "ddk_dynamic_visitor.h"

namespace cpn
{

template<typename Im,typename Dom,typename T>
ddk::detail::builtin_number_function<Im,Dom> instance_as_function(const builtin_numeric_expression<T>& i_exp)
{
	return { Im(i_exp.get()) };
}
template<typename Im,typename Dom,size_t Comp>
ddk::detail::builtin_component_function<Im,Dom> instance_as_function(const component_builtin_expression<Comp>& i_exp)
{
	return { ddk::mpl::static_number<Comp>{} };
}
template<typename Im,typename Dom,typename Expression>
ddk::detail::builtin_inverted_function<Im,Dom> instance_as_function(const builtin_inverted_expression<Expression>& i_exp)
{
	return { instance_as_function<Im,Dom>(i_exp.get()) };
}
template<typename Im,typename Dom,size_t ...Indexs,typename ... Expressions>
ddk::detail::builtin_add_nary_functor<Im,Dom> instance_as_function(const add_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp)
{
	std::vector<function_impl<Im(Dom)>> operands;

	i_exp.enumerate([&operands](auto&& i_exp){ operands.push_back(instance_as_function<Im,Dom>(i_exp)); });

	return { operands };
}
template<typename Im,typename Dom,size_t ...Indexs,typename ... Expressions>
ddk::detail::builtin_prod_nary_functor<Im,Dom> instance_as_function(const prod_nary_expression<ddk::mpl::sequence<Indexs...>,Expressions...>& i_exp)
{
	std::vector<function_impl<Im(Dom)>> operands;

	i_exp.enumerate([&operands](auto&& i_exp){ operands.push_back(instance_as_function<Im,Dom>(i_exp)); });

	return { operands };
}
TEMPLATE(typename Im,typename Dom,typename LhsExpression,typename RhsExpression)
REQUIRED(IS_INSTANTIABLE(LhsExpression),IS_INSTANTIABLE(RhsExpression))
ddk::detail::builtin_composed_function<Im,Dom> instance_as_function(const builtin_composed_expression<LhsExpression,RhsExpression>& i_exp)
{
	return { instance_as_function<Im,ddk::mpl::type_pack<Im>>(i_exp.get_lhs()),instance_as_function<Im,Dom>(i_exp.get_rhs()) };
}
TEMPLATE(typename Im,typename Dom,typename T)
REQUIRED(IS_INSTANTIABLE(T))
auto instance_as_function(const T& i_exp)
{
	return ddk::detail::builtin_expression_function<T,Im,Dom>{ };
}

template<typename Im,typename Dom>
bool operator==(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs)
{
	return visit([](auto&& i_lhs, auto&& i_rhs) { return hash(i_lhs) == hash(i_rhs); },i_lhs,i_rhs);
}
template<typename Im,typename Dom>
bool operator!=(const function<Im(Dom)>& i_lhs,const function<Im(Dom)>& i_rhs)
{
	return (visit([](auto&& i_lhs,auto&& i_rhs) { return hash(i_lhs) == hash(i_rhs); },i_lhs,i_rhs) == false);
}
template<closed_additive_type Im,typename ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)> operator+(const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_lhs,const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_rhs)
{
	return visit([](auto&& ii_lhs,auto&& ii_rhs) -> function_impl<Im(ddk::mpl::type_pack<Dom...>)> { return ii_lhs + ii_rhs; },i_lhs,i_rhs);
}
template<closed_substractive_type Im,typename ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)> operator-(const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_lhs,const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_rhs)
{
	return visit([](auto&& ii_lhs,auto&& ii_rhs) -> function_impl<Im(ddk::mpl::type_pack<Dom...>)> { return ddk::detail::operator-(ii_lhs,ii_rhs); },i_lhs,i_rhs);
}
template<closed_multiplicative_type Im,typename ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)> operator*(const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_lhs,const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_rhs)
{
	return visit([](auto&& ii_lhs,auto&& ii_rhs) -> function_impl<Im(ddk::mpl::type_pack<Dom...>)> { return ddk::detail::operator*(ii_lhs,ii_rhs); },i_lhs,i_rhs);
}
template<closed_divisible_type Im,typename ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)> operator/(const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_lhs,const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_rhs)
{
	return visit([](auto&& ii_lhs,auto&& ii_rhs) -> function_impl<Im(ddk::mpl::type_pack<Dom...>)> { return ddk::detail::operator/(ii_lhs,ii_rhs); },i_lhs,i_rhs);
}

}

namespace ddk
{
namespace detail
{

TEMPLATE(typename T,typename TT)
REQUIRED(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
bool operator==(const T& i_lhs,const TT& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
bool operator!=(const T& i_lhs,const TT& i_rhs)
{
	return hash(i_lhs) != hash(i_rhs);
}

template<cpn::closed_additive_type Im,typename ... Dom>
auto operator+(const builtin_number_function<Im,mpl::type_pack<Dom...>>& i_lhs,const builtin_number_function<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	return ddk::detail::builtin_number_function<Im,mpl::type_pack<Dom...>>{ i_lhs.get_number() + i_rhs.get_number() };
}
template<typename Im,typename ... Dom>
auto operator+(const builtin_number_function<Im,mpl::type_pack<Dom...>>& i_lhs,const builtin_add_nary_functor<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	builtin_add_nary_functor<Im,mpl::type_pack<Dom...>> res;
	bool alreadyAdded = false;

	i_rhs.enumerate([&alreadyAdded,&res,&i_lhs](auto&& i_operand)
	{
		if constexpr(std::is_same<builtin_number_function<Im,mpl::type_pack<Dom...>>,decltype(i_operand)>::value && cpn::additive_type<Im>)
		{
			if(!alreadyAdded)
			{
				const Im sum = i_lhs + i_operand;

				if(sum != Im::sum_operation::identity)
				{
					res.add(sum);
				}

				alreadyAdded = true;
			}
			else
			{
				res.add(i_operand);
			}
		}
		else
		{
			res.add(i_operand);
		}
	});

	if(alreadyAdded == false)
	{
		res.add(i_lhs);
	}

	return res;
}
template<typename Im,typename ... Dom>
auto operator+(const builtin_add_nary_functor<Im,mpl::type_pack<Dom...>>& i_lhs,const ddk::detail::builtin_number_function<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	builtin_add_nary_functor<Im,mpl::type_pack<Dom...>> res;
	bool alreadyAdded = false;

	i_lhs.enumerate([&alreadyAdded,&res,&i_rhs](auto&& i_operand)
	{
		if constexpr(std::is_same<builtin_number_function<Im,mpl::type_pack<Dom...>>,decltype(i_operand)>::value && cpn::additive_type<Im>)
		{
			if(!alreadyAdded)
			{
				const Im sum = i_rhs + i_operand;

				if(sum != Im::sum_operation::identity)
				{
					res.add(sum);
				}

				alreadyAdded = true;
			}
			else
			{
				res.add(i_operand);
			}
		}
		else
		{
			res.add(i_operand);
		}
	});

	if(alreadyAdded == false)
	{
		res.add(i_rhs);
	}

	return res;
}
template<typename T, typename Im,typename ... Dom>
auto operator+(const T& i_lhs,const builtin_add_nary_functor<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	return cpn::factor(i_rhs.combine(i_lhs));
}
template<typename T,typename Im,typename ... Dom>
auto operator+(const builtin_add_nary_functor<Im,mpl::type_pack<Dom...>>& i_lhs, const T& i_rhs)
{
	return cpn::factor(i_lhs.combine(i_rhs));
}
template<typename Im,typename ... Dom>
auto operator+(const builtin_add_nary_functor<Im,mpl::type_pack<Dom...>>& i_lhs,const builtin_add_nary_functor<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	builtin_add_nary_functor<Im,mpl::type_pack<Dom...>> res;

	i_lhs.enumerate([&res,&i_rhs](auto&& i_operand)
	{
		res.add(i_operand + i_rhs);
	});

	return cpn::factor(res);
}
template<size_t ... Indexs, typename Im,typename ... Dom>
inline auto fusioned_sum(const mpl::sequence<Indexs...>&, const builtin_fusioned_function<Im,mpl::type_pack<Dom...>>& i_lhs,const builtin_fusioned_function<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	return builtin_fusioned_function<Im,mpl::type_pack<Dom...>>{ ddk::fusion((i_lhs.template get_callable<Indexs>() + i_rhs.template get_callable<Indexs>())...) };
}
template<typename Im,typename ... Dom>
auto operator+(const builtin_fusioned_function<Im,mpl::type_pack<Dom...>>& i_lhs,const builtin_fusioned_function<Im,mpl::type_pack<Dom...>>& i_rhs)
{
	typedef typename mpl::make_sequence<0,Im::num_places>::type range_seq;

	return fusioned_sum(range_seq{},i_lhs,i_rhs);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
auto operator+(const T& i_lhs,const TT& i_rhs)
{
	return builtin_add_nary_functor{ i_lhs,i_rhs };
}

template<cpn::closed_additive_type Im,typename ... Dom>
auto operator*(const ddk::detail::builtin_number_function<Im,Dom...>& i_lhs,const ddk::detail::builtin_number_function<Im,Dom...>& i_rhs)
{
	return ddk::detail::builtin_number_function<Im,Dom...>{ i_lhs.get_number()* i_rhs.get_number() };
}
template<typename T,typename Im,typename ... Dom>
auto operator*(const T& i_lhs,const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs)
{
	ddk::detail::builtin_add_nary_functor<Im,Dom...> res;

	i_rhs.enumerate([&res,&i_lhs](auto&& i_operand)
	{
		res.add(i_lhs * i_operand);
	});

	return res;
}
template<typename T,typename Im,typename ... Dom>
auto operator*(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs,const T& i_rhs)
{
	ddk::detail::builtin_add_nary_functor<Im,Dom...> res;

	i_lhs.enumerate([&res,&i_rhs](auto&& i_operand)
	{
		res.add(i_rhs * i_operand);
	});

	return res;
}
template<typename T,typename Im,typename ... Dom>
auto operator*(const T& i_lhs,const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_rhs)
{
	return i_rhs.combine(i_lhs);
}
template<typename T,typename Im,typename ... Dom>
auto operator*(const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_lhs,const T& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
template<typename Im,typename ... Dom>
auto operator*(const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_lhs,const ddk::detail::builtin_add_nary_functor<Im,Dom...>& i_rhs)
{
	ddk::detail::builtin_add_nary_functor<Im,Dom...> res;

	i_rhs.enumerate([&res,&i_lhs](auto&& i_operand)
	{
		res.add(i_operand * i_rhs);
	});

	return cpn::factor(res);
}
template<typename Im,typename ... Dom>
auto operator*(const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_lhs,const ddk::detail::builtin_prod_nary_functor<Im,Dom...>& i_rhs)
{
	return i_lhs.combine(i_rhs);
}
TEMPLATE(typename T,typename TT)
REQUIRED(IS_BUILTIN_FUNCTION(T),IS_BUILTIN_FUNCTION(TT))
auto operator*(const T& i_lhs,const TT& i_rhs)
{
	return builtin_prod_nary_functor{ i_lhs,i_rhs };
}

}
}