#include<iostream>
#include<algorithm>
#include<functional>
#include<string>
#include<thread>
#include<mutex>
#include<atomic>
using namespace std;


double Division(int a, int b)
{
	// 当b == 0时抛出异常
	if (b == 0)
	{
		throw string("Division by zero condition!");
	}
	return (double)a / (double)b;
}
void Func()
{
	int* array = new int[10];
	try 
	{
		int len, time;
		cin >> len >> time;
		cout << Division(len, time) << endl;
	}
	catch (...)
	{
		cout << "delete []" << array << endl;
		delete[] array;
		throw; //重新抛出
	}
	// ...
	cout << "delete []" << array << endl;
	delete[] array;
}
int main()
{
	try
	{
		Func();
	}
	catch (const string &s)
	{
		//cout << errmsg << endl;
		cout<<s<<endl;
	}
	return 0;
}


/*
template<typename T>
class pushOnFull
{ 
	T _value;
public:
	pushOnFull(T i)
	{
		_value=i;
	}
	T value()
	{
		return _value;
	}
	void print()
	{
		cerr<<"栈满，"<<value()<<"未压入栈"<<endl;
	}
};

template<typename T>
class popOnEmpty
{
public:
	void print(){cerr<<"栈已空，无法出栈"<<endl;}
};


template<typename T>
class Stack
{
	int top;                                    //栈顶指针（下标）
	T *elements;                               //动态建立的数值
	int maxSize;                               //栈最大允纳的元素个数
public:
	Stack(int sz=10)
	{
		top = -1;
		maxSize = sz;
		elements = new T[sz];
	}
	~Stack()
	{
		delete[] elements;
	}
	void Push(const T &data)
	{
		if(IsFull())
		{
			//自定义异常类
			throw pushOnFull<T>(data);
		}
		elements[++top] = data;
	}
	T Pop() 
	{
		if(IsEmpty())
		{
			throw popOnEmpty<T>();
		}
		T value = elements[top];
		top--;
		return value;
	}
	
	void MakeEmpty()
	{
		top= -1;
	}                  //清空栈
	bool IsEmpty() const
	{
		return top== -1;
	}          //判栈空
	bool IsFull() const
	{
		return top==maxSize-1;
	}      //判栈满
	void PrintStack();                            //输出栈内所有数据
};

void main()
{
	Stack<int> st;
	try
	{
		for(int i=0; i<10; ++i)
			st.Push(i);
	}
	catch( pushOnFull<int> &e)
	{
		e.print();
	}

	try
	{
		for(int i=0; i<=10; ++i)
			st.Pop();
	}
	catch( popOnEmpty<int> &e)
	{
		e.print();
	}
}

/*
void Out_Of_Memory()
{
	cout<<"Out_Of_Memory"<<endl;
	exit(1);
}


void main()
{
	//set_new_handler(Out_Of_Memory);
	int *p;
	try
	{
		p = new int[536870911];
	}
	catch(const bad_alloc & e)
	{
		cout<<e.what()<<endl;
		return;
	}
	
	delete []p;
	cout<<"Main End."<<endl;
}

/*
#define DefaultArraySize 8

template<typename elemType>
class Array
{
	int        size;	
	elemType * ia ;
public:
	explicit Array(int sz=DefaultArraySize)
	{
		size = sz;
		ia = new elemType [size];	
	}
	~ Array()
	{
		delete [] ia;
	}
	elemType & operator[](int ix) const
	{ 
		if(ix<0||ix>=size)
		{ 
			string eObj="out_of_range error in Array<elemType >::operator[]()";
			throw out_of_range(eObj);	
		}
		return  ia[ix];
	}
};

void main()
{
	Array<int> ar(10);
	try
	{
		for(int i=0; i<=10; ++i)
			cout<<ar[i]<<" ";
		cout<<endl;
	}
	catch(const out_of_range &exp)
	{
		cout<<exp.what()<<endl;
	}
}

/*
double Division(int a, int b)
{
	// 当b == 0时抛出异常
	if (b == 0)
	{
		throw string("Division by zero condition!");
	}
	return (double)a / (double)b;
}
void Func()
{
	int* array = new int[10];
	try 
	{
		int len, time;
		cin >> len >> time;
		cout << Division(len, time) << endl;
	}
	catch (...)
	{
		cout << "delete []" << array << endl;
		delete[] array;
		throw; //重新抛出
	}
	// ...
	cout << "delete []" << array << endl;
	delete[] array;
}
int main()
{
	try
	{
		Func();
	}
	catch (const string &s)
	{
		//cout << errmsg << endl;
		cout<<s<<endl;
	}
	return 0;
}

/*
//异常规划
int Div(int a, int b)throw(int,char,double)
{
	double c=1.0;
	if(b == 0) //异常发生
	{
		throw c;
	}
	return a / b;
}
void main()
{
	try
	{
		cout<<Div(10, 0)<<endl;
	}
	
	catch(char) //按类型捕获
	{
		cout<<"你看着办."<<endl;
	}
	catch(int)
	{
		cout<<"喝的高兴."<<endl;
	}
	catch(...)  //default
	{
		cout<<"有我担着."<<endl;
	}

}

/*
int Div(int a, int b)
{
	if(b == 0)
	{
		cout<<"除数为0，发生错误."<<endl;
		return 0;
	}
	return a / b;
}

void main()
{
	cout<<Div(10, 0)<<endl;
}

/*
mutex g_lock;
int number = 0;

int ThreadProc1()
{
	for (int i = 0; i < 10000000; i++)
	{
		//g_lock.lock();

		//lock_guard<mutex> lock(g_lock);
		unique_lock<mutex> lock(g_lock);
		++number;

		//g_lock.unlock();

	}
	return 0;
}

int ThreadProc2()
{
	for (int i = 0; i < 10000000; i++)
	{
		//g_lock.lock();
		//lock_guard<mutex> lock(g_lock);
		unique_lock<mutex> lock(g_lock);
		--number;
		//g_lock.unlock();
	
	}
	return 0;
}

int main()
{
	thread t1(ThreadProc1);
	thread t2(ThreadProc2);
	t1.join();
	t2.join();

	cout << "number:" << number << endl;
	return 0;
}

/*
atomic_uint sum = {0};

void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		sum++;
		//printf("sum = %d\n", sum);
	}
}
int main()
{
	cout << "Before joining,sum = " << sum << std::endl;

	thread t1(fun, 10000000);
	thread t2(fun, 10000000);

	t1.join();
	t2.join();
	
	cout << "After joining,sum = " << sum << std::endl;
	return 0;
}

/*
mutex g_lock;

int number = 0;

int ThreadProc1()
{
	for (int i = 0; i < 10000; i++)
	{
		++number;
		//cout << "thread 1 []:" << number << endl;
		printf("thread 1 [%d]: %d\n",i, number);
	}
	return 0;
}

int ThreadProc2()
{
	for (int i = 0; i < 10000; i++)
	{
		--number;
		//cout << "thread 2 :" << number << endl;
		printf("thread 2 [%d]: %d\n",i, number);
	}
	return 0;
}

int main()
{
	thread t1(ThreadProc1);
	thread t2(ThreadProc2);
	t1.join();
	t2.join();

	cout << "number:" << number << endl;
	return 0;
}

/*
//共享数据

atomic_uint sum = {0};

void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		sum++;
	}
}
int main()
{
	cout << "Before joining,sum = " << sum << std::endl;

	thread t1(fun, 10000000);
	thread t2(fun, 10000000);

	t1.join();
	t2.join();
	
	cout << "After joining,sum = " << sum << std::endl;
	return 0;
}


/*
mutex t;
unsigned long sum = 0L;

void fun(size_t num)
{
	for (size_t i = 0; i < num; ++i)
	{
		t.lock();
		sum++;
		t.unlock();
	}
}
int main()
{
	cout << "Before joining,sum = " << sum << std::endl;

	thread t1(fun, 10000000);
	thread t2(fun, 10000000);

	t1.join();
	t2.join();
	
	cout << "After joining,sum = " << sum << std::endl;
	return 0;
}

/*
void ThreadFunc() 
{
	cout << "ThreadFunc()" << endl; 
}

void main()
{
	thread* th_ar[3];
	for(int i=0; i<3; ++i) //
	{
		th_ar[i] = new thread(ThreadFunc);
	}

	for(int i=0; i<3; ++i)
	{
		th_ar[i]->join();
	}
}

/*
void main()
{
	//thread th1(ThreadFunc);
	//thread th2(ThreadFunc);
	//thread th3(ThreadFunc);

	thread *ar = new thread[3];
	for(int i=0; i<3; ++i)
		ar[i].

	th1.join();
	th2.join();
	th3.join();
}

/*
void ThreadFunc() 
{
	for(;;)
		cout << "ThreadFunc()" << endl; 
}

int main()
{
	thread t(ThreadFunc);
	t.detach();

	return 0;
}

/*
class mythread
{
public:
	explicit mythread(thread &t) :m_t(t)
	{}
	~mythread()
	{
		if (m_t.joinable())
			m_t.join();
	}
	mythread(mythread const&) = delete;
	mythread& operator=(const mythread &) = delete;
private:
	thread &m_t;
};

void ThreadFunc() 
{
	cout << "ThreadFunc()" << endl; 
}
bool DoSomething() 
{ 
	return false; 
}
int main()
{
	thread t(ThreadFunc);
	mythread myth(t);  //

	if (!DoSomething())
		return -1;

	//t.join();
	return 0;
}

/*
void ThreadFunc()
{
	cout << "ThreadFunc()" << endl;
}
void Test1() { throw 1; }

void Test2()
{
	int* p = new int[10];
	std::thread t(ThreadFunc);
	try
	{
		Test1();
	}
	catch (...)
	{
		delete[] p;
		throw;
	}
	t.join();
}

/*
void ThreadFunc() 
{
	cout << "ThreadFunc()" << endl; 
}
bool DoSomething() 
{ 
	return false; 
}
int main()
{
	thread t(ThreadFunc);

	if (!DoSomething())
		return -1;

	t.join();
	return 0;
}

/*
class Test
{
public:
	void test_fun()
	{
		cout<<"This Test::fun()"<<endl;
	}
public:
	int m_a = 10;
};
void main()
{
	Test t;
	thread th(&Test::test_fun,  &t);
	th.join();
}

/*
class love
{
public:
    void saylove(string name);
    static void sayloveyou();
};

void love::saylove(string name)
{
    cout<<"I love "<<name<<"!"<<endl;
}

void love::sayloveyou()
{
    cout<<"I love you!"<<endl;
}

int main()
{
    love loveadapter;
    thread t0(&love::sayloveyou);
    t0.join();

    thread t1(&love::saylove, loveadapter, "one");//传对象可以
    t1.join();
    thread t2(&love::saylove, &loveadapter, "two");//传指针也行
    t2.join();
    thread t3(bind(&love::saylove, loveadapter, "three"));//bind里传对象可以
    t3.join();
    thread t4(bind(&love::saylove, &loveadapter, "four"));//bind里传指针也行
    t4.join();
    return 0;
}

/*
class Test
{
public:
	void fun()
	{
		cout<<"This Test::fun()"<<endl;
	}
public:
	int m_a = 10;
};

void thread_fun(void(*pfun)())
{
	//cout<<"in fun a = "<<a<<endl;
	//pfun();
}

void main()
{
	Test t;
	thread th(thread_fun,  &Test::fun);
	th.join();
}

/*
void main()
{
	int a = 10;
	thread th(thread_fun, ref(a));

	th.join();

	cout<<"a = "<<a<<endl;
}

/*
void thread_fun(int *a)
{
	*a += 10;
	cout<<"in fun a = "<<*a<<endl;
}

void main()
{
	int a = 10;
	thread th(thread_fun, &a);

	th.join();

	cout<<"a = "<<a<<endl;
}

/*
void thread_fun(int a)
{
	a += 10;
	cout<<"in fun a = "<<a<<endl;
}

void main()
{
	int a = 10;
	thread th(thread_fun, a);

	th.join();

	cout<<"a = "<<a<<endl;
}

/*
void thread_fun()
{
	//cout<<"Hello Thread."<<endl;
}

void main()
{
	thread th(thread_fun);
	th.detach();

	if(th.joinable())
	{
		cout<<"th jion able."<<endl;
		//th.join();
	}
	else
		cout<<"Error"<<endl;
}

/*
void thread_fun()
{
	cout<<"Hello Thread."<<endl;
}

void main()
{
	thread th(thread_fun); //函数指针

	thread th1 = move(th);

	th1.join();


}

/*
struct ThreadObj
{
	void operator()()
	{
		cout<<"Hello Thread Object."<<endl;
	}
};

void main()
{
	thread th(thread_fun); //函数指针
	th.join();

	thread th1([]{cout<<"Hello Thread Lambda."<<endl;}); //表达式
	th1.join();

	ThreadObj thobj;
	thread th2(thobj);
	th2.join();
}

/*
void main()
{
	thread th;
	thread::id id = th.get_id();
	cout<<"id = "<<id<<endl;
}

/*
void thread_fun()
{
	cout<<"thread id = "<<this_thread::get_id()<<endl;
}

void main()
{
	cout<<"Main thread id = "<<this_thread::get_id()<<endl;
	thread th(thread_fun);
	th.detach();
	cout<<"child thread id = "<<th.get_id()<<endl;
	//th.join();
}
/*
void thread_fun()
{
	cout<<"thread id = "<<this_thread::get_id()<<endl;
}

void main()
{
	cout<<"Main thread id = "<<this_thread::get_id()<<endl;
	thread th(thread_fun);
	cout<<"child thread id = "<<th.get_id()<<endl;
	th.join();
}

/*
thread::id main_thread_id = this_thread::get_id();

void is_main_thread()
{
	if (main_thread_id == this_thread::get_id())
		cout << "This is the main thread.\n";
	else
		cout << "This is not the main thread.\n";
}

int main()
{
	is_main_thread();
	thread th(is_main_thread);
	th.join();
}

/*
void thread_fun()
{
	cout<<"thread id = "<<
}

void main()
{
	thread th[10];
	for(int i=0; i<10; ++i)
		thread th[i](thread_fun, &)
}

/*
struct Test
{	
	int a;
	double b;
	char c;
};

struct Student
{
	char name[10];
	int age;
};

struct Data
{
	int data;
	Test test_data;
	Student stu_data;
};

void thread_fun(struct Data *pdt)
{
	for(int i=0; i<pdt->data; ++i)
	{
		cout<<"This is Child Thread."<<endl; //
	}
	cout<<pdt->stu_data.name<<" : "<<pdt->stu_data.age<<endl;
}



void main()
{
	int n = 3;
	Test t = {10, 12.34, 'A'};
	Student s = {"bit", 10};
	Data dt = {n, t, s};

	thread th(thread_fun, &dt);
	for(int i=0; i<10; ++i)
	{
		cout<<"This is Main Thread."<<endl; //10
	}
	th.join();
}

/*
void main()
{
	auto f1 = []{cout<<"Hello Hello."<<endl;}; //匿名对象
	auto f2 = []{cout<<"Hello Hello."<<endl;};

	f1();
	f2();

	//f2 = f1;
	void(*pfun)();
	pfun = f1;
	pfun();
}

/*
class Test
{
public:
	int fun(int x, int y)
	{
		auto f =  [this](int x, int y)->int
		{
			return m_a + m_b + x + y;
		};
		return f(x, y);
	}
private:
	int m_a = 1;
	int m_b = 2;
};

void main()
{
	Test t;
	cout<<t.fun(10,20)<<endl;
}

/*
void main()
{
	int x = 10;
	int y = 20;

	auto f1 = [=](int a, int b)mutable->int
	{
		//a = 100;
		b = 200;
		x = 100;
		return a+b+x+y;
	};

	int b = 2;
	cout<<f1(1,b)<<endl;
	cout<<"x = "<<x<<endl;
	cout<<"b = "<<b<<endl;
}

/*
int a = 1;
int b = 2;

int fun(int &x)
{
	return a + b;
}

void main()
{
	cout<<fun()<<endl;
	int x = 10;
	int y = 20;

	auto f1 = [x, y] //捕获
	{
		return a+b+x+y;
	};

	cout<<f1()<<endl;
}

/*
void main()
{
	auto f1 = [](int a, int b)->int{return a+b;};
	cout<<typeid(f1).name()<<endl;
	cout<<f1(10,20)<<endl;

	auto f2 = []{cout<<"Hello Lambda."<<endl;};
	f2();
}


/*
void main()
{
	//[]捕获块
	//()参数列表
	//->返回值
	//{}函数体
	[]()->void{}; //最基本的lambda  //匿名函数对象
}

/*
struct Goods
{
	string _name;
	double _price;
};

int main()
{
	Goods gds[] = 
	{
		{ "苹果", 2.1 }, 
		{ "相交", 3 }, 
		{ "橙子", 2.2 }, 
		{ "菠萝", 1.5 }
	};
	int n = sizeof(gds) / sizeof(gds[0]);
	sort(gds, gds+n, [](const struct Goods &g1, 
						const struct Goods &g2)->bool
	{return g1._price < g2._price;});
	return 0;
}

/*
struct Goods_Less
{
	bool operator()(const struct Goods &g1, const struct Goods &g2)
	{
		return g1._price < g2._price;
	}
};

struct Goods_Greater
{
	bool operator()(const struct Goods &g1, const struct Goods &g2)
	{
		return g1._price > g2._price;
	}
};


int main()
{
	Goods gds[] = 
	{
		{ "苹果", 2.1 }, 
		{ "相交", 3 }, 
		{ "橙子", 2.2 }, 
		{ "菠萝", 1.5 }
	};
	int n = sizeof(gds) / sizeof(gds[0]);
	sort(gds, gds+n, Goods_Greater());
	return 0;
}

/*
int main()
{
	int array[] = { 4, 1, 8, 5, 3, 7, 0, 9, 2, 6 };
	int n = sizeof(array) / sizeof(array[0]);

	for(int i=0; i<n; ++i)
		cout<<array[i]<<" ";
	cout<<endl;
	
	//sort(array, array + n);
	sort(array, array+n, greater<int>());
	
	for(int i=0; i<n; ++i)
		cout<<array[i]<<" ";
	cout<<endl;

	return 0;
}

/*
void Fun(int &x)
{
	cout << "lvalue ref" << endl;
}
void Fun(int &&x)
{
	cout << "rvalue ref" << endl;
}
void Fun(const int &x)
{
	cout << "const lvalue ref" << endl;
}
void Fun(const int &&x)
{
	cout << "const rvalue ref" << endl;
}

template<typename T>
void PerfectForward(T &&t) //const int
{
	Fun(forward<T>(t));  //forward<T>(x)
	//Fun(t);
}

void main()
{
	int a = 10;
	PerfectForward(a);

	PerfectForward(10);
	
	const int b = 20;
	PerfectForward(b);
}

/*
int main()
{
	PerfectForward(10); // rvalue ref
	int a;
	PerfectForward(a); // lvalue ref
	PerfectForward(std::move(a)); // rvalue ref
	const int b = 8;
	PerfectForward(b); // const lvalue ref
	PerfectForward(std::move(b)); // const rvalue ref
	return 0;
}

/*
class String
{
public:
	String(char* str = "")
	{
		if (nullptr == str)
			str = "";
		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}
	
	String(const String& s)
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	//右值引用 移动语义
	String(String&& s) : _str(s._str)
	{
		s._str = nullptr;
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			//异常安全
			char* pTemp = new char[strlen(s._str) + 1];
			strcpy(pTemp, s._str);
			delete[] _str;
			_str = pTemp;
		}
		return *this;
	}
	String operator+(const String& s)
	{
		char* pTemp = new char[strlen(_str) + strlen(s._str) + 1];
		strcpy(pTemp, _str);
		strcpy(pTemp + strlen(_str), s._str);
		String strRet(pTemp);
		return strRet;
	}
	~String()
	{
		if (_str)
			delete[] _str;
	}
private:
	char* _str;
};

class Person
{
public:
	Person(char* name, char* sex, int age)
		: _name(name)
		, _sex(sex)
		, _age(age)
	{}
	Person(const Person& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}
#if 0
	Person(Person&& p)
		: _name(p._name)
		, _sex(p._sex)
		, _age(p._age)
	{}
#else
	Person(Person&& p)
		: _name(move(p._name))
		, _sex(move(p._sex))
		, _age(p._age)
	{}
#endif
private:
	String _name;
	String _sex;
	int    _age;
};

Person GetTempPerson()
{
	Person p("prety", "male", 18);
	return p;
}
int main()
{
	Person p(GetTempPerson());
	return 0;
}

/*
int main()
{
	String s1("hello world");
	String s2(move(s1));
	String s3(s2);
	return 0;
}

/*
void main()
{
	String s1("hello");
	String s2 = move(s1);

	double d = 12.234;
	(int)d;
}

/*
int main()
{
	String s1("hello");
	String s2("world");
	String s3(s1 + s2);
	return 0;
}

/*
void main()
{
	String s1("hello");
	String s2 = s1;
}

/*
int main()
{
	String s1("hello");
	String s2("world");
	String s3(s1 + s2);
	return 0;
}

/*
int fun(int a, int b)
{
	int value = a + b;
	return value;
}

void main()
{
	int &&ret = fun(1, 2);
}


/*
void main()
{
	int a = 10;
	const int &b = a;

	a = 100;

	const int &c = 10; //右值
	int &&d = 10;
}


/*
//单例模式
class Test
{
public:
	Test(int d) : m_data(d)
	{}
	Test(const Test &) = delete;
	Test& operator=(const Test &) = delete;
private:
	//Test(const Test &);
private:
	int m_data;
};

void main()
{
	Test t(10);
	Test t1(0);
	//t1 = t;
	Test t2(1);
	Test t3(2);
}
*/