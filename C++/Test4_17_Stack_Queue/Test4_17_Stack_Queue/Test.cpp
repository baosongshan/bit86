#include<iostream>
#include<stack>
#include<list>
#include<vector>
#include<queue>
#include<deque>
#include<functional>
using namespace std;

void main()
{
	list<int> lt;
	vector<int> iv = {3,2,3,1,2,4,5,5,6};
	for(int i=0; i<iv.size(); ++i)
		lt.push_back(iv[i]);

	lt.sort();
	for(const auto &e : lt)
		cout<<e<<" ";
	cout<<endl;

	lt.unique();
	
	for(const auto &e : lt)
		cout<<e<<" ";
	cout<<endl;

}

/*
void main()
{
	priority_queue<int> pq;
	int ar[9] = {3,2,3,1,2,4,5,5,6};
	
	for(int i=0; i<9; ++i)
		pq.push(ar[i]);


	while(!pq.empty())
	{
		int value = pq.top();
		pq.pop();
		cout<<value<<" ";
	}
	cout<<endl;


}


/*
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		return (_year < d._year) ||
			(_year == d._year && _month < d._month) ||
			(_year == d._year && _month == d._month && _day < d._day);
	}
	bool operator>(const Date& d)const
	{
		return (_year > d._year) ||
			(_year == d._year && _month > d._month) ||
			(_year == d._year && _month == d._month && _day > d._day);
	}
private:
	int _year;
	int _month;
	int _day;
};

void main()
{
	vector<Date> dt{{2020,1,1}, {1998,10,1}, {2022,3,5}, {2000, 4,5}};
	make_heap(dt.begin(), dt.end(), greater<Date>());
}

/*
void main()
{
	int ar[] = {10};
	vector<int> iv{5,8,30,2,1,4,9,7}; //
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	//谓词
	make_heap(iv.begin(), iv.end(), greater<int>());  //
	//make_heap(iv.begin(), iv.end());  //

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
}

/*
struct int_less
{
	bool operator()(void* elem1, void *elem2)
	{
		return *(int*)elem1 < *(int*)elem2;
	}
};


struct int_greater
{
	bool operator()(void* elem1, void *elem2)
	{
		return *(int*)elem1 > *(int*)elem2;
	}
};

void my_qsort(void *base, 
			  size_t num, 
              size_t width, 
              int_less Pr=int_less())
{
	void *tmp = malloc(width);
	for(int i=0; i<num-1; ++i)
	{
		for(int j=0; j<num-i-1; ++j)
		{
			//base[j]                       base[j+1]
			//if(((char*)base)+j*width > ((char*)base)+(j+1)*width)
			if(!Pr(((char*)base)+j*width, ((char*)base)+(j+1)*width))
			{
				memcpy(tmp, ((char*)base)+j*width, width);
				memcpy(((char*)base)+j*width, ((char*)base)+(j+1)*width , width);
				memcpy(((char*)base)+(j+1)*width, tmp, width);
			}
		}
	}
}

void main()
{
	int ar[] = {5,8,30,2,1,4,9,7}; //
	int n = sizeof(ar) / sizeof(ar[0]);

	for(int i=0; i<n; ++i)
		cout<<ar[i]<<" ";
	cout<<endl;

	my_qsort(ar, n, sizeof(int), int_less());
	
	for(int i=0; i<n; ++i)
		cout<<ar[i]<<" ";
	cout<<endl;
}

/*
//void qsort( void *base, 
//            size_t num, 
//            size_t width, 
//            int (*compare )(const void *elem1, const void *elem2 ) );

int int_less(const void *elem1, const void *elem2 )
{
	return (*(int*)elem1 - *(int*)elem2); // >0 ==0 <0
}

int int_greater(const void *elem1, const void *elem2 )
{
	return (*(int*)elem2 - *(int*)elem1); // >0 ==0 <0
}

void my_qsort(void *base, 
			  size_t num, 
              size_t width, 
              int (*compare )(const void *elem1, const void *elem2 ) )
{
	void *tmp = malloc(width);
	for(int i=0; i<num-1; ++i)
	{
		for(int j=0; j<num-i-1; ++j)
		{
			//base[j]                       base[j+1]
			//if(((char*)base)+j*width > ((char*)base)+(j+1)*width)
			if(compare(((char*)base)+j*width, ((char*)base)+(j+1)*width) > 0)
			{
				memcpy(tmp, ((char*)base)+j*width, width);
				memcpy(((char*)base)+j*width, ((char*)base)+(j+1)*width , width);
				memcpy(((char*)base)+(j+1)*width, tmp, width);
			}
		}
	}
}

void main()
{
	int ar[] = {5,8,30,2,1,4,9,7}; //
	int n = sizeof(ar) / sizeof(ar[0]);

	for(int i=0; i<n; ++i)
		cout<<ar[i]<<" ";
	cout<<endl;

	my_qsort(ar, n, sizeof(int), int_greater);
	
	for(int i=0; i<n; ++i)
		cout<<ar[i]<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[] = {10};
	vector<int> iv{5,8,30,2,1,4,9,7}; //
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	//谓词
	make_heap(iv.begin(), iv.end(), greater<int>());  //
	//make_heap(iv.begin(), iv.end());  //

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	plus<int> pl; //对象

	pl.operator()(10,20);
	cout<<pl(10,20)<<endl; //仿函数
}

/*
template<class _Ty>
struct my_plus
{	
	_Ty operator()(const _Ty& _Left, const _Ty& _Right) const
	{	
		return (_Left + _Right);
	}
};

void main()
{
	my_plus<int> pl; //对象

	pl.operator()(10,20);
	cout<<pl(10,20)<<endl; //仿函数
}

/*
void main()
{
	int ar[] = {10};
	vector<int> iv{5,8,30,2,1,4,9,7}; //
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	make_heap(iv.begin(), iv.end(), greater<int>());  //

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[] = {10};
	vector<int> iv{5,8,30,2,1,4,9,7}; //
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	make_heap(iv.begin(), iv.end());  //

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	iv.push_back(10);
	push_heap(iv.begin(), iv.end()); //堆的调整

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;


	sort_heap(iv.begin(), iv.end());
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	int ar[] = {10};
	vector<int> iv{5,8,30,2,1,4,9,7};
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	make_heap(iv.begin(), iv.end());  //

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	//push_heap(ar, ar+1);
	auto it = iv.end();
	for(int i=0; i<iv.size()-1; ++i)
	{
		pop_heap(iv.begin(), it);
		--it;
	}

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	vector<int> iv{5,8,30,2,1,4,9,7};

	priority_queue<int> pq; //大堆结构
	for(int i=0; i<iv.size(); ++i)
		pq.push(iv[i]);

	cout<<"pq size = "<<pq.size()<<endl;
	cout<<"pq top = "<<pq.top()<<endl;

	pq.pop();
	cout<<"pq top = "<<pq.top()<<endl;

	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

}

/*
namespace bit
{
	template<class _Ty, class Cont=deque<_Ty>>
	class stack
	{
	public:
		stack()
		{}
		~stack()
		{}
	public:
		bool empty()const
		{
			return _C.empty();
		}
		size_t size()const
		{
			return _C.size();
		}
		_Ty& top()
		{
			return _C.back();
		}
		const _Ty& top()const
		{
			return _C.back();
		}
		void push(const _Ty &x)
		{
			_C.push_back(x);
		}
		void pop()
		{
			_C.pop_back();
		}
	private:
		Cont _C;
	};

	template<class _Ty, class Cont=deque<_Ty>>
	class queue
	{
	public:
		queue()
		{}
		~queue()
		{}
	public:
		bool empty()const
		{
			return _C.empty();
		}
		size_t size()const
		{
			return _C.size();
		}
		_Ty& front()
		{
			return _C.front();
		}
		_Ty& back()
		{
			return _C.back();
		}
		void pop()
		{
			_C.pop_front();
		}
		void push(const _Ty &x)
		{
			_C.push_back(x);
		}
	private:
		Cont _C;
	};
};

void main()
{
	bit::queue<int, list<int>> q;
	q.push(1);
	q.push(2);
	q.push(3);

	cout<<q.front()<<endl;
	cout<<q.back()<<endl;
	q.pop();
}

/*
void main()
{
	//bit::stack<int, vector<int>> st;
	bit::stack<int> st;
	for(int i=1; i<=10; ++i)
		st.push(i);

	cout<<"st size = "<<st.size()<<endl;
	while(!st.empty())
	{
		int value = st.top();
		st.pop();
		cout<<value<<endl;
	}
}

/*
void main()
{
	deque<int> dq;
	dq.push_back(1);
	dq.push_back(2);
	dq.push_back(3);

	dq.push_front(10);
	dq.push_front(20);
	dq.push_front(30);

	for(const auto &e : dq)
		cout<<e<<" ";
	cout<<endl;

	deque<int>::iterator it = dq.begin();
	while(it != dq.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

}

/*
void main()
{
	queue<int> st;
	for(int i=1; i<=10; ++i)  //1 2 3 4 5 6 7 8 9 10
		st.push(i);

	cout<<"st size = "<<st.size()<<endl;
	
	while(!st.empty())
	{
		int value = st.front();
		st.pop();
		cout<<value<<endl;
	}
}

/*
namespace bit
{
	template<class _Ty>
	class stack
	{
	public:
		stack()
		{}
		~stack()
		{}
	public:
		bool empty()const
		{
			return _C.empty();
		}
		size_t size()const
		{
			return _C.size();
		}
		_Ty& top()
		{
			return _C.back();
		}
		const _Ty& top()const
		{
			return _C.back();
		}
		void push(const _Ty &x)
		{
			_C.push_back(x);
		}
		void pop()
		{
			_C.pop_back();
		}
	private:
		vector<_Ty> _C;
	};
};

void main()
{
	bit::stack<int> st;
	for(int i=1; i<=10; ++i)
		st.push(i);

	cout<<"st size = "<<st.size()<<endl;
	while(!st.empty())
	{
		int value = st.top();
		st.pop();
		cout<<value<<endl;
	}
}

/*
namespace bit
{
	template<class _Ty>
	class stack
	{
	public:
		stack()
		{}
		~stack()
		{}
	public:
		bool empty()const
		{
			return _C.empty();
		}
		size_t size()const
		{
			return _C.size();
		}
		_Ty& top()
		{
			return _C.back();
		}
		const _Ty& top()const
		{
			return _C.back();
		}
		void push(const _Ty &x)
		{
			_C.push_back(x);
		}
		void pop()
		{
			_C.pop_back();
		}
	private:
		list<_Ty> _C;
	};
};

void main()
{
	bit::stack<int> st;
	for(int i=1; i<=10; ++i)
		st.push(i);

	cout<<"st size = "<<st.size()<<endl;
	while(!st.empty())
	{
		int value = st.top();
		st.pop();
		cout<<value<<endl;
	}
}


/*
namespace bit
{
	template<class _Ty>
	class stack
	{
	public:
		stack()
		{
			capacity = STACK_DEFAULT_SIZE;
			tp = 0;
			base = new _Ty[capacity];
		}
		~stack()
		{
			delete []base;
			base = nullptr;
			capacity = tp = 0;
		}
	public:
		bool empty()const
		{return tp == 0;}
		size_t size()const
		{return tp;}
		_Ty& top()
		{
			assert(tp != 0);
			return base[tp-1];
		}
		const _Ty& top()const
		{
			assert(tp != 0);
			return base[tp-1];
		}
		void push(const _Ty &x)
		{
			if(tp >= capacity)
			{
				//扩容
			}
			base[tp++] = x;
		}
		void pop()
		{
			assert(tp != 0);
			tp--;
		}
	private:
		enum{STACK_DEFAULT_SIZE=8};
		_Ty *base;
		size_t capacity;
		size_t tp;
	};
};

void main()
{
	bit::stack<int> st;
}


/*
//容器适配器 
void  main()
{
	stack<int> st;
	for(int i=1; i<=10; ++i)
		st.push(i);

	cout<<"st size = "<<st.size()<<endl;
	while(!st.empty())
	{
		int value = st.top();
		st.pop();
		cout<<value<<endl;
	}

	int ar[] = {1,2,3,4,5,6,7,8,9,10};  // int*
	for(const auto &e : ar)
		cout<<e<<" ";
	cout<<endl;
}
*/