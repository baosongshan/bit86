#include<iostream>
#include<string>
using namespace std;

class A
{
public:
	int m_a = 1;
};

class B :   public A  //虚基类
{
public:
	int m_b = 2;
};

class C : public A
{
public:
	int m_c = 3;
};

class D : public B, public C
{
public:
	int m_d = 4;
};

void main()
{
	D d;
	B b = d;
	C c = d;
}

/*
void main()
{
	D d;
	cout<<d.m_d<<endl;
	cout<<d.m_c<<endl;
	cout<<d.m_b<<endl;

	d.B::m_a = 100;
	d.C::m_a = 200;

	cout<<d.B::m_a<<endl;
	cout<<d.C::m_a<<endl;

	cout<<&(d.B::m_a)<<endl;
	cout<<&(d.C::m_a)<<endl;
	//cout<<d.A::m_a<<endl;
}

/*
class Person
{
public:
	Person()
	{
		++_count;
	}
protected:
	string _name; // 姓名
public:
	static int _count; // 统计人的个数。
};
int Person :: _count = 0;

class Student : public Person
{
protected:
	int _stuNum; // 学号
};

class Graduate : public Student
{
protected:
	string _seminarCourse; // 研究科目
};

void TestPerson()
{
	Student s1;
	Student s2;
	Student s3;
	Graduate s4;
	cout << " 人数 :" << Person::_count << endl;
	Student::_count = 0;
	cout << " 人数 :" << Person::_count << endl;
}

void main()
{
	TestPerson();
}

/*
class Student;
class Person
{
public:
	friend void Display(const Person& p, const Student& s);
protected:
	string _name = "bite"; // 姓名
};

class Student : public Person
{
	friend void Display(const Person& p, const Student& s);
protected:
	int _stuNum = 1000; // 学号
};

void Display(const Person& p, const Student& s)
{
	cout << p._name << endl;
	cout << s._stuNum << endl;
}

void main()
{
	Person p;
	Student s;
	Display(p, s);
}

/*
class A
{
public:
	A(int a) :m_a(a)
	{
		cout<<"A::A()"<<endl;
	}
	~A()
	{
		cout<<"A::~A()"<<endl;
	}
private:
	int m_a;
};

class B
{
public:
	B(int b) :m_b(b)
	{
		cout<<"B::B()"<<endl;
	}
	~B()
	{
		cout<<"B::~B()"<<endl;
	}
private:
	int m_b;
};

class C
{
public:
	C(int c) :m_c(c)
	{
		cout<<"C::C()"<<endl;
	}
	~C()
	{
		cout<<"C::~C()"<<endl;
	}
private:
	int m_c;
};

class D : public B, public A,  public C
{
public:
	D():C(3),A(1),B(2),a(10),b(20),c(30)
	{
		cout<<"D::D()"<<endl;
	}
	~D()
	{
		cout<<"D::~D()"<<endl;
	}
private:
	int m_d;
	B   b;
	A   a;
	C   c;
};

void main()
{
	D d;
}

/*
class Base
{
public:
	Base(int a) :m_a(a)
	{
		cout<<"Base::Base()"<<endl;
	}
	Base(const Base &b)
	{
		cout<<"Base::Base(const Base &b)"<<endl;
	}
	Base& operator=(const Base &b)
	{
		if(this != &b)
		{
			m_a = b.m_a;
		}
		return *this;
	}
	~Base()
	{
		cout<<"Base::~Base()"<<endl;
	}
private:
	int m_a;
};

class D : public Base
{
public:
	D(int d = 0) : m_d(d), Base(100)
	{
		cout<<"D::D()"<<endl;
	}
	D(const D &d) : Base(d)
	{}
	D& operator=(const D &d) 
	{
		if(this != &d)
		{
			Base::operator=(d);
			m_d = d.m_d;
		}
		return *this;
	}
	~D()
	{
		cout<<"D::~D()"<<endl;
	}
private:
	int m_d;
};

void main()
{
	D d;
	D d1 = d;
	D d2;

	d2 = d1;
}

/*
class A
{
public:
	void fun()
	{
		cout << "func()" << endl;
	}
};

class B : public A
{
public:
	void fun(int i)
	{
		A::fun();
		cout << "func(int i)->" << i << endl;
	}
};

void main()
{
	B b;
	b.fun(0);
}

/*
class Person
{
protected:
	string _name = "小李子"; // 姓名
	int _num = 111; // 身份证号
};

class Student : public Person
{
public:
	void Print()
	{
		cout << " 姓名:" << _name << endl;
		cout << " 身份证号:" << Person::_num << endl;
		cout << " 学号:" << _num << endl;
	}
protected:
	int _num = 999; // 学号
};

void main()
{
	Student s;
	s.Print();
}

/*
//赋值兼容规则
class Base
{
public:
	Base(int a = 0) :m_a(a)
	{
		//cout<<"Base::Base()"<<endl;
	}
	~Base()
	{
		//cout<<"Base::~Base()"<<endl;
	}
public:
	void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
	void fun(int a)
	{
		cout<<"Base::fun(int)"<<endl;
	}
	void list()
	{
		cout<<"Base::list()"<<endl;
	}

private:
	int m_a;
	int m_b;
	int m_c;
};

class D : public Base
{
public:
	D(int d = 0) :m_d(d)
	{
		//cout<<"D::D()"<<endl;
	}
	~D()
	{
		//cout<<"D::~D()"<<endl;
	}
public:
	void show()
	{
		cout<<"D::show()"<<endl;
	}
	//同名隐藏
	void fun()
	{
		cout<<"D::fun()"<<endl;
	}
	void fun(int a)
	{
		cout<<"D::fun(int)"<<endl;
	}
private:
	int m_d;
};

void main()
{
	D d;
	Base b;

	//Base *pb = &d;
	//pb->show();

	d.fun();
	d.fun(0);
	d.Base::fun(1);
	//d.list();
}

/*
void main()
{
	D d;
	Base b;

	//b = d;
	//b.fun();

	//Base *pb = &d;
	///pb->fun();

	//Base &rb = d;
	//rb.fun();
}

/*
void main()
{
	Base b;
	D d;
	b.fun();
	//b.show();
	d.show();
	d.fun();
}



/*
void main()
{
	D d;
	Base b;

	b = d;          //1
	Base *pb = &d;  //2
	Base &rb = d;   //3
}

/*
class Base
{
public:
	void Call_fun()
	{
		fun();
	}
private:
	void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
};

//终止父类
class D : private Base
{
public:
	void show()
	{
		Call_fun();
	}
};

class D1 : public D
{
public:
	void fun1()
	{
		//Call_fun();
	}
};

void main()
{
	D d;
	//d.Call_fun();
}

/*
//基类
class A
{
public:
	A(int a = 0) : m_a(a)
	{
		cout<<"A::A()"<<endl;
	}
public:
	void fun()
	{
		cout<<"This is A::fun()"<<endl;
	}
protected:
	void show()
	{
		cout<<"This is A::show()"<<endl;
	}
private:
	void print()
	{
		cout<<"This is A::print()"<<endl;
	}
private:
	int m_a;
};

//派生类
class D : protected A
{
public:
	D(int d = 0):m_d(d)
	{
		cout<<"D::D()"<<endl;
	}
public:
	void list()
	{
		fun();
		show();
		//print();
	}
private:
	int m_d;
};

class D1 : public D
{
public:
	void fun1()
	{
		fun();
	}
};

void main()
{
	D d;
	//d.fun();
}

/*
//基类
class A
{
public:
	A(int a = 0) : m_a(a)
	{
		cout<<"A::A()"<<endl;
	}
public:
	void fun()
	{
		cout<<"This is A::fun()"<<endl;
	}
protected:
	void show()
	{
		cout<<"This is A::show()"<<endl;
	}
private:
	void print()
	{
		cout<<"This is A::print()"<<endl;
	}
private:
	int m_a;
};

//派生类
class D : protected A
{
public:
	D(int d = 0):m_d(d)
	{
		cout<<"D::D()"<<endl;
	}
public:
	void list()
	{
		fun();
		show();
		//print();
	}
private:
	int m_d;
};

void main()
{
	D d;
	//d.fun();
}


/*
//基类
class A
{
public:
	A(int a = 0) : m_a(a)
	{
		cout<<"A::A()"<<endl;
	}
public:
	void fun()
	{
		cout<<"This is A::fun()"<<endl;
	}
protected:
	void show()
	{
		cout<<"This is A::show()"<<endl;
	}
private:
	void print()
	{
		cout<<"This is A::print()"<<endl;
	}
private:
	int m_a;
};

//派生类
class D : public A
{
public:
	D(int d = 0):m_d(d)
	{
		cout<<"D::D()"<<endl;
	}
public:
	void list()
	{
		show();
		//print();
	}
private:
	int m_d;
};

void main()
{
	//cout<<sizeof(A)<<endl;
	//cout<<sizeof(D)<<endl;
	D d;
	d.fun();
	d.list();
}

/*
class Person
{
public:
	void Print()
	{
		cout<<m_name<<" : "<<m_age<<endl;
	}
public:
	string m_name = "bite"; 
	int    m_age = 5; 
};

//继承语法
class Student : public Person
{
public:
	Student(string name, int age) : m_name(name), m_age(age)
	{}
};


void main()
{
	Student s("xxx", 20);
	s.Print();
}

/*
void main()
{
	Person p;
	p.Print();

	Student s;
	s.Print();
}
*/
