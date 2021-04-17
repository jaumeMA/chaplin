#pragma once

namespace ddk
{

class to_any_value
{
public:
	template<typename T>
	operator T() const
	{
		return *const_cast<T*>(reinterpret_cast<const T*>(this));
	}
};

}