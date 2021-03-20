#include<iostream>
#include<assert.h>
using namespace std;


class Test
{
public:
	class Stu   //STL  iterator
	{
	public:
		void show()
		{
			cout<<"aaaaaaaaaaa"<<endl;
		}
	private:
		int m_x;
	};
public:
	void fun()
	{
		cout<<"bbbbbbbbb"<<endl;
	}
private:
	int m_a;
};

void main()
{
	Test t;
	t.fun();
	Test::Stu s;
	s.show();
}

/*
class Stu;   //前向声明
class Test;



class Test
{
	friend class Stu; //友元类
public:
	Test()
	{
	}
	void list(Stu &s)
	{
		s.myfun();
	}
private:
	void show()const
	{
		cout<<"This is Test::show()"<<endl;
	}
	
private:
	int m_a = 0;  //默认值
	int m_b = 0;
};

class Stu
{
public:
	void fun(const Test &t)
	{
		t.show();
	}
	void print(const Test &t)
	{
		t.show();
	}
private:
	void myfun()
	{
		cout<<"This is::Stu::myfun()"<<endl;
	}
public:
	int m_x = 0;
	int m_y = 0;;
};


void main()
{
	Test t;
	Stu s;

	//s.fun(t);
	//s.print(t);

	t.list(s);
}

/*
//C++11  dev++
class Test
{
	friend void fun(const Test &t, const Stu &s);
public:
	Test()
	{
	}
private:
	int m_a = 0;  //默认值
	int m_b = 0;
};

class Stu
{
	friend void fun(const Test &t, const Stu &s);
public:
	int m_x = 0;
	int m_y = 0;;
};

 void fun(const Test &t, const Stu &s)
{}

void main()
{
	Test t;
}

/*
void show()
{}

class Test
{
	
public:
	Test()
	{
		m_count++;
	}
	~Test()
	{
		m_count--;
	}
public:
	friend void fun(const Test &t); //没有this
public:
	static int GetCount()  //成员
	{
		return m_count;
	}
private:
	int m_data;
	static int m_count; //
};

int Test::m_count = 0;

void main()
{
	Test t1;

	{
		Test t2;
		Test t3;
		cout<<"count = "<<Test::GetCount()<<endl;
	}

	cout<<"count = "<<Test::GetCount()<<endl;
}

/*
class Test
{
public:
	Test():m_data(0)
	{}
public:
	// this   Test * const this
	void fun()
	{
		m_data = 1;
		m_value = 10;
		print();
		show();
	}
	static void show()  // 没有this  static int add(int a, int b)
	{
		//m_data = 10;
		m_value = 100;
		//fun();
	}

	//const Test * const this
	void print()const
	{
		cout<<"This print()"<<endl;
		//fun(this);
	}
private:
	int m_data;
public:
	static int m_value; //不属于某一个对象,属于整个类,所有对象共享
};

int Test::m_value = 0;

void main()
{
	Test t1;
	Test t2;
	cout<<t1.m_value<<endl;
	t2.m_value = 100;
	cout<<t1.m_value<<endl;

	t2.fun();
	//t2.show();
	//t1.show();
	Test::show();
}

/*
class A
{
public:
	A(int a): _a2(_a1),_a1(a)	
	{}
	void Print() 
	{
		cout << _a1 << " " << _a2 << endl;
	}
private:
	int _a1;
	int _a2;
	
};

int main() 
{
	A aa(1);
	aa.Print();
}

/*
class Date
{
public:
	Date(int y, int m, int d):m_month(m),m_year(y),m_day(d),ref(m_year),
		c_value(100)
	{
		//ref = m_year;

	}
private:
	int m_year;
	int m_month;
	int m_day;
	int &ref;
	const int c_value;
};

void main()
{
	Date dt(2021, 3, 20);
}

/*
class String
{
public:
	String(const char *str = "")
	{
		m_data = (char *)malloc(sizeof(char) * (strlen(str)+1));
		strcpy(m_data, str);
	}
	String(const String &s)
	{
		m_data = (char *)malloc(sizeof(char) * (strlen(s.m_data)+1));
		strcpy(m_data, s.m_data);
		//m_data = s.m_data;
	}
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			free(m_data);

			m_data = (char *)malloc(sizeof(char) * (strlen(s.m_data)+1));
			strcpy(m_data, s.m_data);
		}
		return *this;
	}
	~String()
	{
		free(m_data);
		m_data = nullptr;
	}
public:
	int length()const
	{
		return strlen(m_data);
	}
public:
	friend ostream& operator<<(ostream &out, const String &s);
	String operator+(const String &s);    //s = s1 + s2;
	String& operator+=(const String &s);  //s1 += s2;
	char operator[](int pos)
	{
		assert(pos>=0 && pos<length());
		return m_data[pos];
	}
	char operator[](int pos)const
	{
		assert(pos>=0 && pos<length());
		return m_data[pos];
	}

private:
	char *m_data;
};

void  main()
{
	const String str1("abc");
	String str2("xyz");
	String str;
	//str = str1 + str;  //abcxyz
	//str1 += str;
	cout<<str1[0]<<endl;

	char *pstr = "ABCXYZ";
	cout<<*(pstr+1)<<endl;
	cout<<pstr[1]<<endl;    //*(pstr+1)
}

/*
class Date
{
	friend ostream& operator<<(ostream &out, const Date &d);
public:
	//判断是否闰年
	bool IsLeap(int year)
	{return ((year%4==0&&year%100!=0) || (year%400==0));}
	// 获取某年某月的天数
	int GetMonthDay(int year, int month)
	{
		                  // 1   2   3   4   5   6   7   8   9   10  11  12
		int days[13] = { 29, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if(month==2 && IsLeap(year))
			month = 0;
		return days[month];
	}
	// 全缺省的构造函数
	Date(int year = 1900, int month = 1, int day = 1)
	{
		m_year = year;
		m_month = month;
		m_day = day;
	}
	// 拷贝构造函数
	// d2(d1)
	Date(const Date& d)
	{
		m_year = d.m_year;
		m_month = d.m_month;
		m_day = d.m_day;
	}
	// 赋值运算符重载
	// d2 = d3 -> d2.operator=(&d2, d3)
	Date& operator=(const Date& d)
	{
		if(this != &d)
		{
			m_year = d.m_year;
			m_month = d.m_month;
			m_day = d.m_day;
		}
		return *this;
	}
	// 析构函数
	~Date()
	{}
public:
	// 日期+=天数
	Date& operator+=(int n)
	{
		int mdays = GetMonthDay(m_year, m_month);
		while(m_day + n > mdays)
		{
			m_month++;
			if(m_month > 12)
			{
				m_year++;
				m_month = 1;
			}
			n -= mdays;
			mdays = GetMonthDay(m_year, m_month);
		}
		m_day += n;
		return *this;

		//*this = *this + n; 
		//return *this;
	}
	// 日期+天数
	Date operator+(int n)
	{
		Date tmp = *this;
		int mdays = GetMonthDay(tmp.m_year, tmp.m_month);
		while(tmp.m_day + n > mdays)
		{
			tmp.m_month++;
			if(tmp.m_month > 12)
			{
				tmp.m_year++;
				tmp.m_month = 1;
			}
			n -= mdays;
			mdays = GetMonthDay(tmp.m_year, tmp.m_month);
		}
		tmp.m_day += n;
		return tmp;
	}
	// 日期-天数
	Date operator-(int day);
	// 日期-=天数
	Date& operator-=(int day);
	// 前置++
	Date& operator++()
	{
		m_day++;
		int mdays = GetMonthDay(m_year, m_month);
		if(m_day > mdays)
		{
			m_day = 1;
			m_month++;
			if(m_month > 12)
			{
				m_month = 1;
				m_year++;
			}
		}
		return *this;
	}
	// 后置++
	Date operator++(int)
	{
		Date tmp = *this;
		++*this;
		return tmp;
	}
	// 后置--
	Date operator--(int);
	// 前置--
	Date& operator--();
	// >运算符重载
	bool operator>(const Date& d)
	{
		if((m_year > d.m_year)
		   || (m_year==d.m_year && m_month>d.m_month)
		   || (m_year==d.m_year && m_month==d.m_month && m_day>d.m_day))
			return true;
		return false;
	}
	// ==运算符重载
	bool operator==(const Date& d)
	{
		return (m_year==d.m_year && m_month==d.m_month && m_day==d.m_day);
	}
	// >=运算符重载
	inline bool operator >= (const Date& d)
	{
		return !(*this < d);
	}
	// <运算符重载
	bool operator < (const Date& d)
	{
		if((m_year < d.m_year)
		   || (m_year==d.m_year && m_month<d.m_month)
		   || (m_year==d.m_year && m_month==d.m_month && m_day<d.m_day))
			return true;
		return false;
	}
	// <=运算符重载
	bool operator <= (const Date& d)
	{
		return !(*this > d);
	}
	// !=运算符重载
	bool operator != (const Date& d)
	{
		return !(*this==d);
	}
	// 日期-日期 返回天数
	int operator-(const Date& d);
public:
	int GetDayByYMD(int year, int month, int day)
	{
		int days = 0;
		for(int i=1; i<month; ++i)
		{
			days += GetMonthDay(year, i);
		}
		days += day;
		return days;
	}
	int GetWeekByYMD(int year, int month, int day)
	{
		return 0;
	}
private:
	int m_year;
	int m_month;
	int m_day;
};

ostream& operator<<(ostream &out, const Date &d)
{
	out<<d.m_year<<"-"<<d.m_month<<"-"<<d.m_day;
	return out;
}

void main()
{
	Date dt1(2021, 3, 20);
	Date dt = dt1 + 1200;
	cout<<dt<<endl;
	cout<<dt1<<endl;
}

/*
void main()
{
	Date dt1(2021, 3, 20);
	Date dt2(2021, 3, 20);

	if(dt1 == dt2)
		cout<<"Equal"<<endl;
	else if(dt1 > dt2)
		cout<<"dt1 > dt2"<<endl;
	else 
		cout<<"dt1 < dt2"<<endl;

}
*/

/*
class String
{
public:
	String(const char *str = "")
	{
		m_data = (char *)malloc(sizeof(char) * (strlen(str)+1));
		strcpy(m_data, str);
	}
	String(const String &s)
	{
		m_data = (char *)malloc(sizeof(char) * (strlen(s.m_data)+1));
		strcpy(m_data, s.m_data);
		//m_data = s.m_data;
	}
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			free(m_data);

			m_data = (char *)malloc(sizeof(char) * (strlen(s.m_data)+1));
			strcpy(m_data, s.m_data);
		}
		return *this;
	}
	~String()
	{
		free(m_data);
		m_data = nullptr;
	}
public:
	friend ostream& operator<<(ostream &out, const String &s);

private:
	char *m_data;
};

void  main()
{
	String str1("abc");
	String str2("xyz");
	String str;
	//str = str1 + str;  //abcxyz
	str1 += str;
}
*/