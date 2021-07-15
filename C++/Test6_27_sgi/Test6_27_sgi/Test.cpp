#include<iostream>
//#include<list>
//#include"stl_alloc.h"
#include"stl_vector.h"
#include"stl_list.h"
#include"stl_deque.h"
using namespace std;

void main()
{
	deque<int> de;
}

/*
void main()
{
	//vector<int> iv(10);
	list<int> mylist;
	for(int i=1; i<=10; ++i)
		mylist.push_back(i);

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
class Test
{
public:
	Test(int d=0) : m_data(d)
	{}
	Test(const Test &t)
	{
		m_data = t.m_data;
	}
	~Test()
	{
		cout<<"Free Obj."<<endl;
	}
private:
	int m_data;
};

void main()
{
	vector<Test> iv(10);
}

/*
void main()
{
	int *ptr = (int*)__default_alloc_template<0,0>::allocate(sizeof(char));
	int *ptr1 = (int*)__default_alloc_template<0,0>::allocate(200);
	int *ptr2 = (int*)__default_alloc_template<0,0>::allocate(sizeof(int)*32);
	int *ptr3 = (int*)__default_alloc_template<0,0>::allocate(sizeof(int)*10);
}

/*
void Out_Of_Memory()
{
	cout<<"Out_Of_Memory."<<endl;
}

void main()
{
	__malloc_alloc_template<0>::set_malloc_handler(Out_Of_Memory);
	int *ptr = (int*)__malloc_alloc_template<0>::allocate(sizeof(int)*536870911);
}

/*
void main()
{
	//int *ptr = (int*)__malloc_alloc_template<0>::allocate(sizeof(int));
	try
	{
		int *ptr = (int*)__malloc_alloc_template<0>::allocate(sizeof(int)*536870911);
	}
	catch(bad_alloc & e)
	{
		cout<<e.what()<<endl;
	}
}


/*
template<class T>
T* _allocate(size_t size, T*)
{
	//set_new_handler(0);
	T *tmp = (T*)::operator new(size * sizeof(T));
	if(tmp == 0)
	{
		cout<<"Out Of Memory."<<endl;
		exit(1);
	}
	return tmp;
}

template<class T>
void _deallocate(T *buffer)
{
	::operator delete(buffer);
}

template<class T1, class T2>
void _construct(T1 *p, const T2 &value)
{
	new(p) T1(value); //∂®Œªnew
}
template<class T>
void _destroy(T *ptr)
{
	ptr->~T();
}

template<class T>
class myallocator
{
public:
	typedef T         value_type;
	typedef T*        pointer;
	typedef const T*  const_pointer;
	typedef T&        reference;
	typedef const T&  const_reference;
	typedef size_t    size_type;
	typedef ptrdiff_t difference_type;
public:
	//…Í«Îø’º‰
	pointer allocate(size_t n, const void *hint=0)
	{
		return _allocate(n, (pointer)0);
	}
	void    deallocate(pointer p, size_type n)
	{
		_deallocate(p);
	}
	void    construct(pointer p, const T &value)
	{
		_construct(p, value);
	}
	void    destroy(pointer p)
	{
		_destroy(p);
	}
};

void main()
{
	list<int> mylist;
}
*/