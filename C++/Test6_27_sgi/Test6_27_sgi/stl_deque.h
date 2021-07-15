#pragma once


#include"stl_alloc.h"

template <class T, class Ref, class Ptr>
struct __deque_iterator
{
	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef T** map_pointer;

	typedef __deque_iterator self;

	T* cur;
	T* first;
	T* last;
	map_pointer node; //T **node;
};


template <class T, class Alloc = alloc, size_t BufSiz = 0> 
class deque 
{
public:                         // Basic types
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
public:
	typedef __deque_iterator<T, T&, T*> iterator;
protected:                      
	typedef pointer* map_pointer;  //ÖÐ¿ØÆ÷
	typedef simple_alloc<value_type, Alloc> data_allocator;
	typedef simple_alloc<pointer, Alloc>    map_allocator;

public:
	deque()	: start(), finish(), map(0), map_size(0)
	{
		create_map_and_nodes(0);
	}

protected:                      // Data members
	iterator start;
	iterator finish;
	map_pointer map;
	size_type map_size;
};
