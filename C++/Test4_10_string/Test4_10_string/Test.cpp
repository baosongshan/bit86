#include<iostream>
#include<vector>
#include<assert.h>
//#include<string>
#include<vld.h>
using namespace std;

//字符串的模拟实现
namespace bit
{
	class string
	{
		friend ostream& operator<<(ostream &out, const string &s);
	public:
		static size_t npos;
		typedef char * iterator;
	public:
		string() : _str(nullptr),_size(0),_capacity(0)
		{}
		string(const char *str)
		{
			_size = strlen(str);
			_capacity = _size;
			_str = new char[_capacity+1]; 
			strcpy(_str, str);
		}
		string(const string &s):_str(nullptr),_size(0),_capacity(0)
		{
			string tmp(s._str);
			swap(*this, tmp);
		}
		string& operator=(const string &s)
		{
			if(this != &s)
			{
				string tmp(s);
				swap(*this, tmp);
			}
			return *this;
		}
		~string()
		{
			delete []_str;
			_str = nullptr;
		}
	public:
		size_t size()const
		{return _size;}
		size_t capacity()const
		{return _capacity;}
		bool empty()const
		{return _size == 0;}
	public:
		iterator begin()
		{return _str;}
		iterator end()
		{return _str + _size;}
	public:
		void push_back(char c)
		{
			if(_size+1 > _capacity)
			{
				int n = _capacity==0 ? 1 : _capacity * 2;
				reserve(n);
			}
			_str[_size++] = c;
			_str[_size] = '\0';
		}
		void append(const char* str)
		{
			size_t sz = strlen(str);
			if(_size+sz > _capacity)
			{
				reserve(_size+sz);
			}

			strcat(_str, str);
			_size += sz;
		}

		string& operator+= (char c)
		{
			push_back(c);
			return *this;
		}
		string& operator+=(const char *str)
		{
			append(str);
			return *this;
		}
		string& operator+=(const string &s)
		{
			append(s._str);
			return *this;
		}
		const char* c_str()const
		{
			return _str;
		}
		char& operator[](int i)
		{
			assert(i>=0 && i<_size);
			return _str[i];
		}
	public:
		void resize(int new_sz, char ch='\0')
		{
			if(new_sz > _capacity)
			{
				reserve(new_sz);
				
				for(int i=_size; i<new_sz; ++i)
					_str[i] = ch;
			}
			
			_size = new_sz;
			_str[_size] = '\0';
		}
		void reserve(int n)
		{
			if(n > _capacity)
			{
				char *new_str = new char[n+1];
				memset(new_str, 0, n+1);
				if(_str != nullptr)
					memcpy(new_str, _str, _capacity+1);
				_capacity = n;
				delete []_str;
				_str = new_str;
			}
		}
	public:

		bool operator<(const string& s);
		bool operator<=(const string& s);
		bool operator>(const string& s);
		bool operator>=(const string& s);
		bool operator==(const string& s)
		{
			return (strcmp(_str, s._str) == 0);
		}
		static void swap(string &s1, string& s2)
		{
			std::swap(s1._str, s2._str);
			std::swap(s1._size, s2._size);
			std::swap(s1._capacity, s2._capacity);
		}
	public:
		
		// 返回c在string中第一次出现的位置
		size_t find(char c, size_t pos = 0) const
		{
			for(int i=pos; i<_size; ++i)
			{
				if(_str[i] == c)
					return i;
			}
			return npos;
		}

		//A B C
		size_t rfind (char c, size_t pos = npos) const
		{
			int new_pos = (pos==npos ? _size-1 : pos);
			for(int i=new_pos; i>=0; --i)
			{
				if(_str[i] == c)
					return i;
			}
			return npos;
		}

		// 返回子串s在string中第一次出现的位置
		size_t find(const char* s, size_t pos = 0) const
		{
			int i = pos;  //_str
			int j = 0;    //s
			while(i<_size && j<strlen(s))
			{
				if(_str[i] == s[j])
				{
					++i;
					++j;
				}
				else
				{
					j = 0;
					i = i-j+1;
				}
			}
			if(j>strlen(s))
				return i-strlen(s);
			return npos;

		}
		// 在pos位置上插入字符c/字符串str，并返回该字符的位置
		string& insert(size_t pos, char c)
		{
			if(_size+1 > _capacity)
				reserve(_capacity*2);

			for(int i=_size; i>pos; --i)
				_str[i] = _str[i-1];

			_str[pos] = c;
			_size++;
			return *this;
		}
		string& insert(size_t pos, const char* str)
		{
			int len = strlen(str);
			if(_size+len > _capacity)
				reserve(_size+len);

			for(int i=_size; i>=pos; --i)
				_str[i+len] = _str[i];

			int j = 0;
			for(int i=pos; j<len; ++i,++j)
			{
				_str[i] = str[j];
			}
			_size += len;
			return *this;
		
		}
		// 删除pos位置上的元素，并返回该元素的下一个位置
		//abcdefghijk
		//   3
		string& erase(size_t pos, size_t len)
		{
			char *tmp = new char[_size-len+1];
			memset(tmp, 0, _size-len+1);
			strncpy(tmp, _str, pos);
			strncat(tmp, _str+pos+len, _size-pos-len+1);

			strcpy(_str, tmp);
			_size -= len;
			delete []tmp;
			return *this;
		}

	private:
		char *_str;
		size_t _size;
		size_t _capacity;
	};

	size_t bit::string::npos = (size_t)(-1);

	ostream& operator<<(ostream &out, const string &s)
	{
		out<<s._str;
		return out;
	}

	bool operator!=(const string& s1, const string &s2)
	{
		return strcmp(s1.c_str(), s2.c_str());
	}
};

void main()
{
	bit::string s1("abcdefghij");
	//int pos = s1.find('e');
	//s1.insert(pos, "@#$");

	s1.erase(3, 3);

	cout<<s1<<endl;
}

/*
size_t find(const char* s, size_t pos = 0) const
		{
			char *t = _str + pos;
			const char *ps = s;
			while(*ps != '\0' && *t != '\0')
			{
				if(*ps != *t)
				{
					ps = s;
				}
				else
				{
					ps++;
				}
				t++;
			}

			if(*ps == '\0')
				return t-_str-strlen(s);
				
			return string::npos;
		}

void main()
{
	bit::string s1("xyzabyc");
	int index = s1.rfind('y', 4);
	if(index == bit::string::npos)
		cout<<"NO."<<endl;
	else
		cout<<index<<endl;
}

/*
void main()
{
	bit::string s1("xyzabc");
	bit::string s2("xyzabc");
	if(s1 == s2)
		cout<<"OK."<<endl;
	else
		cout<<"NO."<<endl;
}

/*
void main()
{
	bit::string s1("xyzabc");
	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;
	s1.resize(9,'@');
	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;
}

/*
void main()
{
	bit::string s1("xyzabcABCXYZ");

	for(auto &e : s1)
		cout<<e;
	cout<<endl;

	bit::string::iterator it = s1.begin();
	while(it != s1.end())
	{
		cout<<*it;
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	bit::string s1("xyzabcABCXYZ");
	for(int i=0; i<s1.size(); ++i)
		cout<<s1[i];
	cout<<endl;

	s1[0] = 'X';  //const

	cout<<s1<<endl;
}

/*
void main()
{
	bit::string s1("xyz");
	int len = strlen(s1.c_str());
}

/*
void main()
{
	bit::string s1("xyz");
	bit::string s2("abc");

	//s1.append("abc");
	//s1 += 'A';
	//s1 += "AB";
	s1 += s2;

	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;
}

/*
void main()
{
	bit::string s1;

	for(int i=0; i<10; ++i)
		s1.push_back('a'+1);

	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;
}

/*
void main()
{
	bit::string s1("Hello");
	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;
	s1.push_back('C');
	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;
}

/*
void main()
{
	bit::string s;
	bit::string s1("Hello");
	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;

	s1.reserve(100);

	cout<<"s1 = "<<s1<<endl;
	cout<<"s1 size = "<<s1.size()<<endl;
	cout<<"s1 capacity = "<<s1.capacity()<<endl;


}

/*
namespace bit
{
	class string
	{
	public:
		string(const char* str = "")
		{
			// 构造string类对象时，如果传递nullptr指针，认为程序非法，此处断言下
			if (nullptr == str)
			{
				assert(false);
				return;
			}
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		string(const string &s):_str(nullptr)
		{
			string tmp(s._str);
			swap(_str, tmp._str);
		}
		string& operator=(string &s)
		{
			if(this != &s)
			{
				//string tmp(s);    //拷贝构造
				string tmp(s._str); //构造函数
				swap(_str, tmp._str);
			}
			return *this;
		}
		~string()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;
			}
		}
	private:
		char* _str;
	};
};

void main()
{
	bit::string s("abc");
	bit::string s1("xyz");
	s1 = s;
}

/*
void main()
{
	string s1 = "abc";
	string s2 = "abc";
	string s3 = s1 + s2;

	if(s1 > s2)
		cout<<"s1 > s2"<<endl;
	else if(s1 == s2)
		cout<<"s1 == s2"<<endl;
	else
		cout<<"s1 < s2"<<endl;

	string str;
	//cin>>str;  //"Hello You"
	getline(cin, str, ' ');
	cout<<"str = "<<str<<endl;
}

/*
void main()
{
	string s("string.cpp");
	s += 'c';
	s += "java";
}

/*
void main()
{
	string file("string.cpp");


	string email_type = "xxxxxx@qq.com";

	size_t pos = file.rfind('.');
	string suffix(file.substr(pos+1, file.size() - pos));
	cout << suffix << endl;
}

/*
void main()
{
	string s("abcvip"); 
	string ret = s.substr(2, 3);
	cout<<"ret = "<<ret<<endl;

	cout<<"s = "<<s<<endl;
}

/*
void main()
{
	string s("abcxxz"); 

	//int pos = s.find('x');
	//int pos = s.find('x', 4);
	//int pos = s.find("cxy");
	//int pos = s.find("cxy", 3);
	int pos = s.find("cxyjflalajflka", 2, 2);
	if(pos == string::npos)
		cout<<"没有找到"<<endl;
	else
		cout<<"pos = "<<pos<<endl;

}

/*
void main()
{
	string s1 = "abc";
	int len = strlen(s1.c_str());

	string s2;
	s2.resize(10);
	cout<<"s2 size = "<<s2.size()<<endl;
	len = strlen(s2.c_str());
	cout<<"s2 size = "<<len<<endl;

}

/*
void main()
{
	string s1 = "abc";
	string s2 = "xyz";
	string s3 = s1 + s2;
	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;
	cout<<"s3 = "<<s3<<endl;

	s1 += s2;
	cout<<"s1 = "<<s1<<endl;

}

/*
void main()
{
	string s("abc"); 
	cout<<"s = "<<s<<endl;
	s.push_back('x');
	cout<<"s = "<<s<<endl;
	s.append("fgh");
	cout<<"s = "<<s<<endl;
}

/*
void main()
{
	string s("abcxyz");   //C
	cout<<"s = "<<s<<endl;

	for(int i=0; i<s.size(); ++i)
		cout<<s[i];
	cout<<endl;

	string::iterator it = s.begin();
	while(it != s.end())
	{
		cout<<*it;
		++it;
	}
	cout<<endl;

	for(auto &e : s)
		cout<<e;
	cout<<endl;

	const string s1 = "asdfghjkl";
	string::const_iterator cit = s1.cbegin();
	while(cit != s1.cend())
	{
		cout<<*cit;
		++cit;
	}
	cout<<endl;

	string::reverse_iterator rit = s.rbegin();
	while(rit != s.rend())
	{
		cout<<*rit;
		++rit;
	}
	cout<<endl;

}

/*
void main()
{
	string s;
	cout<<"s = "<<s<<endl;
	
	char *pstr = "abc";
	string s1(pstr);
	cout<<"s1 = "<<s1<<endl;

	string s2("xyz");
	cout<<"s2 = "<<s2<<endl;

	string s3(10,'a');
	cout<<"s3 = "<<s3<<endl;

	string s4 = s2;
	cout<<"s4 = "<<s4<<endl;

	cout<<"s3 size = "<<s3.size()<<endl;
	cout<<"s3 length = "<<s3.length()<<endl;
	cout<<"s3 capacity = "<<s3.capacity()<<endl;

	s3.append("fjlajflajfla");
	cout<<"s3 = "<<s3<<endl;
	cout<<"s3 capacity = "<<s3.capacity()<<endl;

	s3.clear();
	cout<<"s3 = "<<s3<<endl;
	cout<<"s3 length = "<<s3.length()<<endl;
	cout<<"s3 capacity = "<<s3.capacity()<<endl;

	s3.reserve(100);
	cout<<"s3 = "<<s3<<endl;
	cout<<"s3 length = "<<s3.length()<<endl;
	cout<<"s3 capacity = "<<s3.capacity()<<endl;

	s3.resize(10, 's');//0 0 0 0 0 0 0 0 0 0
	cout<<"s3 = "<<s3<<endl;
	cout<<"s3 size = "<<s3.size()<<endl;
	cout<<"s3 length = "<<s3.length()<<endl;
	cout<<"s3 capacity = "<<s3.capacity()<<endl;
}

/*
void main()
{
	//C++ string
	string s;
	basic_string<char, char_traits<char>, allocator<char> > s1;
}

/*
class String
{
	friend ostream& operator<<(ostream &out, const String &s);
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
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			delete m_data;
			m_data = new char[strlen(s.m_data)+1];
			strcpy(m_data, s.m_data);
		}
		return *this;
	}
	~String()
	{
		delete []m_data;
		m_data = nullptr;
	}
private:
	char *m_data;
};

ostream& operator<<(ostream &out, const String &s)
{
	out<<s.m_data;
	return out;
}
/////////////////////////////////////////////////////
namespace bit
{
	template<class T>
	class vector
	{
	public:
		// Vector的迭代器是一个原生指针
		typedef T* iterator;
		typedef const T* const_iterator;
		iterator begin() { return _start; }
		iterator end() { return _finish; }
		const_iterator cbegin() const { return _start; }
		const_iterator cend() const { return _finish; }
		// construct and destroy
		vector()
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{}
		vector(int n, const T& value = T())
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(n);
			while (n--)
			{
				push_back(value);
			}
		}
		template<class InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			reserve(last - first);
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}
		vector(const vector<T>& v)
			: _start(nullptr)
			, _finish(nullptr)
			, _endOfStorage(nullptr)
		{
			reserve(v.capacity());
			iterator it = begin();
			const_iterator vit = v.cbegin();
			while (vit != v.cend())
			{
				*it++ = *vit++;
			}
			_finish = it;
		}
		vector<T>& operator=(vector<T> v)
		{
			swap(v);
			return *this;
		}
		~vector()
		{
			delete[] _start;
			_start = _finish = _endOfStorage = nullptr;
		}
		// capacity
		size_t size() const { return _finish - _start; }
		size_t capacity() const { return _endOfStorage - _start; }
		bool empty() const { return _first == _finish; }
		void reserve(size_t n)
		{
			if (n > capacity())
			{
				size_t oldSize = size();
				T* tmp = new T[n];

				// 这里直接使用memcpy?
				//if (_start)
				// memcpy(tmp, _start, sizeof(T)*size);

				if (_start)
				{
					for (size_t i = 0; i < oldSize; ++i)
						tmp[i] = _start[i];
				}

				_start = tmp;
				_finish = _start + oldSize;
				_endOfStorage = _start + n;
			}
		}
		void resize(size_t n, const T& value = T())
		{
			// 1.如果n小于当前的size，则数据个数缩小到n
			if (n <= size())
			{
				_finish = _start + n;
				return;
			}
			// 2.空间不够则增容
			if (n > capacity())
				reserve(n);
			// 3.将size扩大到n
			iterator it = _finish;
			iterator _finish = _start + n;
			while (it != _finish)
			{
				*it = value;
				++it;
			}
		}
		///////////////access///////////////////////////////
		T& operator[](size_t pos){ return _start[pos]; }
		const T& operator[](size_t pos)const { return _start[pos]; }
		///////////////modify/////////////////////////////
		void push_back(const T& x){ insert(end(), x); }
		void pop_back(){ erase(--end()); }
		void swap(vector<T>& v)
		{
			swap(_start, v._start);
			swap(_finish, v._finish);
			swap(_endOfStorage, v._endOfStorage);
		}
		iterator insert(iterator pos, const T& x)
		{
			assert(pos <= _finish);
			// 空间不够先进行增容
			if (_finish == _endOfStorage)
			{
				size_t sz = size();
				size_t newCapacity = (0 == capacity()) ? 1 : capacity() * 2;
				reserve(newCapacity);
				// 如果发生了增容，需要重置pos
				pos = _start + sz;
			}
			iterator end = _finish - 1;
			while (end >= pos)
			{
				*(end + 1) = *end;
				--end;
			}
			*pos = x;
			++_finish;
			return pos;
		}
		iterator erase(iterator pos)
		{
			// 挪动数据进行删除
			iterator begin = pos + 1;
			while (begin != _finish) 
			{
				*(begin - 1) = *begin;
				++begin;
			}
			--_finish;
			return pos;
		}
	private:
		iterator _start; // 指向数据块的开始
		iterator _finish; // 指向有效数据的尾
		iterator _endOfStorage; // 指向存储容量的尾
	};
}

void main()
{
	String str[] = {"abc","xyz", "lmn"};
	bit::vector<String> v;
	v.push_back(str[0]);
	v.push_back(str[1]);
	v.push_back(str[2]);

	cout<<"v capacity = "<<v.capacity()<<endl;

	bit::vector<String> v1 = v;
	v1[0] = "RST";

	for(auto &e : v)
		cout<<e<<endl;

	for(auto &e : v1)
		cout<<e<<endl;

}

/*
void main()
{
	String str[] = {"abc","xyz", "lmn"};
	vector<String> v;
	v.push_back(str[0]);
	v.push_back(str[1]);
	v.push_back(str[2]);

	for(auto &e : v)
		cout<<e<<endl;
}

/*
void main()
{
	char* str[] = {"abc","xyz", "lmn"};
	vector<char*> v;
	for(int i=0; i<3; ++i)
		v.push_back(str[i]); //

	for(auto &e : v)
		cout<<e<<endl;
	cout<<endl;
}

/*
void main()
{
	vector<char> v;
	for(int i=0; i<10; ++i)
		v.push_back('a'+i); //

	for(auto &e : v)
		cout<<e;
	cout<<endl;
}
*/