#pragma once

#include"stl_alloc.h"

//Ë«ÏòÑ­»·Á´±í

template <class T>
struct __list_node
{
	typedef void* void_pointer;
	void_pointer next;
	void_pointer prev;
	T data;
};

/////////////////////////////////////////////////////////////////
template<class T, class Ref, class Ptr>
struct __list_iterator 
{
	typedef __list_iterator<T, T&, T*>   iterator;
	typedef __list_iterator<T, Ref, Ptr>  self;

	typedef T value_type;
	typedef Ptr pointer;
	typedef Ref reference;

	typedef __list_node<T>* link_type;

	link_type node; //list_node *node;

	__list_iterator(link_type x) : node(x) {}
	__list_iterator() {}

	bool operator==(const self& x) const 
	{
		return node == x.node; 
	}
    bool operator!=(const self& x) const 
	{ 
		return node != x.node; 
	}

	reference operator*() const 
	{
		return (*node).data;
	}
	self& operator++()
	{
		node = (link_type)((*node).next);
		return *this;
	}
};

template <class T, class Alloc = alloc>
class list 
{
private:
	typedef void* void_pointer;
	typedef __list_node<T> list_node;
	typedef simple_alloc<list_node, Alloc> list_node_allocator;
public:
	typedef T value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef list_node* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
public:
	typedef __list_iterator<T, T&, T*> iterator;
public:
	list() 
	{
		empty_initialize();
	}
public:
	iterator begin()
	{
		return (link_type)((*node).next);
	}
	iterator end()
	{
		return node;
	}
public:
	 void push_back(const T& x) 
	 {
		 insert(end(), x);
	 }
public:
	iterator insert(iterator position, const T& x) 
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}
protected:
	link_type get_node()
	{
		return list_node_allocator::allocate();
	}
	link_type create_node(const T& x)
	{
		link_type p = get_node();
		construct(&p->data, x);
		return p;
	}
	void empty_initialize()
	{
		node = get_node();
		node->next = node;
		node->prev = node;
	}

protected:
	link_type node;  //list_node *node;
};