#pragma once

#include "ddk_visitable_type_interface.h"
#include "ddk_inherited_value.h"
#include "ddk_shared_from_this.h"

namespace cpn
{

class symbolic_number_interface : public ddk::share_from_this<symbolic_number_interface>
{
	DECLARE_TYPE_VISITABLE_BASE(symbolic_number_interface);

public:
	typedef ddk::inherited_value<symbolic_number_interface> inherited_symbolic_number;

	virtual ~symbolic_number_interface() = default;

	virtual double resolve(unsigned char i_accuracy) const = 0;
};

using inherited_symbolic_number = ddk::inherited_value<symbolic_number_interface>;

}