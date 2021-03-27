#include<iostream>
#include"mymemory.h"
using namespace std;

class String
{
public:
	String(const char *str="")
	{
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
	String(const String &s)
	{
		m_data = new char[strlen(s.m_data)+1];
		strcpy(m_data, s.m_data);
	}
	~String()
	{
		delete []m_data;
	}
private:
	char *m_data;
};

namespace bit
{
	template<class _Ty, class _A=my_allocator<_Ty>>
	class list
	{
	public:
		//类型的萃取
		typedef size_t  size_type;
		typedef _Ty     value_type;
		typedef _Ty*    pointer_type;
		typedef _Ty&    referenct_type;
	public:
		struct _Node;
		typedef _Node*  _Nodeptr;
		struct _Node
		{
			_Nodeptr _Next;
			_Nodeptr _Prev;
			_Ty      _Value;
		};
		struct _Acc
		{
			typedef _Node*& _Nodepref;
			typedef _Ty&    _Vref;
			static _Nodepref _Next(_Nodeptr _P)
		    {return _P->_Next;}
			static _Nodepref _Prev(_Nodeptr _P)
			{return _P->_Prev;}
			static _Vref _Value(_Nodeptr _P)
			{return _P->_Value;}
		};
	public:
		class iterator
		{
		public:
			iterator()
			{}
			iterator(_Nodeptr _P) : _Ptr(_P)
			{}
		public:
			_Ty& operator*()
			{
				return _Ptr->_Value;
			}
			iterator& operator++()
			{
				_Ptr = _Ptr->_Next;
				return *this;
			}
			iterator& operator--()
			{
				_Ptr = _Ptr->_Prev;
				return *this;
			}
			bool operator!=(const iterator &it)
			{
				return _Ptr != it._Ptr;
			}
			bool operator==(const iterator &it)
			{
				return _Ptr == it._Ptr;
			}
			_Nodeptr _Mynode() const
			{
				return (_Ptr); 
			}
		protected:
			_Nodeptr _Ptr;
		};
	public:
		explicit list():_Head(_Buynode()),_Size(0)
		{}
		explicit list(size_type _N, const _Ty& _V = _Ty())
			:_Head(_Buynode()), _Size(0)
		{
			insert(begin(), _N, _V);
		}
	public:
		iterator begin()
		{
			return iterator(_Head->_Next);
		}
		iterator end()
		{
			return iterator(_Head);
		}
	public:
		void push_back(const _Ty &x)
		{insert(end(), x);}
		void push_front(const _Ty &x)
		{insert(begin(), x);}
	public:
		iterator insert(iterator _P, const _Ty& _X = _Ty())
		{
			_Nodeptr _S = _P._Mynode();
			_Acc::_Prev(_S) = _Buynode(_S, _Acc::_Prev(_S));
			_S = _Acc::_Prev(_S);
			_Acc::_Next(_Acc::_Prev(_S)) = _S;
			//_S->_Value = _X;
			allocator.construct(&_Acc::_Value(_S), _X);
			++_Size;
			return (iterator(_S));
		}
		void insert(iterator _P, size_type _M, const _Ty& _X)
		{
			for (; 0 < _M; --_M)
				insert(_P, _X); 
		}
		void insert(iterator _P, const _Ty *_F, const _Ty *_L)
		{
			for (; _F != _L; ++_F)
				insert(_P, *_F); 
		}
	protected:
		                           //后继参数        前驱参数
		_Nodeptr _Buynode(_Nodeptr _Narg=0, _Nodeptr _Parg=0)
		{
			//_Node *_S = (_Node*)malloc(sizeof(_Node));
			_Node *_S = (_Nodeptr)allocator._Charalloc(sizeof(_Node));
			_Acc::_Next(_S) = _Narg != 0 ? _Narg : _S;
			_Acc::_Prev(_S) = _Parg != 0 ? _Parg : _S;

			return _S;
		}
	private:
		_A        allocator; //空间配置器对象
		_Nodeptr  _Head;
		size_type _Size;
	};
};

using namespace bit;
void main()
{
	list<String> mylist;
	String s[] = {"abc", "xyz", "hjk"};
	mylist.push_back(s[0]);
	mylist.push_back(s[1]);
	mylist.push_back(s[2]);
}

/*
void main()
{
	list<int> mylist(10,2);
	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
}

/*
void main()
{
	int ar[] = {12,23,34,45,56,67,78,89};
	int n = sizeof(ar)/sizeof(ar[0]);

	list<int> mylist;
	mylist.push_back(1);
	mylist.push_back(2);
	mylist.push_back(3);
	mylist.push_back(4);
	mylist.push_front(5);

	//5 1 2 3 4
	list<int>::iterator pos = mylist.begin();
	++pos;
	++pos;
	//mylist.insert(pos, 3,100);
	mylist.insert(pos, ar, ar+n);

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
}
*/