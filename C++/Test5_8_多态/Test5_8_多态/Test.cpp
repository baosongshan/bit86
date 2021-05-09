#include<iostream>
using namespace std;

class Base
{
public:
	void f(int x)
	{}
};

class Derived : public Base
{
public:
	void f(char *str)
	{}
};

void main()
{
	Derived d;
	d.f("abc");
	d.f(10);
}

/*
void main()
{
	Derived d;
	Base *pb = &d;
	pb->f("abc");
}


/*
class Base
{
public:
	virtual void f(float x)
	{ cout << "Base::f(float) " << x << endl; }
	void g(float x)
	{ cout << "Base::g(float) " << x << endl; }
	void h(float x)
	{ cout << "Base::h(float) " << x << endl; }
};

class Derived : public Base
{
public:
	virtual void f(float x)
	{ cout << "Derived::f(float) " << x << endl; }
	void g(int x){ cout << "Derived::g(int) " << x << endl; }
	void h(float x){ cout << "Derived::h(float) " << x << endl; }
};

void main(void)
{
	Derived d;

	Base *pb = &d;
	Derived *pd = &d;

	// Good : behavior depends solely on type of the object
	pb->f(3.14f); // Derived::f(float) 3.14
	pd->f(3.14f); // Derived::f(float) 3.14
	// Bad : behavior depends on type of the pointer
	pb->g(3.14f); // Base::g(float) 3.14
	pd->g(3.14f); // Derived::g(int) 3 (surprise!)
	// Bad : behavior depends on type of the pointer
	pb->h(3.14f); // Base::h(float) 3.14 (surprise!)
	pd->h(3.14f); // Derived::h(float) 3.14
}

/*
class Base
{
public:
	void f(int x)
	{
		cout << "Base::f(int) " << x << endl; 
	}
	void f(float x)
	{ 
		cout << "Base::f(float) " << x << endl; 
	}
	virtual void g(void)
	{
		cout << "Base::g(void)" << endl; 
	}
};

class Derived : public Base
{
public:
	virtual void g(void)
	{
		cout << "Derived::g(void)" << endl;
	}
};

void main(void)
{
	Derived d;
	Base *pb = &d;

	pb->f(42);
	pb->f(3.14f);
	pb->g();
}

/*
class Base
{
public:
	Base()
	{
		cout<<"Base::Base()"<<endl;
	}
public:
	virtual void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
	void fun(int a)
	{}
	virtual void list(int a)
	{
		cout<<"Base::list()"<<endl;
	}
	void print()
	{
		cout<<"Base::print()"<<endl;
	}
private:
	int m_base = 1;
};

class D : public Base
{
public:
	D()
	{
		cout<<"D::D()"<<endl;
	}
public:
	virtual void fun()
	{
		cout<<"D::fun()"<<endl;
	}
	virtual void fun(int a)
	{
		cout<<"D::fun()"<<endl;
	}
	virtual void show()
	{
		cout<<"D::show()"<<endl;
	}
private:
	int m_d = 2;
};


void main()
{
	D d;
	//cout<<<<endl;
}


/*
class Car
{
public:
	virtual void Drive() {}
};
class Benz :public Car
{
public:
	virtual void Drive()override { cout << "Benz-舒适" << endl; }
	virtual void Drive(int a) { cout << "Benz-舒适" << endl; }
	virtual void Drive(int a, int b) { cout << "Benz-舒适" << endl; }
};

void main()
{
	Car *pc = new Benz;
	pc->Drive();
}

/*
class Base
{
public:
	Base()
	{
		cout<<"Base::Base()"<<endl;
		this->fun(); //虚机制在构造函数不起作用
	}
	virtual ~Base()
	{
		cout<<"Base;:~Base()"<<endl;
	}
public:
	void list()
	{
		fun();
	}
	virtual void fun()   //虚函数  贼
	{
		cout<<"Base::fun()"<<endl;
	}
private:
	int m_a = 0;
};

class D : public Base
{
public:
	D()
	{
		cout<<"D::D()"<<endl;
	}
	~D()
	{
		cout<<"D::~D()"<<endl;
	}
public:
	virtual void fun()
	{
		cout<<"D::fun()"<<endl;
	}

private:
	int m_b = 0;
};

void main()
{
	D d;
	d.list();
}


/*
void main()
{
	Base *pb = new D;
	delete pb;

	//D *pd = new D;
	//delete pd;
}

/*
class Base
{
public:
	virtual int* fun()   //虚函数  贼
	{
		static int a = 10;
		cout<<"Base::fun()"<<endl;
		return &a;
	}
private:
	int m_a = 0;
};

class D : public Base
{
public:
	virtual double* fun()
	{
		static double d = 12.34;
		cout<<"D::fun()"<<endl;
		return &d;
	}

private:
	int m_a = 0;
};

void main()
{
	Base *pb = new D;
	pb->fun();
}

/*
class C : public D
{
public:
	void fun()
	{
		cout<<"C::fun()"<<endl;
	}
	void fun(int a)
	{
		cout<<"C::fun(int)"<<endl;
	}
};

void main()
{
	D *pd = new C;
	pd->fun();
	pd->fun(1);
}

/*
void main()
{
	Base *pb = new D;
	pb->fun();
	pb->fun1();
}

/*
void main()
{
	Base *pb = new D;
	pb->fun();

	Base *pb1 = new D1;
	pb1->fun();
}

/*
class Base
{
public:
	virtual void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
};

class D : public Base
{
public:
	//重写
	void fun()
	{
		cout<<"D::fun()"<<endl;
	}
};

void main()
{
	Base *pb = new D;
	pb->fun(1);
}

/*
void main()
{
	D d;
	Base &rb = d;
	rb.fun();
}

/*
void main()
{
	D d;
	Base b = d;
	b.fun();
}

/*
void main()
{
	D d;
	Base *pb = &d;
	pb->fun();
}

/*
class A
{
public:
	virtual void Eat()
	{
		cout<<"A::Eat()"<<endl;
	}
	virtual void Foot()
	{
		cout<<"A::Foot()"<<endl;
	}
	virtual void Sleep()
	{
		cout<<"A::Sleep()"<<endl;
	}
};

class Person : public A
{
public:
	void Eat()
	{
		cout<<"Person::Eat()"<<endl;
	}
	void Foot()
	{
		cout<<"Person::Foot()"<<endl;
	}
	void Sleep()
	{
		cout<<"Person::Sleep()"<<endl;
	}
};

class Bird : public A
{
public:
	void Eat()
	{
		cout<<"Bird::Eat()"<<endl;
	}
	void Foot()
	{
		cout<<"Bird::Foot()"<<endl;
	}
	void Sleep()
	{
		cout<<"Bird::Sleep()"<<endl;
	}
};

class Dog : public A
{
public:
	void Eat()
	{
		cout<<"Dog::Eat()"<<endl;
	}
	void Foot()
	{
		cout<<"Dog::Foot()"<<endl;
	}
	void Sleep()
	{
		cout<<"Dog::Sleep()"<<endl;
	}
};

//多态  完成不同的功能
void Active(A *pa)
{
	pa->Eat();
	pa->Foot();
	pa->Sleep();
}

void main()
{
	Person p;
	Bird b;
	Dog d;

	Active(&d);
}

/*
class Car
{
private:
	Wheel two[2];
	Door  four[4];
};

/*
class Base
{
public:
	void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
private:
	int m_a = 0;
	int m_b = 0;
};

class D :public Base
{
public:
	//同名隐藏
	void fun()
	{
		cout<<"D::fun()"<<endl;
	}
	void fun(int a)
	{
		cout<<"D::fun(int)"<<endl;
	}
	void show()
	{
		cout<<"D::show()"<<endl;
	}
private:
	int m_c = 0;
};

void main()
{
	D d;
	Base *pb = &d;

	pb->fun();
	//pb->show();
	//pb->fun(1);

}

/*
class Base
{
public:
	void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
	void fun(int a)
	{
		cout<<"Base::fun(int)"<<endl;
	}
	void fun(int a, int b)
	{
		cout<<"Base::fun(int, int)"<<endl;
	}
private:
	int m_a = 0;
	int m_b = 0;
};

class D :public Base
{
public:
	//同名隐藏
	void fun(int a, int b, int c)
	{
		cout<<"D::fun(int,int,int)"<<endl;
	}
	void show()
	{
		cout<<"D::show()"<<endl;
	}
private:
	int m_c = 0;
};

void main()
{
	D d;
	Base *pb = &d;

	pb->fun();

}

/*
//赋值兼容规则  
void main()
{
	Base  b;
	D     d;

	b = d;

	Base *pb = &d;

	Base &rb = d;  //初始化
}

/*
void main()
{
	D d;
	//d.fun();
	//d.fu1n();
	//d.fun(1,2);
	d.fun(1,2,3);
}

/*
class Base
{
private:
	void fun()
	{
		cout<<"Base::fun()"<<endl;
	}
};

class D : private Base
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
*/