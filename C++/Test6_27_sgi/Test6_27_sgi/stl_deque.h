#pragma once

#include<cmath>
#include"stl_alloc.h"
#include"stl_construct.h"

inline size_t __deque_buf_size(size_t n, size_t sz)
{
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

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

	__deque_iterator() : cur(0), first(0), last(0), node(0) 
	{}

	static size_t buffer_size() 
	{
		return __deque_buf_size(0, sizeof(T));
	}
	void set_node(map_pointer new_node)
	{
		node = new_node;
		first = *new_node;
		last = first + difference_type(buffer_size());
	}

	reference operator*() const 
	{
		return *cur; 
	}
	self& operator++() 
	{
		++cur;
		if (cur == last)
		{
			this->set_node(node + 1);
			cur = first;
		}
		return *this;
  }

	bool operator==(const self& x) const
	{
		return cur == x.cur; 
	}
	bool operator!=(const self& x) const 
	{
		return !(*this == x);
	}

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

	void push_front(const value_type& t)
	{
		if (start.cur != start.first)
		{
			construct(start.cur - 1, t);
			--start.cur;
		}
		else
			push_front_aux(t);
	}

	void push_back(const value_type& t) 
	{
		if (finish.cur != finish.last - 1)
		{
			construct(finish.cur, t);
			++finish.cur;
		}
		else
			push_back_aux(t);
  }
public:
	iterator begin()
	{
		return start;
	}
	iterator end() 
	{
		return finish; 
	}
protected:
	static size_type buffer_size() 
	{
		return __deque_buf_size(BufSiz, sizeof(value_type));
	}

	static size_type initial_map_size() 
	{
		return 8; 
	}

	pointer allocate_node() 
	{
		return data_allocator::allocate(buffer_size()); 
	}
	
	void create_map_and_nodes(size_type num_elements)
	{
		size_type num_nodes = num_elements / buffer_size() + 1;

		map_size = max(initial_map_size(), num_nodes + 2);
		map = map_allocator::allocate(map_size);

		map_pointer nstart = map + (map_size - num_nodes) / 2;
		map_pointer nfinish = nstart + num_nodes - 1;

		map_pointer cur;
		
		for (cur = nstart; cur <= nfinish; ++cur)
			*cur = allocate_node();

		start.set_node(nstart);
		finish.set_node(nfinish);
		start.cur = start.first;
		finish.cur = finish.first + num_elements % buffer_size();
	}

	void reallocate_map(size_type nodes_to_add, bool add_at_front)
	{
		size_type old_num_nodes = finish.node - start.node + 1;
		size_type new_num_nodes = old_num_nodes + nodes_to_add;

		map_pointer new_nstart;
		if (map_size > 2 * new_num_nodes) 
		{
			new_nstart = map + (map_size - new_num_nodes) / 2
				+ (add_at_front ? nodes_to_add : 0);
			if (new_nstart < start.node)
				copy(start.node, finish.node + 1, new_nstart);
			else
				copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
		}
		else 
		{
			size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;

			map_pointer new_map = map_allocator::allocate(new_map_size);
			new_nstart = new_map + (new_map_size - new_num_nodes) / 2
				+ (add_at_front ? nodes_to_add : 0);
			copy(start.node, finish.node + 1, new_nstart);
			map_allocator::deallocate(map, map_size);

			map = new_map;
			map_size = new_map_size;
		}

		start.set_node(new_nstart);
		finish.set_node(new_nstart + old_num_nodes - 1);
	}

	void reserve_map_at_back(size_type nodes_to_add = 1)
	{
		if (nodes_to_add + 1 > map_size - (finish.node - map))
			reallocate_map(nodes_to_add, false);
	}
	void push_back_aux(const value_type& t)
	{
		value_type t_copy = t;
		reserve_map_at_back();
		*(finish.node + 1) = allocate_node();

		construct(finish.cur, t_copy);
		finish.set_node(finish.node + 1);
		finish.cur = finish.first;
	}


	void reserve_map_at_front (size_type nodes_to_add = 1) 
	{
		if (nodes_to_add > start.node - map)
			reallocate_map(nodes_to_add, true);
	}
	void push_front_aux(const value_type& t)
	{
		value_type t_copy = t;
		reserve_map_at_front();
		*(start.node - 1) = allocate_node();

		start.set_node(start.node - 1);
		start.cur = start.last - 1;
		construct(start.cur, t_copy);

	}

protected:                      // Data members
	iterator start;
	iterator finish;
	map_pointer map;   //T ** map
	size_type map_size;
};
