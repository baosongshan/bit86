#pragma once

#include"stl_alloc.h"
#include"stl_uninitialized.h"

template<class T, class Alloc=alloc>
class vector
{
public:
	typedef T         value_type;
	typedef T*        pointer;
	typedef const T*  const_pointer;
	typedef T&        reference;
	typedef const T&  const_reference;
	typedef size_t    size_type;
public:
	typedef T* iterator;
public:
	vector() : start(0),finish(0),end_of_storage(0)
	{}
	vector(size_type n, const T &value=T())
	{
		fill_initialize(n, value);
	}
private:
	void fill_initialize(size_type n, const T &value)
	{
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
	iterator allocate_and_fill(size_type n, const T &x)
	{
		iterator result = data_allocator::allocate(n);
		Uninitialized_fill_n(result, n, x);
		return result;
	}
private:
	iterator start;
	iterator finish;
	iterator end_of_storage;
	//vectorø’º‰≈‰÷√∆˜
	typedef simple_alloc<value_type, Alloc> data_allocator; 
};
