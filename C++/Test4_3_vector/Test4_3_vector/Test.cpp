#include<iostream>
#include<vector>
#include<vld.h>
using namespace std;


namespace bit
{
	template<class _Ty>
	class vector
	{
	public:
		typedef _Ty* iterator;
	public:
		vector()
			:_First(nullptr),_Last(nullptr),_End(nullptr)
		{}
		~vector()
		{
			delete _First;
			_First = _Last = _End = nullptr;
		}
	public:
		size_t size()const
		{
			return _Last - _First;
		}
		size_t capacity()const
		{
			return _End - _First;
		}
		iterator begin()
		{
			return _First;
		}
		iterator end()
		{
			return _Last;
		}
		void push_back(const _Ty &x)
		{
			insert(end(), x);
		}
	public:
		void reserve(size_t n)
		{
			if(n > capacity())
			{
				//扩容
				size_t old_size = size();
				_Ty *new_first = new _Ty[n];
				memcpy(new_first, _First, sizeof(_Ty)*old_size);
				
				delete []_First;

				_First = new_first;
				_Last = _First + old_size;
				_End = _First + n;
			}
		}

		void resize(size_t n, const _Ty &x=_Ty())
		{
			if(n <= size())
			{
				_Last = _First + n;
				return;
			}

			if(n > capacity())
			{
				reserve(n);
			}

			iterator cur = _Last;
			_Last = _First + n;
			while(cur != _Last)
			{
				*cur = x;
				++cur;
			}
		}

		iterator insert(iterator _P, const _Ty &x)
		{
			if(_Last == _End)
			{
				size_t p_size = _P - _First;
				size_t new_size = size()==0 ? 1 : size()*2;
				reserve(new_size);
				//修改_P迭代器
				_P = _First + p_size;
			}
			iterator end = _Last;
			while(end > _P)
			{
				*end = *(end-1);
				--end;
			}

			*_P = x;
			++_Last;
			return _P;
		}
	private:
		iterator _First;
		iterator _Last;
		iterator _End;
	};
};

void main()
{
	bit::vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	v.push_back(5);

	for(auto &e : v)
		cout<<e<<" ";
	cout<<endl;

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;

	v.resize(70,9);

	for(auto &e : v)
		cout<<e<<" ";
	cout<<endl;

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
}

/*
void main()
{
	bit::vector<int> v;
	auto pos = v.begin();

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
	pos = v.insert(pos, 1);

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
	pos = v.insert(pos, 2);

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
	
	pos = v.insert(pos, 3);
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;

	pos=v.insert(pos, 4);
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;

	for(auto &e : v)
		cout<<e<<" ";
	cout<<endl;

}

/*
void main()
{
	bit::vector<int> v;
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;


	v.reserve(5);
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;

	v.reserve(15);
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
}

/*
void main()
{
	bit::vector<int> v;
	auto pos = v.begin();

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
	pos = v.insert(pos, 1);

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
	pos = v.insert(pos, 2);

	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;
	
	pos = v.insert(pos, 3);
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;

	pos=v.insert(pos, 4);
	cout<<"size = "<<v.size()<<endl;
	cout<<"capacity = "<<v.capacity()<<endl;

	for(auto &e : v)
		cout<<e<<" ";
	cout<<endl;

}

/*
int main()
{
	vector<int> v{ 1, 2, 3, 4};
	auto it = v.begin();

	while (it != v.end())
	{
		if (*it % 2 == 0)
		{
			it = v.erase(it);
		}
		else
			++it;
	}
	return 0;
}

/*
int main()
{
	int a[] = { 1, 2, 3, 4 };
	vector<int> v(a, a + sizeof(a) / sizeof(int));
	
	vector<int>::iterator pos = find(v.begin(), v.end(), 3);
	
	v.erase(pos);
	cout << *pos << endl; // 此处会导致非法访问

	for(int i=0; i<v.size(); ++i)
		//cout<<iv[i]<<" ";
		cout<<v.at(i)<<" ";
	cout<<endl;

	return 0;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);
	vector<int> iv(ar, ar+n);

	cout<<"size = "<<iv.size()<<endl;
	cout<<"capacity = "<<iv.capacity()<<endl;

	//iv.reserve(20);

	auto it = find(iv.begin(), iv.end(), 5);
	cout<<"*it = "<<*it<<endl;

	iv.push_back(20);

	it = find(iv.begin(), iv.end(), 5);

	cout<<"*it = "<<*it<<endl;

}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);
	vector<int> iv(ar, ar+n);

	for(int i=0; i<=iv.size(); ++i)
		//cout<<iv[i]<<" ";
		cout<<iv.at(i)<<" ";
	cout<<endl;
}

/*
void main()
{
	vector<int> iv;
	iv.push_back(1);
	iv.push_back(2);

	iv.insert(iv.begin(),10);

	//10 1  2 
	auto pos = find(iv.begin(), iv.end(), 1);
	iv.insert(pos, 20);
	

	for(int i=0; i<iv.size(); ++i)
		cout<<iv[i]<<" ";
	cout<<endl;
}

/*
void main()
{
	vector<int> iv(5,1);

	iv.resize(10, 2);

	cout<<"size = "<<iv.size()<<endl;
	cout<<"capacity = "<<iv.capacity()<<endl;

	for(int i=0; i<iv.size(); ++i)
		cout<<iv[i]<<" ";
	cout<<endl;
}

/*
void main()
{
	vector<int> iv(5,1);
	
	iv.reserve(100); //

	for(int i=1; i<=100; ++i)
	{
		iv.push_back(i);
		cout<<"capacity = "<<iv.capacity()<<endl;
	}
}

/*
void main()
{
	vector<int> iv;
	iv.push_back(1);
	iv.push_back(2);
	iv.push_back(3);
	iv.push_back(4);
	iv.push_back(5);
	iv.push_back(6);
	iv.push_back(7);

	cout<<"size = "<<iv.size()<<endl;
	cout<<"capacity = "<<iv.capacity()<<endl;

	//iv.resize(3);  //size 
	iv.reserve(8);  //capacity

	cout<<"size = "<<iv.size()<<endl;
	cout<<"capacity = "<<iv.capacity()<<endl;
}


/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	vector<int> iv(ar, ar+n);

	cout<<"size = "<<iv.size()<<endl;
	cout<<"capacity = "<<iv.capacity()<<endl;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	vector<int> iv(ar, ar+n);

	vector<int>::iterator it = iv.begin();
	while(it != iv.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	vector<int>::reverse_iterator rit = iv.rbegin();
	while(rit != iv.rend())
	{
		cout<<*rit<<" ";
		++rit;
	}
	cout<<endl;
}

/*
void main()
{
	vector<int> iv;
	vector<int> iv1(10);

	for(int i=0; i<iv1.size(); ++i)
		cout<<iv1[i]<<" ";
	cout<<endl;

	for(auto &e : iv1)
		cout<<e<<" ";
	cout<<endl;

	vector<int>::iterator it = iv1.begin();
	while(it != iv1.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}
*/