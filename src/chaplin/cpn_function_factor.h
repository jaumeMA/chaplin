#pragma once

#include "ddk_type_concepts.h"
#include "ddk_concepts.h"
#include <unordered_map>

namespace cpn
{

template<typename Im, typename ... Dom>
class function_factor
{
	struct function_hash_equalizer
	{
		function_hash_equalizer() = default;
		inline bool operator()(size_t i_lhs, size_t i_rhs) const;
	};
	typedef std::unordered_map<size_t,std::pair<size_t,function_impl<Im(ddk::mpl::type_pack<Dom...>)>>,std::hash<size_t>,function_hash_equalizer> operand_map_t;

public:
	function_factor(const ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function);

	inline void feed(const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_callable);
	inline function_impl<Im(ddk::mpl::type_pack<Dom...>)> resolve();

private:
	mutable operand_map_t m_operands;
};

template<typename Im, typename ... Dom>
inline function_impl<Im(ddk::mpl::type_pack<Dom...>)> factor(const ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function);

}

#include "cpn_function_factor.inl"