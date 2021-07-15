#include<iostream>
#include<vector>
#include<list>
#include<forward_list>
using namespace std;

void main()
{
	forward_list<int> mylist;
	for(int i=1; i<=10; ++i)
		mylist.push_front(i);

	forward_list<int>::iterator it= mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

}

/*
template<class Type>
class ListItem
{
public:
	Type value()
	{
		return _value;
	}
	ListItem* next()
	{
		return _next;
	}
private:
	Type _value;
	ListItem *_next;
};

template<class Type>
class List
{
private:
	ListItem<Type> *_front;
	ListItem<Type> *_end;
	size_t          _size;
};

////////////////////////////////////////////////////
template<class Type>
class ListIterator
{
public:
	ListIterator(Type *p=0) : _ptr(p)
	{}
private:
	Type *_ptr;
};

/*
void main()
{
	vector<int> iv = {3,9,8,5,0,1,2,4,6};
	auto it = find(iv.begin(),iv.end(), 2);

	list<int> lt = {3,9,8,5,0,1,2,4,6};
	auto it1 = find(lt.begin(),lt.end(), 2);
}

/*
void Out_Of_Memory()
{
	cout<<"Out_Of_Memory."<<endl;
	//exit(1);
}


void main()
{
	//int *ptr = (int*)malloc(sizeof(int) * 536870911);
	try
	{
		set_new_handler(Out_Of_Memory);
		int *ptr = new int[536870911];
	}
	catch(bad_alloc & e)
	{
		cout<<e.what()<<endl;
	}
	
	cout<<"OK"<<endl;
}
*/