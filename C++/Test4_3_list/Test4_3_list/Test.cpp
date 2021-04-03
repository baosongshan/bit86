#include<iostream>
#include<list>
#include<functional>
using namespace std;

namespace bit
{
	template<class _Ty>
	class list;

	template<class _Ty>
	class List_iterator;

	template<class _Ty>
	class Node
	{
		friend class list<_Ty>;
		friend class List_iterator<_Ty>;
	public:
		Node():_val(_Ty()),_next(nullptr),_prev(nullptr)
		{}
		Node(const _Ty &val, Node*next=nullptr,Node *prev=nullptr)
			:_val(val),_next(next),_prev(prev)
		{}
		~Node()
		{}
	private:
		Node *_next;
		Node *_prev;
		_Ty _val;
	};

	template<class _Ty>
	class List_iterator
	{
		typedef List_iterator<_Ty> self;
 	public:
		List_iterator(Node<_Ty> *_P):_Ptr(_P)
		{}
	public:
		_Ty& operator*()
		{
			return _Ptr->_val;
		}
		self& operator++()
		{
			_Ptr = _Ptr->_next;
			return *this;
		}
		self operator++(int)
		{
			self tmp(*this);
			++*this;
			return tmp;
		}
		self& operator--()
		{
			_Ptr = _Ptr->_prev;
			return *this;
		}
		bool operator!=(const self &it)
		{
			return (_Ptr != it._Ptr);
		}
		Node<_Ty>* _Mynode()
		{
			return _Ptr;
		}
	private:
		Node<_Ty> *_Ptr;
	};

	template<class _Ty>
	class list
	{
	public:
		typedef List_iterator<_Ty> iterator;
		typedef iterator _It;
	public:
		list():_Size(0)
		{
			CreateHead();
		}
		list(int n, const _Ty& value = T())
		{
			CreateHead();
			while(--n)
			{
				insert(begin(), value);
			}
		}
		list(_It _first, _It _last)
		{
			CreateHead();
			while(_first != _last)
			{
				push_back(*_first);
				++_first;
			}
		}
		list(list &lt)
		{
			CreateHead();
			list<_Ty> tmp(lt.begin(), lt.end());
			swap(_Head, tmp._Head);
			_Size = lt.size();
		}

		//a = b;
		list<_Ty>& operator=(list<_Ty> &lt)
		{
			if(this != &lt)
			{
				list<_Ty> tmp(lt.begin(), lt.end());
				swap(_Head, tmp._Head);
			}
			return *this;
		}

		~list()
		{
			clear();
			delete _Head;
			_Head = nullptr;
		}
	public:
		iterator begin()
		{
			return iterator(_Head->_next);
		}
		iterator end()
		{
			return iterator(_Head);
		}
	public:
		size_t size()const
		{
			return _Size;
		}
		bool empty()const
		{
			return size() == 0;
		}
		_Ty& front()
		{
			return *begin();
		}
		const _Ty& front()const
		{
			return *begin();
		}
		_Ty& back()
		{
			return *--end();
		}
		const _Ty& back()const
		{
			return *--end();
		}
		void push_back(const _Ty &x)
		{
			insert(end(), x);
		}
		void clear()
		{
			erase(begin(), end());
		}
		//void swap(list &lt);
	public:
		iterator insert(iterator _P, const _Ty &x)
		{
			Node<_Ty> *_S = new Node<_Ty>(x);
			Node<_Ty> *cur = _P._Mynode();
			_S->_next = cur;
			_S->_prev = cur->_prev;
			_S->_next->_prev = _S;
			_S->_prev->_next = _S;
			_Size++;
			return iterator(_S);
		}

		iterator erase(iterator _P)
		{
			Node<_Ty> *cur = _P._Mynode();
			Node<_Ty> *next_node = cur->_next;
			cur->_next->_prev = cur->_prev;
			cur->_prev->_next = cur->_next;
			delete cur;
			_Size--;
			return iterator(next_node);
		}
		iterator erase(iterator _first, iterator _last)
		{
			while(_first != _last)
			{
				_first = erase(_first);
			}
			return iterator(_last);
		}
	protected:
		void CreateHead()
		{
			_Head = new Node<_Ty>;
			_Head->_next = _Head;
			_Head->_prev = _Head;
		}
	private:
		Node<_Ty> *_Head;
		size_t     _Size;
	};
};

void main()
{
	bit::list<int> mylist(10, 2);
	bit::list<int> youlist;   //list<int> youlist = mylist

	youlist = mylist;

	bit::list<int>::iterator it = youlist.begin();
	while(it != youlist.end())
	{
		cout<<*it<<" ";
		++it; //it++
	}
	cout<<endl;

}

/*
void main()
{
	bit::list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	mylist.push_back(5);

	bit::list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<" ";
		++it; //it++
	}
	cout<<endl;

	//mylist.erase(mylist.begin());
	mylist.clear();

	it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<" ";
		++it; //it++
	}
	cout<<endl;

}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> list1(ar, ar+n);

	auto it = list1.begin();
	while(it != list1.end())
	{
		it = list1.erase(it);
		//++it;
	}

	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	list<int> list1(ar, ar+n);

	auto it = list1.begin();
	auto it1 = find(list1.begin(), list1.end(), 5);
	list1.erase(it);
	++it1;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,5,5,5,5,5,5,6,7,8,9,10,4,4,3,2,5};
	int n = sizeof(ar) / sizeof(ar[0]);
	list<int> list1(ar, ar+n);
	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

	//list1.remove(6);
	//list1.unique();
	//list1.sort();
	list1.sort(greater<int>());

	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

	list1.reverse();

	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	int br[10] = {12,23,34,45,56,67,78,89,90,100};
	list<int> list1(ar, ar+10);
	list<int> list2(br, br+10);

	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

	list1.splice(list1.end(), list2);
	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

	for(auto & e : list2)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	list<int> list1(ar, ar+10);
	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

	list1.assign(5, 0);
	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	list<int> list1(ar, ar+10);
	cout<<"size = "<<list1.size()<<endl;
	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;
	list1.resize(5, 13);
	cout<<"size = "<<list1.size()<<endl;
	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	int br[10] = {12,23,34,45,56,67,78,89,90,100};
	list<int> list1(ar, ar+10);
	list<int> list2(br, br+10);

	cout<<"empty = "<<list1.empty()<<endl;
	cout<<"size = "<<list1.size()<<endl;
	cout<<"front = "<<list1.front()<<endl;
	cout<<"back = "<<list1.back()<<endl;

	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

	//auto pos = find(list1.begin(), list1.end(), 5);
	//list1.insert(pos, 100);
	//list1.insert(pos, 10, 2);
	//list1.insert(pos, list2.begin(), list2.end());
	//list1.insert(pos, br, br+10);
	//list1.erase(list1.begin(), list1.end());

	//list1.swap(list2);
	list1.clear();

	for(auto & e : list1)
		cout<<e<<" ";
	cout<<endl;

}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	const list<int> list1(ar, ar+10);

	list<int>::const_iterator it = list1.begin();
	while(it != list1.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	list<int>::const_reverse_iterator rit = list1.rbegin();
	while(rit != list1.rend())
	{
		cout<<*rit<<" ";
		++rit;
	}
	cout<<endl;
}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	list<int> list1(ar, ar+10);

	list<int>::iterator it = list1.begin();
	while(it != list1.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	list<int>::reverse_iterator rit = list1.rbegin();
	while(rit != list1.rend())
	{
		cout<<*rit<<" ";
		++rit;
	}
	cout<<endl;
}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	list<int> list1(ar, ar+10);

	for(auto & e : list1)  //
		cout<<e<<" ";
	cout<<endl;

	list<int>::iterator it = list1.begin();
	while(it != list1.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	auto it1 = list1.begin();
	cout<<typeid(it1).name()<<endl;
	while(it1 != list1.end())
	{
		cout<<*it1<<" ";
		++it1;
	}
	cout<<endl;
}

/*
void main()
{
	int ar[10] = {1,2,3,4,5,6,7,8,9,10};

	list<int> list1;
	list<int> list2(10);
	list<int> list3(10, 5);
	list<int> list4(ar, ar+10);
	list<int> list5(list4);
	list<int> list6(list5.begin(), list5.end());

	for(auto & e : list6)
		cout<<e<<" ";
	cout<<endl;
}
*/