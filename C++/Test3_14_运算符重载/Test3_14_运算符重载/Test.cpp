#include<iostream>  //istream  ostream
#include<vld.h>
#include<assert.h>
#include<time.h>
#include<windows.h>
using namespace std;

class DateTime
{
	friend ostream& operator<<(ostream &out, const DateTime &d);
public:
	DateTime()
	{
		time_t te;
		time(&te);
		struct tm *ptm = localtime(&te);
		m_year = ptm->tm_year + 1900;
		m_month = ptm->tm_mon + 1;
		m_day = ptm->tm_mday;
		m_hour = ptm->tm_hour;
		m_minute = ptm->tm_min;
		m_second = ptm->tm_sec;
	}
	DateTime(int year, int month, int day, int h, int m, int s)
	{
		m_year = year;
		m_month = month;
		m_day = day;
		m_hour = h;
		m_minute = m;
		m_second = s;
	}
public:
	DateTime GetCurDateTime()
	{
		time_t te;
		time(&te);
		struct tm *ptm = localtime(&te);
		
		return DateTime(ptm->tm_year + 1900,
						ptm->tm_mon + 1,
						ptm->tm_mday,
						ptm->tm_hour,
						ptm->tm_min,
						ptm->tm_sec);
	}
public:
	void ShowDateTime()
	{
		//cout<<m_year<<"年"<<m_month<<"月"<<m_day<<"日";
		//cout<<m_hour<<"时"<<m_minute<<"分"<<m_second<<"秒";
		printf("%d年%d月%d日%d时%d分%d秒",m_year,m_month,m_day,m_hour,m_minute,m_second);
	}
	void DShowDateTime()
	{
		for(;;)
		{
			DateTime tmp = GetCurDateTime();
			tmp.ShowDateTime();
			Sleep(1000);
			system("cls");
		}
	}
private:
	int m_year;
	int m_month;
	int m_day;
	int m_hour;
	int m_minute;
	int m_second;
};

ostream& operator<<(ostream &out, const DateTime &d)
{
	out<<d.m_year<<"年"<<d.m_month<<"月"<<d.m_day<<"日";
	out<<d.m_hour<<"时"<<d.m_minute<<"分"<<d.m_second<<"秒";
	return out;
}

void main()
{

	DateTime dt;
	dt.DShowDateTime();
	

}

/*
class Date
{
	friend ostream& operator<<(ostream &out, const Date &d);
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		m_year = year;
		m_month = month;
		m_day = day;
	}
	//Date(const Date& d);
	//Date& operator=(const Date& d);
    ~Date()
	{}
public:
	Date operator+(int n)
	{
		//
	}
	Date operator-(int n)
	{}

	//计算星期
	int GetWeekByYMD(int year, int month, int day)
	{
		//
	}
private:
	int m_year;
	int m_month;
	int m_day;
};

ostream& operator<<(ostream &out, const Date &d)
{
	out<<d.m_year<<"年"<<d.m_month<<"月"<<d.m_day<<"日";
	return out;
}

void  main()
{
	Date d(2021, 3, 14);
	cout<<d<<endl;

	Date dt = d + 100;
	cout<<dt<<endl;

}

/*
class String
{
	friend ostream& operator<<(ostream &out, const String &s);
public:
	String(const char *str="")
	{
		m_data = (char *)malloc(strlen(str)+1);
		assert(m_data != NULL);
		strcpy(m_data, str);
	}
	String(const String &s)
	{
		m_data = (char *)malloc(strlen(s.m_data)+1);
		assert(m_data != NULL);
		strcpy(m_data, s.m_data);
	}
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			free(m_data);
			m_data = (char *)malloc(strlen(s.m_data)+1);
			assert(m_data != NULL);
			strcpy(m_data, s.m_data);
		}
		return *this;
	}
	~String()
	{
		free(m_data);
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
//main 
void main()
{
	char *str = "Hello C++";
	String s(str);
	cout<<"s = "<<s<<endl;

	String s1;
	s1 = s;
	cout<<"s1 = "<<s1<<endl;
}

/*
class Test
{
public:
	Test();
	Test(const Test &);
	Test& operator=(const Test &);
	~Test();
	Test* operator&();
	const Test* operator&()const;
};



/*
class Test
{
	friend ostream& operator<<(ostream &out, const Test &t);
	friend istream& operator>>(istream &in, Test &t);
public:
	explicit Test(int d = 0)
	{
		m_data = d;
	}
	Test(const Test &t)
	{
		m_data = t.m_data;
	}
	Test& operator=(const Test &t)
	{
		if(this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}
	~Test()
	{}
public:
	int GetData()const
	{return m_data;}
	void SetData(int data)
	{
		m_data = data;
	}
public:
	//强制类型转换
	operator int()
	{
		return m_data;
	}
private:
	int m_data;
};

void main()
{
	Test t;
	t = (Test)100;
	int value = t;
}



/*
void main()
{
	char ch = 'A';
	int a = 100;
	double d = 12.34;

	cout<<a<<endl;
	cout<<ch<<" : "<<a<<" : "<<d<<endl;
}


class Int
{
	friend ostream& operator<<(ostream &out, const Int &x);
public:
	Int(int i = 0) : m_i(i)
	{}
	~Int()
	{}
public:
	Int& operator++()      //++a
	{
		m_i++;
		return *this;
	}
	Int operator++(int)   //a++
	{
		Int tmp(*this); 
		m_i++;
		return tmp;
	}
	Int& operator--()
	{
		m_i--;
		return *this;
	}
	Int operator--( int)
	{
		Int tmp(*this);
		--*this;   //--(*this)
		return tmp;
	}
public:
	Int operator+(const Int &x)
	{
		return Int(m_i + x.m_i);
	}
	Int operator-(const Int &x);
	Int operator*(const Int &x);
	Int operator/(const Int &x);
	Int operator%(const Int &x);
public:
	Int& operator+=(const Int &x)
	{
		m_i += x.m_i;
		return *this;
	}
	Int& operator-=(const Int &x);
	Int& operator*=(const Int &x);
	Int& operator/=(const Int &x);
	Int& operator%=(const Int &x);

public:
	bool operator==(const Int &x)
	{return m_i == x.m_i;}
	bool operator!=(const Int &x);
	bool operator>(const Int &x);
	bool operator>=(const Int &x);
	bool operator<(const Int &x);
	bool operator<=(const Int &x);
private:
	int m_i;
};

ostream& operator<<(ostream &out, const Int &x)
{
	out<<x.m_i;
	return out;
}

void main()
{
	Int a = 1;
	Int b = 2;

	Int v = a+b;

	cout<<"v = "<<v<<endl;
	cout<<"a = "<<a<<endl;
}

/*
class Test
{
	friend ostream& operator<<(ostream &out, const Test &t);
	friend istream& operator>>(istream &in, Test &t);
public:
	explicit Test(int d = 0)
	{
		m_data = d;
	}
	Test(const Test &t)
	{
		m_data = t.m_data;
	}
	Test& operator=(const Test &t)
	{
		if(this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}
	~Test()
	{}
public:
	int GetData()const
	{return m_data;}
	void SetData(int data)
	{
		m_data = data;
	}
public:
private:
	int m_data;
};

ostream& operator<<(ostream &out, const Test &t)
{
	out<<t.m_data;  //cout.operator<<()
	return out;
}
istream& operator>>(istream &in, Test &t)
{
	in>>t.m_data;
	return in;
}

void main()
{
	Test t(100);
	cout<<t<<endl; 

	Test t1;
	cin>>t1;
}

/*
class Complex
{
	friend Complex operator+(int val, const Complex &c);
	friend Complex operator+(const Complex &c1, const Complex &c2);
public:
	//参数列表
	Complex(int real=0, int imag=0):m_real(real),m_imag(imag)
	{}
	Complex& operator=(const Complex &c)
	{
		if(this != &c)
		{
			m_real = c.m_real;
			m_imag = c.m_imag;
		}
		return *this;
	}
	~Complex()
	{}
public:
	
	Complex operator-(const Complex &c);
	Complex operator*(const Complex &c);
	Complex operator/(const Complex &c);
public:
	bool operator==(const Complex &c)
	{
		return (m_real==c.m_real && m_imag==c.m_imag);
	}
	bool operator!=(const Complex &c)
	{
		//return (m_real!=c.m_real || m_imag!=c.m_imag);
		return !(*this==c);
	}
	bool operator>(const Complex &c);
	bool operator<(const Complex &c);
	bool operator>=(const Complex &c);
	bool operator<=(const Complex &c);
private:
	int m_real;
	int m_imag;
};

Complex operator+(int val, const Complex &c)
{
	return Complex(val+c.m_real, c.m_imag);
}

Complex operator+(const Complex &c1, const Complex &c2)
{
	return Complex(c1.m_real+c2.m_real, c1.m_imag+c2.m_imag);
}

void main()
{
	Complex c, c1(1,3), c2(2,5);
	//c = c1 + 10;
	//c = 10 + c1;
	c = c1 + c2;
}

/*
class Test
{
	friend void fun(const Test &t); //友元
public:
	Test(int d = 0)
	{
		m_data = d;
	}
	
public:
	int GetData()const
	{
		return m_data;
	}
	void SetData(int data)
	{
		m_data = data;
	}
private:
	int m_data;
};

void fun(const Test &t)  //没有this
{
	int value = t.m_data;
	cout<<"value = "<<value<<endl;
}


void main()
{
	Test t(10);
	//t.m_data = 100;
	t.SetData(100);
	fun(t);
}

/*
class Complex
{
public:
	//参数列表
	Complex(int real=0, int imag=0):m_real(real),m_imag(imag)
	{}
	Complex& operator=(const Complex &c)
	{
		if(this != &c)
		{
			m_real = c.m_real;
			m_imag = c.m_imag;
		}
		return *this;
	}
	~Complex()
	{}
public:
	Complex operator+(int val)
	{
		return Complex(m_real+val, m_imag);
	}
	Complex operator+(const Complex &c)//成员函数
	{
		return Complex(m_real+c.m_real, m_imag+c.m_imag);
	}
	Complex operator-(const Complex &c);
	Complex operator*(const Complex &c);
	Complex operator/(const Complex &c);
public:
	bool operator==(const Complex &c)
	{
		return (m_real==c.m_real && m_imag==c.m_imag);
	}
	bool operator!=(const Complex &c)
	{
		//return (m_real!=c.m_real || m_imag!=c.m_imag);
		return !(*this==c);
	}
	bool operator>(const Complex &c);
	bool operator<(const Complex &c);
	bool operator>=(const Complex &c);
	bool operator<=(const Complex &c);
private:
	int m_real;
	int m_imag;
};

void main()
{
	Complex c, c1(1,3);
	c = c1 + 10;
	c = 10 + c1;

}

/*
//运算符重载  赋以新的含义 特殊函数而已
void main()
{
	Complex c1(1,3), c2(2,5);
	Complex c;
	c = c1 + c2;  // +
	//c = c1.operator+(c2);  //  left+right

	if(c1 != c2)  //c1.operator==(c2)
		cout<<"Equal"<<endl;
	else
		cout<<"No Equal"<<endl;
}

/*
class Test
{
public:
	explicit Test(int d = 0)
	{
		m_data = 0;
	}
	Test(const Test &t)
	{
		m_data = t.m_data;
	}
	Test& operator=(const Test &t)
	{
		if(this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}
	~Test()
	{}
public:
	operator int()
	{
		return m_data;
	}
private:
	int m_data;
};

void main()
{
	Test t;
	t = (Test)100;  //隐示转换
}

/*
void main()
{
	Test t1(10);
	Test t2(t1); // Test t2 = t1;

	Test t3;
	t3 = t2;

}
*/