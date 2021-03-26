#pragma once

#include "cpn_algebraic_concepts.h"

namespace cpn
{

template<typename T, typename Criteria>
struct point_convergence_operation
{
	//static_assert(substractive_type<T>, "You can only define complete types upon substractive underlying types.");

	PUBLISH_OPERATION_PROPERTIES(point_convergence_operation,point_conv_operation);

	friend inline bool has_converged(const T& i_lhs, const T& i_rhs, const double i_epsilon)
	{
		const Criteria s_criteria(i_epsilon);

		return s_criteria(i_lhs,i_rhs);
	}
};

template<typename T, typename Criteria>
using complete_space = typename T::template equip_with<point_convergence_operation<T,Criteria>>;

}