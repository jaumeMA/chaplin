
namespace cpn
{

template<typename Im,typename ... Dom>
bool function_factor<Im,Dom...>::function_hash_equalizer::operator()(size_t i_lhs,size_t i_rhs) const
{
	return i_lhs == i_rhs || i_lhs == ~i_rhs;
}

template<typename Im,typename ... Dom>
function_factor<Im,Dom...>::function_factor(const ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function)
{
	i_function.enumerate([this](auto&& i_operand)
	{
		const size_t operandHash = hash(i_operand);

		typename operand_map_t::iterator itOperand = m_operands.find(operandHash);
		if(itOperand == m_operands.end())
		{
			m_operands.insert({operandHash,std::make_pair(1,i_operand)});
		}
		else
		{
			if(operandHash == itOperand->first)
			{
				itOperand->second.first++;
			}
			else
			{
				if(itOperand->second.first > 1)
				{
					itOperand->second.first--;
				}
				else
				{
					m_operands.erase(itOperand);
				}
			}
		}
	});
}
template<typename Im,typename ... Dom>
void function_factor<Im,Dom...>::feed(const function_impl<Im(ddk::mpl::type_pack<Dom...>)>& i_callable)
{
	const size_t operandHash = visit([](auto&& i_function) -> size_t { return hash(i_function); },i_callable);

	typename operand_map_t::iterator itOperand = m_operands.find(operandHash);
	if(itOperand == m_operands.end())
	{
		m_operands.insert({operandHash,std::make_pair(1,i_callable)});
	}
	else
	{
		if(operandHash == itOperand->first)
		{
			itOperand->second.first++;
		}
		else
		{
			if(itOperand->second.first > 1)
			{
				itOperand->second.first--;
			}
			else
			{
				m_operands.erase(itOperand);
			}
		}
	}
}
template<typename Im,typename ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)> function_factor<Im,Dom...>::resolve()
{
	ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>> res;

	typename operand_map_t::iterator itOperand = m_operands.begin();
	for(;itOperand!= m_operands.end();++itOperand)
	{
		const std::pair<size_t,function_impl<Im(ddk::mpl::type_pack<Dom...>)>>& functionPair = itOperand->second;

		if(functionPair.first > 0)
		{
			res.add(ddk::detail::builtin_prod_nary_functor<Im,ddk::mpl::type_pack<Dom...>>{ ddk::detail::builtin_number_function<Im,ddk::mpl::type_pack<Dom...>>{ static_cast<int>(functionPair.first) },functionPair.second });
		}
	}

	return res;
}

template<typename Im,typename ... Dom>
function_impl<Im(ddk::mpl::type_pack<Dom...>)> factor(const ddk::detail::builtin_add_nary_functor<Im,ddk::mpl::type_pack<Dom...>>& i_function)
{
	function_factor<Im,Dom...> factorizer(i_function);

	return factorizer.resolve();
}

}