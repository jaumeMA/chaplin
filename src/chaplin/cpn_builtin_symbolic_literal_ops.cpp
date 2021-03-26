#include "cpn_builtin_symbolic_literal_ops.h"

namespace cpn
{

bool operator==(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
bool operator==(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return hash(i_lhs) == hash(i_rhs);
}
bool operator<(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return std::pow(i_lhs.number(),1.f / i_lhs.degree()) < std::pow(i_rhs.number(),1.f / i_rhs.degree());
}
bool operator<(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return std::log(i_lhs.number()) * std::log(i_rhs.base()) < std::log(i_rhs.number()) * std::log(i_lhs.base());
}
bool operator<(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	//pending
	return false;
}
bool operator<(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	//pending
	return false;
}

sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, i_rhs };
}
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	if(i_lhs.base() == i_rhs.base())
	{
		return { log_symbolic_literal(i_lhs.number() * i_rhs.number(),i_lhs.base()) };
	}
	else
	{
		return { i_lhs,i_rhs };
	}
}
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr (std::is_same<value_type,integer_symbolic_literal>::value)
		{
			res.emplace(i_value + i_lhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs, const integer_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,integer_symbolic_literal>::value)
		{
			res.emplace(i_value + i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator+(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_value + i_lhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_value + i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator+(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return {i_lhs,i_rhs};
}
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{i_lhs};

	i_rhs.enumerate([&res](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		res.emplace(i_value);
	});

	return res;
}
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{ i_rhs };

	i_lhs.enumerate([&res](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		res.emplace(i_value);
	});

	return res;
}
sum_symbolic_literal operator+(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return {i_lhs,i_rhs};
}
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,log_symbolic_literal>::value)
		{
			if(!alreadyApplied && i_value.base() == i_lhs.base())
			{
				res.emplace(log_symbolic_literal{i_value.number() * i_lhs.number(),i_lhs.base()});
				alreadyApplied = true;
			}
			else
			{
				res.emplace(i_value);
			}
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,log_symbolic_literal>::value)
		{
			if(!alreadyApplied && i_value.base() == i_rhs.base())
			{
				res.emplace(log_symbolic_literal{ i_value.number() * i_rhs.number(),i_rhs.base() });
				alreadyApplied = true;
			}
			else
			{
				res.emplace(i_value);
			}
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator+(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return {i_lhs,i_rhs};
}
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs, const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value + i_rhs);
	});

	return res;
}
sum_symbolic_literal operator+(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{i_lhs};

	res.emplace(i_rhs);

	return res;
}
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{ i_rhs };

	res.emplace(i_lhs);

	return res;
}
sum_symbolic_literal operator+(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}

sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs, -i_rhs };
}
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	if(i_lhs.base() == i_rhs.base())
	{
		return { log_symbolic_literal(i_lhs.number() / i_rhs.number(),i_lhs.base()) };
	}
	else
	{
		return { i_lhs,-i_rhs };
	}
}
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,integer_symbolic_literal>::value)
		{
			res.emplace(i_lhs - i_value);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(-i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,integer_symbolic_literal>::value)
		{
			res.emplace(i_value - i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(-i_rhs);
	}

	return res;
}
sum_symbolic_literal operator-(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_lhs - i_value);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(-i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_value - i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(-i_rhs);
	}

	return res;
}
sum_symbolic_literal operator-(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{ i_lhs };

	i_rhs.enumerate([&res](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		res.emplace(-i_value);
	});

	return res;
}
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{ -i_rhs };

	i_lhs.enumerate([&res](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		res.emplace(i_value);
	});

	return res;
}
sum_symbolic_literal operator-(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,log_symbolic_literal>::value)
		{
			if(!alreadyApplied && i_value.base() == i_lhs.base())
			{
				res.emplace(log_symbolic_literal{ -i_value.number() * i_lhs.number(),i_lhs.base() });
				alreadyApplied = true;
			}
			else
			{
				res.emplace(-i_value);
			}
		}
		else
		{
			res.emplace(-i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,log_symbolic_literal>::value)
		{
			if(!alreadyApplied && i_value.base() == i_rhs.base())
			{
				res.emplace(log_symbolic_literal{ -i_value.number() * i_rhs.number(),i_rhs.base() });
				alreadyApplied = true;
			}
			else
			{
				res.emplace(i_value);
			}
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(-i_rhs);
	}

	return res;
}
sum_symbolic_literal operator-(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value - i_rhs);
	});

	return res;
}
sum_symbolic_literal operator-(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{ i_lhs };

	res.emplace(-i_rhs);

	return res;
}
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res{ -i_rhs };

	res.emplace(i_lhs);

	return res;
}
sum_symbolic_literal operator-(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,-i_rhs };
}

prod_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return {i_lhs,i_rhs};
}
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	if(i_lhs.number() == i_rhs.number())
	{
		return { root_symbolic_literal(i_lhs.number(),i_lhs.degree() + i_rhs.degree()) };
	}
	else
	{
		return { i_lhs,i_rhs };
	}
}
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
sum_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_rhs.enumerate([&res,&i_lhs](const auto& i_value)
	{
		res.emplace(i_value * i_lhs);
	});

	return res;
}
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value * i_rhs);
	});

	return res;
}
prod_symbolic_literal operator*(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,integer_symbolic_literal>::value)
		{
			res.emplace(i_value * i_lhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,integer_symbolic_literal>::value)
		{
			res.emplace(i_value * i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_rhs.enumerate([&res,&i_lhs](const auto& i_value)
	{
		res.emplace(i_value * i_lhs);
	});

	return res;
}
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value * i_rhs);
	});

	return res;
}
prod_symbolic_literal operator*(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_value * i_lhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_value * i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_rhs.enumerate([&res,&i_lhs](const auto& i_value)
	{
		res.emplace(i_value * i_lhs);
	});

	return res;
}
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value * i_rhs);
	});

	return res;
}
prod_symbolic_literal operator*(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,root_symbolic_literal>::value)
		{
			res.emplace(i_value * i_lhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,rational_symbolic_literal>::value)
		{
			res.emplace(i_value * i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_rhs.enumerate([&res,&i_lhs](const auto& i_value)
	{
		res.emplace(i_value * i_lhs);
	});

	return res;
}
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value * i_rhs);
	});

	return res;
}
prod_symbolic_literal operator*(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_rhs.enumerate([&res,&i_lhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,log_symbolic_literal>::value)
		{
			res.emplace(i_value * i_lhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_lhs);
	}

	return res;
}
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;
	bool alreadyApplied = false;

	i_lhs.enumerate([&res,&i_rhs,&alreadyApplied](const auto& i_value)
	{
		typedef ddk::mpl::remove_qualifiers<decltype(i_value)> value_type;

		if constexpr(std::is_same<value_type,log_symbolic_literal>::value)
		{
			res.emplace(i_value * i_rhs);
			alreadyApplied = true;
		}
		else
		{
			res.emplace(i_value);
		}
	});

	if(!alreadyApplied)
	{
		res.emplace(i_rhs);
	}

	return res;
}
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value * i_rhs);
	});

	return res;
}
sum_symbolic_literal operator*(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_lhs.enumerate([&res,&i_rhs](const auto& i_value)
	{
		res.emplace(i_value * i_rhs);
	});

	return res;
}
sum_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	sum_symbolic_literal res;

	i_rhs.enumerate([&res,&i_lhs](const auto& i_value)
	{
		res.emplace(i_value * i_lhs);
	});

	return res;
}
prod_symbolic_literal operator*(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	prod_symbolic_literal res;

	i_rhs.enumerate([&res,&i_lhs](const auto& i_value)
	{
		res.emplace(i_value * i_lhs);
	});

	return res;
}

div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return {i_lhs,i_rhs};
}
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { integer_symbolic_literal{i_lhs.numerator()},i_lhs.denominator() * i_rhs };
}
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_rhs.denominator() * i_lhs,integer_symbolic_literal{i_rhs.numerator()} };
}
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { integer_symbolic_literal{i_lhs.numerator()},i_lhs.denominator() * i_rhs };
}
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return { i_rhs.denominator() * i_lhs,integer_symbolic_literal{i_rhs.numerator()} };
}
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	if(i_lhs.number() == i_rhs.number())
	{
		return { root_symbolic_literal(i_lhs.number(),i_lhs.degree() - i_rhs.degree()) };
	}
	else
	{
		return { i_lhs,i_rhs };
	}
}
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const integer_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
prod_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const integer_symbolic_literal& i_rhs)
{
	return i_lhs * rational_symbolic_literal{ 1,i_rhs.number() };
}
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return { integer_symbolic_literal{i_lhs.numerator()}, i_lhs.denominator() * i_rhs };
}
sum_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return rational_symbolic_literal{ i_rhs.denominator(),i_rhs.numerator()} * i_lhs;
}
div_symbolic_literal operator/(const rational_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { integer_symbolic_literal{i_lhs.numerator()}, i_lhs.denominator() * i_rhs };
}
prod_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const rational_symbolic_literal& i_rhs)
{
	return rational_symbolic_literal{ i_rhs.denominator(),i_rhs.numerator() } *i_lhs;
}
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const root_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const root_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const log_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const log_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const sum_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const sum_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}
div_symbolic_literal operator/(const prod_symbolic_literal& i_lhs,const prod_symbolic_literal& i_rhs)
{
	return { i_lhs,i_rhs };
}

}