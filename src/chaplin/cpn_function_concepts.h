#pragma once

#define IS_INSTANTIABLE(_TYPE) \
	decltype(_TYPE::template instance<int,int>())
#define IS_INSTANTIABLE_BY(_TYPE,...) \
	decltype(ddk::mpl::remove_qualifiers<_TYPE>::template instance<__VA_ARGS__>())