#include<stdio.h>

class CGoods
{
public:
	//�ӿ�
	void Register(char *name, int count, float price);
	void GetName(char *name);
	int GetCount();
	int GetPrice();
	int GetTotalPrice();
private:
	char m_name[10];
	int  m_count;
	float m_price;
	float m_total_price;
};

/*
class Test
{
public:
	int a;
	int x;
private:
	int y;
protected:
	int b;
private:
	int c;
};
void main()
{
	Test t;
	t.a = 100;  //����ֱ�ӷ���˽�г�Ա
	t.b = 200;  //����ֱ�ӷ��ʱ�����Ա
	t.c = 300;
}

/*
class CGoods
{
public:
	char m_name[10];
	int  m_count;
	float m_price;
	float m_total_price;
};

void main()
{
	CGoods c;  //����  struct ���� ����  class ʵ����  ����
	c.m_count = 100;
}


/*
//��
class Test
{
	int a;     //��Ա����
	double b;
	char c;

	void fun() //��Ա����
	{
		printf("This is fun().\n");
	}
};

void main()
{
	struct Test t;
}


/*
#include<iostream>
#include<time.h>
#include"Test.h"
using namespace std;

void f(int a)
{
	cout << "f(int)" << endl;
}
void f(int *p)
{
	cout << "f(int*)" << endl;
}

//C++  nullptr  NULL
void main()
{
	f(0);
	f(NULL); //ָ��
	f(nullptr);

	int *p = nullptr;
}

/*
void fun(int ar[])   //*ar  û�з�Χ
{
	for(auto &e : ar)
		cout<<e<<" ";
	cout<<endl;
}

void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	fun(ar);
}

/*
void main()
{
	int ar[] = {1,2,3,4,5,6,7,8,9,10};
	int n = sizeof(ar) / sizeof(ar[0]);

	for(int i=0; i<n; ++i)
		cout<<ar[i]<<" ";
	cout<<endl;

	for(auto e : ar)
		cout<<e<<" ";
	cout<<endl;

	for(auto &e : ar)
	{
		cout<<e<<" ";
		break;
	}
	cout<<endl;
}

/*
void fun(auto a)
{}

void main()
{
	int a = 10;
	fun(a);

}

/*
void main()
{
	int x = 10;
	auto a = &x;  //int *
	cout<<typeid(a).name()<<endl;

	auto *b = &x;   //int
	cout<<typeid(b).name()<<endl;

	auto &c = x;
	cout<<typeid(c).name()<<endl;

	int ar[10] = {0};
	//int (&br)[10] = ar;
	auto &br = ar;   //?  int[10]
	cout<<typeid(br).name()<<endl;  //int *

}

/*
struct Test
{};

void main()
{
	int a = 0;
	float f = 1.2f;
	double d = 12.34;
	Test t;

	cout<<typeid(a).name()<<endl;  //"int"
	cout<<typeid(f).name()<<endl;
	cout<<typeid(d).name()<<endl;
	cout<<typeid(t).name()<<endl;

	//auto 
	auto b = f;
	cout<<typeid(b).name()<<endl;
}

/*
void main()
{
	int res = fun(10, 20);
}

/*
void main()
{
	const int a = 1;
	//int *p = &a;
	//int **pp = &p;

	//int &ra = a;

}

/*
void main()
{
	int a = 1;
	int &ra = a;
	ra++;
	cout<<a<<endl;
	int *pa = &a;
	pa++;
}

/*
struct Test
{
	int a;
	double b;
	char c;
};

void main()
{
	Test t;

	Test &rt = t;

	Test *pt = &t;

	cout<<sizeof(t)<<endl;
	cout<<sizeof(rt)<<endl;
	cout<<sizeof(pt)<<endl;  //4
}

/*
void main()
{
	int value = 10;
	int x = 20;
	int &a = value;
	
	int *p = &value;
	p = &x;

	int &c = NULL;
	int *q = NULL;
}

/*
struct Test
{
	int ar[100000];
};

Test t;

Test fun1() //��ֵ
{
	return t;
}
Test& fun2() //������
{
	return t;
}



void TestValueTime()
{
	time_t begin = clock();
	for(int i=0; i<10000; ++i)
		fun1();
	time_t end = clock();
	cout<<"value time : "<<end-begin<<endl;
}
void TestRefTime()
{
	time_t begin = clock();
	for(int i=0; i<10000; ++i)
		fun2();
	time_t end = clock();
	cout<<"ref time : "<<end-begin<<endl;
}

void main()
{
	TestValueTime();
	TestRefTime();
}


/*
int& fun(int a, int b)
{
	static int v;
	v = a + b;
	return v;
}

int main()
{
	int &ver = fun(10, 20);
	fun(1, 2);
	cout << ver << endl;
}


/*
int& fun(int a, int b)
{
	static int v = a + b;
	return v;
}

void main()
{
	int &res = fun(10, 20);
	fun(1,2);
	cout<<"res = "<<res<<endl;
}

/*
void Swap(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void main()
{
	int a = 10;
	int b = 20;
	cout<<a<<" "<<b<<endl;
	Swap(a, b);
	cout<<a<<" "<<b<<endl;
}


/*
void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void main()
{
	int a = 10;
	int b = 20;
	cout<<a<<" "<<b<<endl;
	Swap(&a, &b);
	cout<<a<<" "<<b<<endl;
}

/*
void main()
{
	const int a = 10;
	const int &b = a;  //������

	//a = 100;
	//b = 1000;
}

/*
struct Student
{
	char name[10];
	int age;
	char sex[5];
};

void main()
{
	int a = 10; //����������
	int &b = a;

	Student stu;
	Student &rstu = stu;

	int ar[10] = {1,2,3,4,5,6,7,8,9,10};  //���������
	int (&br)[10] = ar;

	int *ptr = &a;   //ָ�������
	int *&q = ptr;
}

/*
void main()
{
	int a = 10;
	int &b = a;   
	int &c = a;
	int &e = b;

	int x = 100;
    b = x;
}

/*
void main()
{
	int a = 10;
	int &b = a;   //���ܳ��ֿ�����

	cout<<"a = "<<a<<endl;
	b = 100;
	cout<<"a = "<<a<<endl;

}

/*
extern "C" int TestFunc(int a, int b)   //_TestFunc
{
	cout << "void TestFunc(int)" << endl;
	return 0;
}
extern "C" double TestFunc(int a)  //_TestFunc
{
	cout << "void TestFunc(int)" << endl;
	return 0.0;
}
void main()
{
	int res = TestFunc(100, 200);  //������
	double res1 = TestFunc(100);
	//TestFunc();
}

/*
void fun(int a, int b=0, int c, int d=0)
{}

void main()
{
	//printf("\n");    
	std::cout<<"Hello C++"<<std::endl;  //<<��������  �����

	int val;
	std::cin>>val;   // >> ���������  ��ȡ��
}
*/