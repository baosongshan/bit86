#include<iostream>
#include<memory>
#include<vld.h>
#include<string>
#include<thread>
#include<mutex>
//#include<boost/smart_ptr.hpp>
using namespace std;
//using namespace boost;

//删除器
void FreeSpace(void *ptr)
{
	cout<<"Free"<<endl;
	free(ptr);  //delete []  close(socket)
}

void main()
{
	int *p = (int *)malloc(sizeof(int)); //malloc  new []
	shared_ptr<int> ps(p, FreeSpace); //delete
}

/*
struct ListNode
{
	int _data;
	weak_ptr<ListNode> _prev;
	weak_ptr<ListNode> _next;
	~ListNode(){ cout << "~ListNode()" << endl; }
};

int main()
{
	shared_ptr<ListNode> node1(new ListNode);
	shared_ptr<ListNode> node2(new ListNode);

	cout << node1.use_count() << endl;  //1
	cout << node2.use_count() << endl;  //2

	node1->_next = node2; //形成链表
	node2->_prev = node1;
	cout << node1.use_count() << endl;
	cout << node2.use_count() << endl;
	return 0;
}

/*
struct ListNode
{
	int _data;
	shared_ptr<ListNode> _prev;
	shared_ptr<ListNode> _next;
	~ListNode(){ cout << "~ListNode()" << endl; }
};

int main()
{
	shared_ptr<ListNode> node1(new ListNode);
	shared_ptr<ListNode> node2(new ListNode);

	cout << node1.use_count() << endl;  //1
	cout << node2.use_count() << endl;  //2

	node1->_next = node2;
	node2->_prev = node1;
	//cout << node1.use_count() << endl;
	//cout << node2.use_count() << endl;
	return 0;
}


/*
template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		: _ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}
	~SharedPtr() 
	{
		Release();
	}
	SharedPtr(const SharedPtr<T>& sp)
		: _ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}

	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		if (_ptr != sp._ptr)
		{
			Release();
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;
			AddRefCount();
		}
		return *this;
	}

	T& operator*() { return *_ptr; }
	T* operator->() { return _ptr; }
	int UseCount() { return *_pRefCount; }
	T* Get() { return _ptr; }
	void AddRefCount()
	{
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool deleteflag = false;
		_pMutex->lock();
		if (--(*_pRefCount) == 0)
		{
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		_pMutex->unlock();
		if(deleteflag)
			delete _pMutex;

	}
private:
	int* _pRefCount; // 引用计数
	T  * _ptr;       // 指向管理资源的指针
	mutex *_pMutex;
};


class Date
{
public:
	Date() { cout << "Date()" << endl; }
	~Date(){ cout << "~Date()" << endl; }
	size_t _year = 0;
	size_t _month = 0;
	size_t _day = 0;
};

mutex mt;
void SharePtrFunc(SharedPtr<Date>& sp, size_t n)
{
	cout << sp.Get() << endl;
	for (size_t i = 0; i < n; ++i)
	{
		SharedPtr<Date> copy(sp);
		mt.lock();
		copy->_year++;
		copy->_month++;
		copy->_day++;
		mt.unlock();
	}
}

int main()
{
	SharedPtr<Date> p(new Date);

	cout << p.Get() << endl;
	const size_t n = 10000000;

	thread t1(SharePtrFunc, p, n);
	thread t2(SharePtrFunc, p, n);

	t1.join();
	t2.join();
	cout << p->_year << endl;
	cout << p->_month << endl;
	cout << p->_day << endl;
	return 0;
}

/*
void main()
{
	int *ptr = new int(10);
	shared_ptr<int> sp(ptr);
	cout<<"use_count = "<<sp.use_count()<<endl;

	weak_ptr<int> wp = sp;
	cout<<"use_count = "<<sp.use_count()<<endl;
	//cout<<*wp<<endl;
}

/*


void main()
{
	int *ptr = new int(10);
	SharedPtr<int> sp(ptr);
	cout<<"use_count = "<<sp.UseCount()<<endl;
	SharedPtr<int> sp1 = sp;
	cout<<"use_count = "<<sp.UseCount()<<endl;
	{
		SharedPtr<int> sp2;
		sp2 = sp;
		cout<<"use_count = "<<sp.UseCount()<<endl;
	}
	cout<<"use_count = "<<sp.UseCount()<<endl;
}

/*
void main()
{
	//String
	int *ptr = new int(10);
	boost::shared_ptr<int> ps(ptr);
	cout<<*ps<<endl;
	cout<<"use count = "<<ps.use_count()<<endl;
	boost::shared_ptr<int> ps1 = ps;
	cout<<"use count = "<<ps.use_count()<<endl;

	{
		boost::shared_ptr<int> ps2 = ps;
		cout<<"use count = "<<ps.use_count()<<endl;
	}
	cout<<"use count = "<<ps.use_count()<<endl;
}

/*
void main()
{
	int *ptr = new int(10);
	unique_ptr<int> ps(ptr);
	cout<<*ps<<endl;;

	unique_ptr<int> ps1;
	//ps1 = ps;
}

/*
void main()
{
	int *ptr = new int[10]{1,2,3,4,5,6,7,8,9,10};
	scoped_array<int> ps(ptr);

	for(int i=0; i<10; ++i)
		cout<<ps[i]<<" ";
	cout<<endl;
}

/*
class Test
{
public:
	void fun()
	{
		cout<<"This is Test::fun()."<<endl;
	}
};

void main()
{
	int *ptr = new int(10);
	scoped_ptr<int> ps(ptr);
	cout<<*ps<<endl;;

	int *q = new int(20);
	ps.reset(q);

}


/*
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
	public:
		typedef auto_ptr<_Ty> _Myt;
	public:
		explicit auto_ptr(_Ty *_Ptr = 0) : _Myptr(_Ptr)
		{}
		auto_ptr(_Myt& _Right)	: _Myptr(_Right.release())
		{}
		_Myt& operator=(_Myt& _Right)
		{	
			reset(_Right.release());
			return (*this);
		}
		_Ty& operator*() const 
		{	
			return (*get());
		}
		_Ty *operator->() const 
		{
			return (get());
		}
		_Ty *get() const 
		{	
			return (_Myptr);
		}
		~auto_ptr()
		{			
			delete _Myptr;  //delete nullptr  delete []
		}
	public:
		_Ty *release()
		{	
			_Ty *_Tmp = _Myptr;
			_Myptr = 0;
			return (_Tmp);
		}
		void reset(_Ty *_Ptr = 0)
		{	
			if (_Ptr != _Myptr)
				delete _Myptr;
			_Myptr = _Ptr;
		}
	private:
		_Ty *_Myptr;
	};
};

void main()
{
	int *ptr = new int(10);
	bit::auto_ptr<int> pa(ptr);
}
/*
void main()
{
	int *ptr = new int(10);
	bit::auto_ptr<int> pa(ptr);
	cout<<*pa<<endl;

	//pa.reset(nullptr);
	int *tmp = pa.release();
	delete tmp;
	
	//int *q = new int(100);
	//pa.reset(q);
}


/*
void main()
{
	int *ptr = new int(10);
	auto_ptr<int> pa(ptr);
	cout<<*pa<<endl;
	auto_ptr<int> pa1 = pa;
	cout<<*pa<<endl;
}
/*
namespace bit
{
	template<class _Ty>
	class auto_ptr
	{
	public:
		auto_ptr(_Ty *_P = 0) : _Ptr(_P), _Owns(_P!=0)
		{}
		auto_ptr(const auto_ptr<_Ty>& _Y):_Owns(_Y._Owns), _Ptr(_Y.release())
		{}
		//pa1 = pa;
		auto_ptr& operator=(const auto_ptr<_Ty> &_Y)
		{
			if (this != &_Y)
			{
				if (_Ptr != _Y.get())
				{
					if (_Owns)
						delete _Ptr;
					_Owns = _Y._Owns;
				}
				else if (_Y._Owns)
					_Owns = true;

				_Ptr = _Y.release();
			}
			return (*this); 
		}
		_Ty& operator*()
		{
			return (*get()); //*_Ptr
		}
		_Ty* operator->()
		{
			return _Ptr;
		}
		_Ty *get() const
		{
			return (_Ptr);
		}
		//_Ty* release(const auto_ptr * const this)
	    _Ty* release()const
		{
			((auto_ptr<_Ty>*)this)->_Owns = false;
			return _Ptr;
		}
		~auto_ptr()
		{
			if(_Owns)
				delete _Ptr;
		}
	private:
		bool _Owns; //拥有权 true false
		_Ty *_Ptr;  //管理空间
	};
};

class Test
{
public:
	void fun()
	{
		cout<<"This is Test::fun()."<<endl;
	}
};

void main()
{
	int *ptr = new int(10);
	int *ptr1 = new int(100);
	bit::auto_ptr<int> pa = ptr;
	bit::auto_ptr<int> pa1 = ptr1; //

	bit::auto_ptr<int> pa2 = pa1;

	pa1 = pa; 
	cout<<*pa1<<endl;
	cout<<*pa<<endl;
}

/*
void main()
{
	int *ptr = new int(10);
	//*ptr = 100;
	bit::auto_ptr<int> pa = ptr;
	//bit::auto_ptr<int> pa1 = pa;
	cout<<*pa<<endl;
	*pa = 100;
	cout<<*pa<<endl;

	bit::auto_ptr<Test> pa1 = new Test;
	pa1->fun(); //pa1.operator->
}


/*
void main()
{
	int *ptr = new int(10);
	auto_ptr<int> pa(ptr);  //智能指针
	cout<<*pa<<endl;

	auto_ptr<int> pa1 = pa; //
	cout<<*pa1<<endl;
	cout<<*pa<<endl;
}

/*

/*
//boost
//第三方代理
//智能 指针
void main()
{
	int *ptr = new int(10);
	auto_ptr<int> pa(ptr);  //智能指针
	cout<<*pa<<endl;

	string *pstr = new string("abcxyzjtflalkjalk");
	auto_ptr<string> ps(pstr);
	cout<<ps->size()<<endl;
}
*/