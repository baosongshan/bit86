#include<iostream>
#include<thread>
#include<mutex>
#include<windows.h>
#include<assert.h>
#include<boost/utility.hpp>
using namespace std;
using namespace boost;

class A
{
public:
	virtual void f()
	{
		cout<<"This is A::f()."<<endl;
	}
public:
	int m_a;
};
class B : public A
{
public:
	void f()
	{
		cout<<"This is B::f()."<<endl;
	}
	void h()
	{
		cout<<"Thi is B::h()"<<endl;
	}
public:
	int m_b;
};

void Active(A *pa)
{
	B *pb = dynamic_cast<B*>(pa);
	if(pb != nullptr)
	{
		pb->h();
		pb->m_b = 10;
	}
}

void main()
{
	//B b;
	A a;
	Active(&a);
}

/*
void Active(A *pa)
{
	pa->f();
	B *pb = (B*)pa;
	pb->h();
	pb->m_b = 10;
}

void main()
{
	B b;
	//A a;
	Active(&b);
}

/*
class A
{
private:
	int m_a = 1;
};
class B
{
private:
	int m_b = 2;
};

class C : public A, public B
{
private:
	int m_c = 3;
};
void main()
{
	C c;
	A *pa = &c;
	B *pb = &c;
	printf("&c=%p, pa=%p, pb=%p\n", &c, (A*)&c, (B*)&c);
	printf("&c=%p, pa=%p, pb=%p\n", &c, (A*)&c, reinterpret_cast<B*>(&c));
	
}

/*
void main()
{
	C c;
	cout<<"&c = "<<&c<<endl;

	A *pa = &c;
	cout<<"pa = "<<pa<<endl;

	B *pb = &c;
	cout<<"pb = "<<pb<<endl;
}

/*
void main()
{
	const int a = 10;
	int *pa = (int *)&a;
	int *pb = const_cast<int*>(&a);

	double *pd = (double*)&a;
	//double *pd1 = const_cast<double*>(&a);
}

/*
void main()
{
	double d = 12.34;
	int i = static_cast<int>(d);

	double *pd = &d;

	//int a = (int)pd;
	//int a = static_cast<int>(pd);   //安全性 高
	//int *pi = static_cast<int*>(pd);
}

/*
class Test : public noncopyable
{

};

void main()
{
	Test t1;
	//Test t2;
	//t2 = t1;
}

/*
template<typename T>
class LASingletonTemplateBase 
{
    private:
        static T* sm_instance;
    protected:
        LASingletonTemplateBase()
        {
            assert(sm_instance == 0);
            sm_instance = static_cast<T*>(this);
        }
        virtual ~LASingletonTemplateBase()
        {
            assert(sm_instance != 0);
            sm_instance = 0;
        }

    public:
        static T* get_instance_ptr()
        {
            if(sm_instance == 0)
            {
                sm_instance = new T();
            }
            return sm_instance;
        }

        static T& get_instance_ref()
        {
            if(sm_instance == 0)
            {
                sm_instance = new T();
            }
            return *sm_instance;
        }

        static void remove_instance()
        {
            assert(sm_instance);
            if(sm_instance)
            {
                delete sm_instance;
            }
            assert(sm_instance == 0);
        }
};
template<typename T>
T* LASingletonTemplateBase<T>::sm_instance = 0;
//////////////////////////////////////////////////////////

class Test
{};

void main()
{
	Test *pt1 = LASingletonTemplateBase<Test>::get_instance_ptr();
	Test *pt2 = LASingletonTemplateBase<Test>::get_instance_ptr();
	Test *pt3 = LASingletonTemplateBase<Test>::get_instance_ptr();

	Test &rt1 = LASingletonTemplateBase<Test>::get_instance_ref();
	Test &rt2 = LASingletonTemplateBase<Test>::get_instance_ref();
}

/*
mutex mt;
class Singleton
{
public:
	static Singleton* Instance()
	{
		//双检锁
		if(_instance == nullptr)
		{
			mt.lock();
			if(_instance == nullptr)
			{
				Sleep(100);
				_instance = new Singleton;
			}
			mt.unlock();
		}
		return _instance;
	}
protected:
	Singleton()
	{
	}
private:
	static Singleton* _instance;
};

Singleton* Singleton::_instance = nullptr;

/////////////////////////////////////////////////////

void thread_fun()
{
	//cout<<"aaaaaaaaaaaaaaa"<<endl;
	Singleton* ps = Singleton::Instance();
	cout<<ps<<endl;
}

#define N 2000

void main()
{
	thread* th[N];
	for(int i=0; i<N; ++i)
	{
		th[i] = new thread(thread_fun);
	}

	for(int i=0; i<N; ++i)
	{
		th[i]->join();
	}
}

/*
void main()
{
	Singleton *pst1 = Singleton::Instance();
	Singleton *pst2 = Singleton::Instance();
	Singleton *pst3 = Singleton::Instance();
	Singleton *pst4 = Singleton::Instance();
}

/*
//饿汉
class Singleton
{
public:
	static Singleton* GetInstance()
	{
		return &m_instance;
	}
private:
	// 构造函数私有
	Singleton(){};
	static Singleton m_instance;
private:
	int m_a;
	int m_b;
};

Singleton Singleton::m_instance; //

void main()
{
	Singleton *ps1 = Singleton::GetInstance();
	Singleton *ps2 = Singleton::GetInstance();
}

/*
class Singleton
{
public:
	static Singleton* Instance()
	{
		if(_instance == nullptr)
		{
			_instance = new Singleton;
		}
		return _instance;
	}
protected:
	Singleton()
	{
	}
private:
	static Singleton* _instance;
};

Singleton* Singleton::_instance = nullptr;

void main()
{
	Singleton *pst1 = Singleton::Instance();
	Singleton *pst2 = Singleton::Instance();
	Singleton *pst3 = Singleton::Instance();
	Singleton *pst4 = Singleton::Instance();
}

/*
class Test
{};

void main()
{
	Test t1;
	Test t2;
}

/*
class Base final
{
public:
	Base()
	{}
};

class D : public Base
{};

void main()
{
	D d;
}

/*
class Base
{
private:
	Base()
	{}
};

class D : public Base
{};

void main()
{
	D d;
}

/*
class StackOnly
{
public:
	static StackOnly CreateObject()
	{
		return StackOnly();
	}
private:
	StackOnly() {}
	StackOnly(const StackOnly &);
private:
	int m_a = 1;
	int m_b = 2;
};

void main()
{
	StackOnly obj = StackOnly::CreateObject();
}
/*
class Test
{
public:
	Test()
	{}
private:
	void* operator new(size_t sz) ;
};

void main()
{
	Test t;
	Test *pt = new Test;
}

/*
class Test
{
public:
	static Test* CreateInstance()
	{
		return new Test;
	}
private:
	Test()
	{}
};

void main()
{
	Test *pt = Test::CreateInstance();
}
*/