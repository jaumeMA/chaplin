#pragma once

#include "ddk_visitable_type.h"
#include "ddk_inherited_value.h"
#include "ddk_distribute_from_this.h"

namespace cpn
{

class symbolic_number_interface : public ddk::distribute_from_this<symbolic_number_interface>
{
    friend inline auto share(symbolic_number_interface& i_value)
    {
        return i_value.ref_from_this();
    }
    friend inline auto share(const symbolic_number_interface& i_value)
    {
        return i_value.ref_from_this();
    }

public:
	virtual ~symbolic_number_interface() = default;

	virtual double resolve(unsigned char i_accuracy) const = 0;
};

using inherited_symbolic_number = ddk::inherited_value<const symbolic_number_interface>;

}
