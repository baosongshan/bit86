#include<iostream>
#include<bitset>
#include<vector>
#include<string>
#include<map>
using namespace std;

//无名 临时变量 具有const
int fun(int a, int b)
{
	int value = a + b;
	return value;
}

void main()
{
	int a = 10;

	int &&b = a;
	const int &value = fun(10, 20);

	int &&value1 = fun(10, 20);
}

/*
class A
{
public:
	A(int a) : _a(a)
	{}
	A(const A &) = delete;
private:
	int _a;
};

void main()
{
	A a(1);
	A b = a;
}

/*
class A
{
public:
	A() = delete; //A(){}
	A(const A&) = default;

	A(int a) :_a(a)
	{}
private:
	int _a;
};
void main()
{
	A a(1);
	A b;
}

/*
void main()
{
	map<int,string>::iterator pos;

	cout<<typeid(pos).name()<<endl; //字符串
	
	auto pos1 = pos;

	decltype(pos) it;

	int a = 10;
	int b = 20;

	decltype(a) c;
}

/*
template<class Type>
class SeqList
{
public:
	SeqList(const initializer_list<Type> &list) 
		: capacity(list.size()),size(0)
	{
		base = new Type[capacity];
		for(const auto &e : list)
			base[size++] = e;
	}
private:
	Type *base;
	size_t capacity;
	size_t size;
};

void main()
{
	SeqList<int> sq = {1,2,3,4,5};
}

/*
class Point
{
public:
	Point(int x = 0, int y = 0): _x(x), _y(y)
	{}
private:
	int _x;
	int _y;
};

int main()
{
	Point p{ 1, 2 };  //Pointer p(1,2);
	//Point p(1, 2 );
	return 0;
}

/*
void main()
{
	int ar[] = {1,2,3,4,5};
	vector<int> iv{1,2,3,4,5};

	int *p = new int[10]{1,2,3,4,5,6,7,8,9,10};
}

/*
//Key-->int % 

#define _N 1000

template<class T>  
struct KeyToInt1
{
	size_t operator()(const T &str)
	{
		return BKDRHash(str.c_str()) % _N;
	}
	size_t BKDRHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * 131 + ch;
		}
		return hash;
	}
};


template<class T>  
struct KeyToInt2
{
	size_t operator()(const T &str)
	{
		return SDBMHash(str.c_str()) % _N;
	}
	size_t SDBMHash(const char *str)
	{
		register size_t hash = 0;
		while (size_t ch = (size_t)*str++)
		{
			hash = 65599 * hash + ch;
		}
		return hash;
	}
};

template<class T>  
struct KeyToInt3
{
	size_t operator()(const T &str)
	{
		return RSHash(str.c_str()) % _N;
	}
	size_t RSHash(const char *str)
	{
		register size_t hash = 0;
		size_t magic = 63689;
		while (size_t ch = (size_t)*str++)
		{
			hash = hash * magic + ch;
			magic *= 378551;
		}
		return hash;
	}
};



template<class K, 
		 class hashfcn1 = KeyToInt1<K>, 
		 class hashfcn2 = KeyToInt2<K>,
		 class hashfcn3 = KeyToInt3<K>>
class BloomFilte
{
public:
	BloomFilte():size(0)
	{}
public:
	void insert(const K &key)
	{
		size_t index1 = hashfcn1()(key);
		size_t index2 = hashfcn2()(key);
		size_t index3 = hashfcn3()(key);
		_bmp.set(index1);
		_bmp.set(index2);
		_bmp.set(index3);
	}
	bool test(const K &key)
	{
		size_t index1 = hashfcn1()(key);
		if(!_bmp.test(index1))
			return false;
		size_t index2 = hashfcn2()(key);
		if(!_bmp.test(index2))
			return false;
		size_t index3 = hashfcn3()(key);
		if(!_bmp.test(index3))
			return false;

		return true;
	}
private:
	bitset<_N> _bmp;
	size_t     size;
};

void main()
{
	string url = "http://www.taobao.com";
	string url2 = "http://www.baidu.com";
	string url3 = "http://www.taobao.con";
	BloomFilte<string> bf;
	bf.insert(url.c_str());

	cout<<bf.test(url)<<endl; // 1
	cout<<bf.test(url3)<<endl;
}

/*
namespace bit
{
	class bitset
	{
		friend ostream& operator<<(ostream &out, const bitset &bt)
		{
			for(int i=bt.size()-1; i>=0; --i)
				out<<bt[i];
			return out;
		}
	public:
		bitset(size_t count) 
			: _bit(count/32+1), _bitCount(count)
		{}
		void set(int pos)
		{
			//0000 0000 0000 0000 0000 0000 0000 0100
			if(pos >= _bitCount)
				return;
			int index = pos / 32;   //1
			int offset = pos % 32;  //3
			_bit[index] |= (1<<offset);
		}
		void reset(int pos)
		{
			if(pos >= _bitCount)
				return;
			int index = pos / 32;   
			int offset = pos % 32; 
			_bit[index] &= ~(1<<offset);
		}
	public:
		size_t size()const
		{
			return _bitCount;
		}
		bool operator[](int pos)const
		{
			//00 0000 0100
			return _bit[pos/32] & (1<<(pos%32)) ? 1 : 0;
		}

	size_t count()const
	{
		//0000 0000 
		int bitCntTable[256] = {
0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2,
3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5,
6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5,
6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3,
4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
6, 7, 6, 7, 7, 8};
		size_t ar_count = _bit.size() / 32 + 1; //10
		size_t cnt = 0;
		for(int i=0; i<ar_count; ++i)
		{
			int value = _bit[i];
			int j = 0;
			while (value)
			{
				unsigned char c = value;
				cnt += bitCntTable[c];
				value >>= 8;
			}
		}
		return cnt;
	}
	private:
		vector<int> _bit;
		size_t      _bitCount;
	};
};

void main()
{
	//0000 0010 1000 0000
	bit::bitset bt(10);
	cout<<"bt = "<<bt<<endl;
	bt.set(2);
	bt.set(7);
	cout<<"bt = "<<bt<<endl;
	bt.reset(2);
	bt.set(9);
	cout<<"bt = "<<bt<<endl;
	cout<<"count = "<<bt.count()<<endl;


}

/*
namespace bit
{
	template<size_t _N> 
	class bitset 
	{
	public:
		typedef unsigned long _Ty;
	public:
		bitset()
		{
			_Tidy();
		}
	public:
		bitset<_N>& set()
		{
			_Tidy(~(_Ty)0);
			return (*this); 
		}
		bitset<_N>& set(size_t _P, bool _X = true)
		{
			if (_X)
				_A[_P / _Nb] |= (_Ty)1 << _P % _Nb;
			else
				_A[_P / _Nb] &= ~((_Ty)1 << _P % _Nb);
			return (*this); 
		}
		size_t size() const
		{
			return (_N); 
		}
		bool test(size_t _P) const
		{
			return ((_A[_P / _Nb] & ((_Ty)1 << _P % _Nb)) != 0); 
		}
		bool any() const
		{
			for (int _I = _Nw; 0 <= _I; --_I)
				if (_A[_I] != 0)
					return (true);
			return (false);
		}
		bool none() const
		{
			return (!any());
		}
		size_t count() const
		{
			size_t _V = 0;
			for (int _I = _Nw; 0 <= _I; --_I)
				for (_Ty _X = _A[_I]; _X != 0; _X >>= 4)
					_V += "\0\1\1\2\1\2\2\3"
					"\1\2\2\3\2\3\3\4"[_X & 0xF];
			return (_V);
		}

		class reference 
		{
			friend class bitset<_N>;
		public:
			reference& operator=(bool _X)
			{
				_Pbs->set(_Off, _X);
				return (*this); 
			}
			reference& operator=(const reference& _Bs)
			{
				_Pbs->set(_Off, bool(_Bs));
				return (*this); 
			}
			reference& flip()
			{
				_Pbs->flip(_Off);
				return (*this); 
			}
			bool operator~() const
			{
				return (!_Pbs->test(_Off)); 
			}
			operator bool() const
			{
				return (_Pbs->test(_Off)); 
			}
		private:
			reference(bitset<_N>& _X, size_t _P)
				: _Pbs(&_X), _Off(_P) {}
			bitset<_N> *_Pbs;
			size_t _Off;
		};

		reference operator[](size_t _P)
		{
			return (reference(*this, _P)); 
		}
	private:
		void _Tidy(_Ty _X = 0)
		{
			for (int _I = _Nw; 0 <= _I; --_I)
				_A[_I] = _X;
			if (_X != 0)
				_Trim();
		}
		void _Trim()
		{
			if (_N % _Nb != 0)
				_A[_Nw] &= ((_Ty)1 << _N % _Nb) - 1; 
		}
	private:
		enum 
		{
			//#define CHAR_BIT 8
			_Nb = CHAR_BIT * sizeof (_Ty),
			_Nw = _N == 0 ? 0 : (_N - 1) / _Nb
		};
		_Ty _A[_Nw + 1];

	private:
		friend ostream& operator<<(ostream& _O, const bitset<_N>& _R)
		{
			for (size_t _P = _N; 0 < _P;)
				_O << (_R.test(--_P) ? '1' : '0');
			return (_O);
		}
	};

};

void main()
{
	bit::bitset<10> bt;
	cout<<"bt = "<<bt<<endl;
	//bt.set(3);
	//reference r1 = r2;
	bt[3] = 1;
	cout<<"bt = "<<bt<<endl;
	cout<<"count = "<<bt.count()<<endl;

}

/*
//0 0 0 1 1 1 1 0 1 1

void main()
{
	bitset<10> bt1(123);
	bitset<10> bt2(100);
	cout<<"bt1 =  "<<bt1<<endl;
	cout<<"bt2 =  "<<bt2<<endl;

	bitset<10> bt = bt1 & bt2;
	cout<<"bt =   "<<bt<<endl;
}

/*
void main()
{
	bitset<10> bt(123);
	cout<<"bt =  "<<bt<<endl;
	//cin>>bt; //123
	cout<<"bt =  "<<~bt<<endl;
}

/*
void main()
{
	bitset<10> bt(123);
	for(int i=0; i<bt.size(); ++i)
		cout<<bt[i];
	cout<<endl;
}

/*
void main()
{
	bitset<10> bt(123);
	cout<<"bt =  "<<bt<<endl;
	//cout<<bt.test(2)<<endl;
	//cout<<bt.any()<<endl;
	//cout<<bt.at(1)<<endl;
	//bt.at(1) = 0;
	//cout<<"bt =  "<<bt<<endl;
	//cout<<bt.count()<<endl;
	//cout<<bt.size()<<endl;
	//cout<<bt.none()<<endl;
	//bt.set();
	//bt.set(1, false);
	//bt.reset();
	//bt.reset(1);
	//bt.flip();
	bt.flip(2);
	cout<<"bt =  "<<bt<<endl;

}

/*
void main()
{
	bitset<10> bt;
	cout<<"bt =  "<<bt<<endl;
	bitset<15> bt1(1234);
	cout<<"bt1 = "<<bt1<<endl;
	cout<<"bt1 = "<<bt1.to_ulong()<<endl;

}
*/