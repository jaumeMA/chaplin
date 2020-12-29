#pragma once

#if defined(WIN32)

#define _ENABLE_EXTENDED_ALIGNED_STORAGE

#endif

#include "ddk_tuple.h"
#include "ddk_iterable_impl_interface.h"
#include "ddk_iterable_valued_traits.h"

namespace ddk
{
namespace detail
{

template<typename ... Iterables>
class intersection_iterable_impl : public iterable_impl_interface<intersection_iterable_base_traits<typename Iterables::traits ...>>
{
    static const size_t s_num_iterables = tuple<Iterables...>::size();
    typedef iterable_impl_interface<intersection_iterable_base_traits<typename Iterables::traits ...>> base_t;
    using typename base_t::traits;
    typedef typename intersection_iterable_traits<typename Iterables::traits ...>::iterable_value iterable_value;
    typedef typename intersection_iterable_traits<typename Iterables::traits ...>::iterable_const_value iterable_const_value;
	template<size_t Index, typename ... IIterables>
	friend typename mpl::nth_type_of<Index, IIterables...>::type::reference intersection_navigate(intersection_iterable_impl<IIterables...>* i_iterable, const iter::shift_action& i_initialAction);
	template<size_t Index, typename ... IIterables>
	friend typename mpl::nth_type_of<Index, IIterables...>::type::const_reference const_intersection_navigate(const intersection_iterable_impl<IIterables...>* i_iterable, const iter::shift_action& i_initialAction);

public:
    using typename base_t::reference;
    using typename base_t::const_reference;
    using typename base_t::action;

    intersection_iterable_impl(const Iterables& ... i_iterables);
    intersection_iterable_impl(const tuple<Iterables...>& i_tupleIterable);
	intersection_iterable_impl(const intersection_iterable_impl&) = default;
	intersection_iterable_impl(intersection_iterable_impl&&) = default;

    const tuple<Iterables...>& get_iterables() const;
    tuple<Iterables...>& get_iterables();

private:
    void iterate_impl(const function<action(reference)>& i_try, const iter::shift_action& i_initialAction, iter::action_state_lent_ptr i_actionStatePtr) override;
    void iterate_impl(const function<action(const_reference)>& i_try, const iter::shift_action& i_initialAction, iter::action_state_lent_ptr i_actionStatePtr) const override;
    size_t size() const override;
    bool empty() const override;

    template<size_t ... Indexs>
    inline void iterate_impl(const mpl::sequence<Indexs...>&, const function<action(reference)>& i_try, const iter::shift_action& i_initialAction, iter::action_state_lent_ptr i_actionStatePtr);
    template<size_t ... Indexs>
    inline void iterate_impl(const mpl::sequence<Indexs...>&, const function<action(const_reference)>& i_try, const iter::shift_action& i_initialAction, iter::action_state_lent_ptr i_actionStatePtr) const;

    tuple<Iterables...> m_iterables;
};

}
}

#include "ddk_intersection_iterable_impl.inl"