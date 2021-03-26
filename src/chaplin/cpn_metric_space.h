#pragma once

#include "cpn_type_concepts.h"
#include "cpn_algebraic_concepts.h"
#include "cpn_complete_space.h"
#include "ddk_iterable_algorithm.h"

namespace cpn
{

template<coordinate_type T>
struct euclidean_metric
{
	static_assert(complete_space_type<typename T::place_type>, "You shall define metric operation over complete spaces.");

	inline double operator()(const T& i_lhs,const T& i_rhs) const
	{
		return ddk::sqrt <<= ddk::sum <<= ddk::iter::pow(ddk::arg_0,2) <<= ddk::iter::subs(i_lhs,i_rhs);
	}
};

template<typename T>
struct abs_value_metric
{
	//static_assert(substractive_type<T>,"You shall define metric operation over substractive types.");

	inline double operator()(const T& i_lhs,const T& i_rhs) const
	{
		return std::abs(i_lhs - i_rhs);
	}
};

template<typename T, typename Metric>
struct point_convergence_from_metric
{
public:
	constexpr point_convergence_from_metric(const double& i_epsilon)
	: m_epsilon(i_epsilon)
	{
	}
	inline bool operator()(const T& i_lhs, const T& i_rhs) const
	{
		static const Metric s_metric;

		return s_metric(i_lhs - i_rhs) < m_epsilon;
	}

private:
	const double m_epsilon;
};

template<typename T, typename Metric>
struct metric_space_operation : point_convergence_operation<T,point_convergence_from_metric<T,Metric>>
{
	PUBLISH_OPERATION_PROPERTIES(metric_space_operation,metric_operation);

	friend inline double distance(const T& i_lhs,const T& i_rhs)
	{
		static const Metric s_metric;

		return s_metric(i_lhs - i_rhs);
	}
};

template<typename T, typename Metric>
using metric_space = typename T::template equip_with<metric_space_operation<T,Metric>>;

}