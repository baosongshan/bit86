#include<iostream>    //1
using namespace std;
#include<stdio.h>
#include"Test.h"

void main()
{
	int a = 10;
	int &b = a;  //引用 别名  不开辟空间  &
	&b;  //取地址

	int ar[10] = {1,2,3,4,5,6,7,8,9,10};
	int (&br)[10] = ar;

	int *p = &a;
	int *&q = p;
}

/*
int fun(int a, int b=0, int c=0)  //缺省参数  备胎
{
	return a + b + c;
}

void main()
{
	printf("result = %d\n", fun(1));
}

/*
int fun(int a=0, int b=0, int c=0)  //缺省参数  备胎
{
	return a + b + c;
}

void main()
{
	printf("result = %d\n", fun(1, 2, 3));
}



/*
namespace MySpace
{
	int fun(int a, int b)   
	{
		cout<<"AAAAAAAAAAAAAA"<<endl;
		return 0;
	}

	void fun1()
	{
		cout<<"This is MySpace::fun1()"<<endl;
	}
};

namespace YouSpace
{
	int fun(int a, int b)   
	{
		cout<<"BBBBBBBBBBBBBB"<<endl;
		return 0;
	}

	void fun1()
	{
		cout<<"This is YouSpace::fun1()"<<endl;
	}
};

////////////////////////////////////////////////////////
namespace BSS
{
	int fun(int a, int b)   
	{
		cout<<"BBBBBBBBBBBBBB"<<endl;
		return 0;
	}

	void fun1()
	{
		cout<<"This is YouSpace::fun1()"<<endl;
	}
};

using namespace YouSpace;
//using YouSpace::fun;
void main()
{
	//BSS::fun(1,2);
	fun(1,2);
	fun1();
}

/*
#define AAA

#ifdef AAA
int fun(int a, int b)   
{
	cout<<"AAAAAAAAAAAAAA"<<endl;
	return 0;
}
#else
int fun(int a, int b)   
{
	cout<<"BBBBBBBBBBBBBB"<<endl;
	return 0;
}
#endif

void main()
{
	fun(1,2);
}

/*
int fun(int a, int b)
{
	printf("This is fun(int, int).\n");
	return 0;
}

int fun(int a, int b)
{
	printf("This is fun(int, int).\n");
	return 0;
}

void main()
{
	fun(1,2);
}

/*
int fun(int a, int b)
{
	cout<<"This is fun(int, int)."<<endl;
}

double fun(int a, int b)
{
	cout<<"This is fun(int, int)."<<endl;
}

void main()
{
	fun(1,2);
}

/*
//函数的重载
void fun(char ch, double d)  _fun
{
	cout<<"This is fun(char, double)."<<endl;
	//printf("This is fun().");
}

void fun(int a, int b)    _fun
{
	cout<<"This is fun(int, int)."<<endl;
	//printf("This is fun(int).");
}

void main()
{
	fun('A', 12.34);
	fun(1,2);
}

/*
void main()
{
	cout<<"Hello World"<<endl;
}

/*
void main()
{
	char ch;
	int a;
	float f;
	cin>>ch;
	cin>>a;
	cin>>f;
}

/*
void main()
{
	char ch;
	int a;
	float f;
	scanf("%c", &ch);
	scanf("%d", &a);
	scanf("%f", &f);
}

/*
void main()
{
	char ch = 'A';
	int a = 100;
	float f = 12.34f;

	printf("ch = %c, a = %d, f = %f\n", ch, a, f);
	cout<<ch<<endl;
	cout<<a<<endl;
	cout<<f<<endl;
}


/*
#include<iostream>  //in out stream
using namespace std;  //命名空间  标准

void main()
{
	for(int i=0; i<10; ++i)
	{
		printf("Hello Cpp.\n");
	}

	for(int i=0; i<10; ++i)
	{
		printf("Hello Cpp.\n");
	}

}

/*
void main()
{
	int a = 10;
	a = 100;
	printf("hello CPP.\n");
	int b;
	b = 20;
}
*/

