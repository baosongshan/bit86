#include<iostream>
#include<vld.h>
using namespace std;

class A
{
public:
	A() { cout << "1111111111111"<< endl; }
	~A(){}
};

class B 
{
public:
	B()
	{ cout << "222222222222"<< endl; }
};
class C 
{
public:
	C() { cout << "333333333333" << endl; }
};

class D : public A, virtual public B, public C
{
public:
	D()
	{
		cout << "444444444444"<< endl;
	}

private:
	A a;
	B b;
	C c;
};

void main()
{
	D d;
}


/*
class A
{
public:
	A() { cout << "1111111111111"<< endl; }
	~A(){}
};

class B : public A
{
public:
	B()
	{ cout << "222222222222"<< endl; }
};
class C : public A
{
public:
	C() { cout << "333333333333" << endl; }
};

class D :public B, public C
{
public:
	D()
	{
		cout << "444444444444"<< endl;
	}

private:

};

void main()
{
	D d;
}

/*
class A
{
public:
	A(char *s) { cout << s << endl; }
	~A(){}
};

class B : virtual public A
{
public:
	B(char *s1, char*s2) :A(s1) 
	{ cout << s2 << endl; }
};
class C : virtual public A
{
public:
	C(char *s1, char*s2) :A(s1) { cout << s2 << endl; }
};

class D :public B, public C
{
public:
	D(char *s1, char *s2, char *s3, char *s4) :B(s1, s2), C(s1, s3), A(s1)
	{
		cout << s4 << endl;
	}
};

int main() 
{
	D *p = new D("class A", "class B", "class C", "class D");
	delete p;
	return 0;
}

/*
class Base
{
public:
	virtual void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
private:
	int m_a;
	int m_b;
};

class D : public Base
{
public :
	virtual void f() 
	{
		cout << "D::f" << endl;
	}
	void g() 
	{
		cout << "D::g" <<endl;
	}
	virtual void h() 
	{
		cout << "D::h" <<endl;
	}
};

void main()
{
	Base b1, b2;
	D d1, d2;
}

/*
class A
{
public :
	virtual inline void Eat()
	{
		cout<<"A::Eat"<<endl;
	}
};

class D : public A
{
public:
	virtual void Eat() 
	{
		cout<<"D::Eat"<<endl;
	}
};

void main()
{
	D d;
	d.Eat();
}


/*
class Base
{
public:
	void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
private:
	int m_a;
	int m_b;
};

class D : public Base
{
public :
	virtual void f() 
	{
		cout << "D::f" << endl;
	}
	void g() 
	{
		cout << "D::g" <<endl;
	}
	virtual void h() 
	{
		cout << "D::h" <<endl;
	}
};

void main()
{
	D d;
	memset(&d, 0, sizeof(d));
	Base *pb = &d;

	pb->g();
}

/*
class Base
{
public:
	virtual void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
private:
	int m_a = 0;
	int m_b = 1;
};

typedef void(*VFPTR)();

void main()
{
	Base b;
	VFPTR *vTable = (VFPTR*)*(int*)&b;

	for(int i=0; vTable[i]!=nullptr; ++i)
	{
		VFPTR pfun = vTable[i];
		pfun();
	}
}

/*
//多继承 -无虚函数覆盖
//单继承-有虚函数覆盖
class Base
{
public:
	virtual void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
};

class Base1
{
public:
	virtual void f() 
	{
		cout << "Base1::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base1::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base1::h" <<endl;
	}
};
class Base2
{
public:
	virtual void f() 
	{
		cout << "Base2::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base2::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base2::h" <<endl;
	}
};


class D : public Base, public Base1, public Base2
{
public:
	virtual void f1() 
	{
		cout << "D::f1" << endl;
	}
	virtual void g1() 
	{
		cout << "D::g1" <<endl;
	}
	virtual void h1() 
	{
		cout << "D::h1" <<endl;
	}
};

void main()
{
	D d;
}



/*
//单继承-有虚函数覆盖
class Base
{
public:
	virtual void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
};

class D : public Base
{
public:
	virtual void f() 
	{
		cout << "D::f1" << endl;
	}
	virtual void g1() 
	{
		cout << "D::g1" <<endl;
	}
	virtual void h1() 
	{
		cout << "D::h1" <<endl;
	}
};


void main()
{
	D d;
}

/*
//单继承-无虚函数覆盖
class Base
{
public:
	virtual void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
};

class D : public Base
{
public:
	virtual void f1() 
	{
		cout << "D::f1" << endl;
	}
	virtual void g1() 
	{
		cout << "D::g1" <<endl;
	}
	virtual void h1() 
	{
		cout << "D::h1" <<endl;
	}
};


void main()
{
	D d;
}


/*
class Base
{
public:
	virtual void f() 
	{
		cout << "Base::f" << endl;
	}
	virtual void g() 
	{
		cout << "Base::g" <<endl;
	}
	virtual void h() 
	{
		cout << "Base::h" <<endl;
	}
private:
	int m_a = 0;
	int m_b = 1;
};

typedef void(*pFun)();

void main()
{
	Base b;
	//cout<<"对象的地址："<<&b<<endl;
	printf("对象的地址：0x%p\n", &b);
	printf("虚表的地址：0x%p\n", *(int*)&b);
	//cout<<hex<<"虚表的地址："<<*(int*)&b<<endl;

	
	pFun pfun;
	pfun = (pFun)(*((int*)(*(int*)&b) + 0));
	pfun();

	pfun = (pFun)(*((int*)(*(int*)&b) + 1));
	pfun();

	pfun = (pFun)(*((int*)(*(int*)&b) + 2));
	pfun();
	
}


/*
//抽象类型
class A
{
public:
	//接口
	virtual void Eat() = 0;  //纯虚函数
	virtual void Sleep() = 0;
	virtual void Foot() = 0;

};

class Dog : public A
{
public:
	virtual void Eat()
	{
		cout<<"Dog::Eat()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"Dog::Sleep()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"Dog::Foot()"<<endl;
	}
};

class Pig : public A
{
public:
	virtual void Eat()
	{
		cout<<"Pig::Eat()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"Pig::Sleep()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"Pig::Foot()"<<endl;
	}
};

class Bird : public A
{
public:
	virtual void Eat()
	{
		cout<<"Bird::Eat()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"Bird::Sleep()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"Bird::Foot()"<<endl;
	}
	virtual void Fly()
	{
		cout<<"Bird::Fly()"<<endl;
	}
};

class TN : public Bird
{
private:
	virtual void Fly();
};

//////////////////////////////////////////////////////
//运行时的动态
void Active(A *pa)
{
	pa->Eat();
	pa->Foot();
	pa->Sleep();
}

void main()
{
	//A a;
	Dog dog;
	Pig pig;
	Bird b;
	Active(&b);

	TN t;
	t.Fly();
}

/*
class A
{
public:
	virtual void Eat()
	{
		cout<<"A::Eat()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"A::Sleep()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"A::Foot()"<<endl;
	}
};

class Dog : public A
{
public:
	virtual void Eat()
	{
		cout<<"Dog::Eat()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"Dog::Sleep()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"Dog::Foot()"<<endl;
	}
};

class Pig : public A
{
public:
	virtual void Eat()
	{
		cout<<"Pig::Eat()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"Pig::Sleep()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"Pig::Foot()"<<endl;
	}
};

//////////////////////////////////////////////////////
//运行时的动态
void Active(A *pa)
{
	pa->Eat();
	pa->Foot();
	pa->Sleep();
}

void main()
{
	A a;
	Dog dog;
	Pig pig;
	Active(&pig);
}

/*
class Base
{
public:
	virtual void Func1()
	{
		cout << "Base::Func1()" << endl;
	}
	virtual void Func2()
	{
		cout << "Base::Func2()" << endl;
	}
	void Func3()
	{
		cout << "Base::Func3()" << endl;
	}
private:
	int _b = 1;
};

class Derive : public Base
{
public:
	virtual void Func1()
	{
		cout << "Derive::Func1()" << endl;
	}

	virtual void Func4()
	{
		cout << "D::Func3()" << endl;
	}
private:
	int _d = 2;
};
int main()
{
	Base b;

	Derive d;

	return 0;
}

/*
class Base
{
public:
	virtual void Func1()
	{
		cout << "Func1()" << endl;
	}
	virtual void Func2()
	{
		cout << "Func2()" << endl;
	}
private:
	int _b = 1;
};

void main()
{
	cout<<sizeof(Base)<<endl;
	Base b;
}

/*
//继承 代码复用的重要手段
//实现多态
class Base
{
public:
	Base()
	{
		cout<<"Base::Base()"<<endl;
		m_value = new char[10];
	}
	virtual ~Base()
	{
		cout<<"Base::~Base()"<<endl;
		delete []m_value;
	}
public:
	virtual void fun()//虚地址表
	{
		cout<<"Base::fun()"<<endl;
	}
	virtual void fun(int a)//虚地址表
	{
		cout<<"Base::fun(int a)"<<endl;
	}
	virtual void fun1()  //虚地址表
	{
		cout<<"Base::fun1()"<<endl;
	}
	virtual void fun2()  //虚地址表
	{
		cout<<"Base::fun2()"<<endl;
	}
private:
	char *m_value;
};
class D : public Base
{
public:
	D()
	{
		cout<<"D::D()"<<endl;
		m_data = new int[10];
	}
	~D()
	{
		cout<<"D::~D()"<<endl;
		delete  []m_data;
	}
public:
	void fun(int a, int b)
	{
		cout<<"D::fun(int a, int b)"<<endl;
	}
private:
	int *m_data;
};

void main()
{
	//D d;
	Base *pd = new D;
	delete pd;
}

/*
void main()
{
	D d;
	Base b;
	Base *pb = &d;
	pb->fun(1);
}

/*
void main()
{
	D d;
	d.fun();
	d.fun(1);
}


/*
/*
void main()
{
	D d;
	Base b;
	Base *pb = &d;
	pb->fun();
}

/*
void main()
{
	D d;
	Base *pb = &d;
	//pb->fun();

	d.fun();  //静态绑定
}
*/