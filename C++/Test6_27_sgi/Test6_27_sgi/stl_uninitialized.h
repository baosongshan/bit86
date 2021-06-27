#pragma once

#include"type_traits.h"
#include"stl_itertor.h"
#include"stl_construct.h"

template<class ForwardIterator, class Size, class T>
ForwardIterator __Uninitizlized_fill_n_aux(ForwardIterator first,
										   Size n,
										   const T &x,
										   __true_type)
{
	return fill_n(first, n, x);
}

template<class ForwardIterator, class Size, class T>
ForwardIterator __Uninitizlized_fill_n_aux(ForwardIterator first,
										   Size n,
										   const T &x,
										   __false_type)
{
	ForwardIterator cur = first;
	for(; n>0; --n, ++cur)
		construct(& *cur, x);
	return cur;
}

template<class ForwardIterator, class Size, class T, class T1>
ForwardIterator __Uninitialized_fill_n(ForwardIterator first,
									   Size n,
									   const T &x,
									   T1 *)
{
	typedef typename __type_traits<T1>::is_POD_type is_POD;
	return __Uninitizlized_fill_n_aux(first, n, x, is_POD());
}

template<class ForwardIterator, class Size, class T>
ForwardIterator Uninitialized_fill_n(ForwardIterator first, 
									 Size n,
									 const T&x)
{
	return __Uninitialized_fill_n(first, n, x, value_type(first));
}