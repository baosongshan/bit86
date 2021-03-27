#include<iostream>
#include<assert.h>
#include"seqlist.h"
#include<list>
using namespace std;

void main()
{
	list<int> mylist;
	mylist.push_back(3);
	mylist.push_back(2);
	mylist.push_back(5);
	mylist.push_back(1);
	mylist.push_back(10);
	mylist.push_back(7);
	mylist.push_back(6);
	cout<<"list length = "<<mylist.size()<<endl;

	for(auto &e : mylist)
		cout<<e<<" ";
	cout<<endl;

	mylist.sort();

	for(auto &e : mylist)
		cout<<e<<" ";
	cout<<endl;

	mylist.reverse();
	for(auto &e : mylist)
		cout<<e<<" ";
	cout<<endl;

}


/*
void main()
{
	list<int> mylist;
	for(int i=1; i<=10; ++i)
		mylist.push_back(i);

	list<int>::iterator it = mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	list<int> mylist;
	for(int i=1; i<=10; ++i)
		mylist.push_back(i);

	for(auto &e : mylist)
		cout<<e<<"-->";
	cout<<"Over."<<endl;
}


/*
//模板不支持分离编译

void main()
{
	SeqList<int> mylist;
}

/*
//Java完全面向  class int a;

//data(int()) //零初始化

//data(Stu())

class Stu
{
public:
	Stu()
	{
		name[0] = '\0';
		age = 0;
		sex[0] = '\0';
	}
private:
	char name[10];
	int age;
	char sex[3];
};

template<class Type>
class BinTreeNode
{
public:
	BinTreeNode(BinTreeNode *left=NULL, BinTreeNode *right=NULL)
		:data(Type()), leftChild(left), rightChild(right)
	{}
private:
	Type data;
	BinTreeNode *leftChild;
	BinTreeNode *rightChild;
};

template<class Type>
class BinTree
{
private:
	BinTreeNode<Type> *root;
};

void main()
{
	BinTree<Stu> bt;
}

/*
//基于对象
class A
{};

void main()
{
	int a =    int();
	char ch =  char();
	double d = double();  //0.0000000
	float f =  float();
}

/*
//类模板
template<class Type>
class SeqList
{
public:
	SeqList(int sz = 8)
	{
		capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
		base = new Type[SEQLIST_DEFAULT_SIZE];
		assert(base != NULL);
		size = 0;
	}
	~SeqList()
	{
		delete []base;
		base = nullptr;
		capacity = size = 0;
	}
public:
	bool full()const
	{return size >= capacity;}
public:
	void push_back(const Type &x);
	//{
	//	assert(!full());
	//	base[size++] = x;
	//}
private:
	//enum{SEQLIST_DEFAULT_SIZE = 8};
	const int SEQLIST_DEFAULT_SIZE = 8; //支持类型检查
private:
	Type *base;
	size_t capacity;
	size_t size;
};

template<class Type>
void SeqList<Type>::push_back(const Type &x)
{
	assert(!full());
	base[size++] = x;
}

void main()
{
	SeqList<int> mylist(10);
	SeqList<char> youlist(5);

	SeqList<SeqList<int>> hilist;
}



/*
#define ElemType int
#define SEQLIST_DEFAULT_SIZE 8

typedef struct SeqList
{
	ElemType *base;
	size_t capacity;
	size_t size;
}SeqList;

void InitSeqList(SeqList *plist);
void DestroySeqList(SeqList *plist)
{
    free(plist->base);
	base = NULL;
}

void InitSeqList(SeqList *plist)
{
	plist->base = (ElemType*)malloc(sizeof(ElemType) * SEQLIST_DEFAULT_SIZE);
	assert(plist->base != NULL);
	plist->capacity = SEQLIST_DEFAULT_SIZE;
	plist->size = 0;
}

void main()
{
	SeqList mylist;
	InitSeqList(&mylist);
}


/*
//冗余  重复性
//模板  把类型当做参数进行传递

//函数模板  模板函数
//template<class Type>
template<typename Type>
Type Fun(Type a, Type b)
{
	Type value = a + b;
	return value;
}

void main()
{
	Fun(1,2);
	Fun(1.1, 2.2);
	Fun<int>(1, 2);

	Fun(1, 2.2);
}

/*
void  main()
{
	int a = 10;  //4
	double b = 23.45;  //8

	Fun((double)a, b);
	Fun(a, (int)b);
	Fun<int>(a, b);
}

/*
template<class Type>
void Swap(Type &a, Type &b)
{
	Type tmp = a;
	a = b; 
	b = tmp;
}

void  main()
{
	int a = 10;  //4
	double b = 23.45;  //8
	Swap(a, (int&)b);
	//Swap((double&)a, b);
	Swap<int>(a, b);
}


/*
template<class Type1, class Type2>
void Swap(Type1 &a, Type2 &b)
{
	Type1 tmp = a;
	a = b;  //int = double
	b = tmp;
}

void  main()
{
	int a = 10;
	double b = 23.45;
	Swap(a, b);
}

/*
void main()
{
	char ch1='a', ch2='b';
	cout<<"ch1 = "<<ch1<<" : ch2 = "<<ch2<<endl;
	Swap<char>(ch1, ch2);
	cout<<"ch1 = "<<ch1<<" : ch2 = "<<ch2<<endl;

	int a=10, b=20;
	cout<<"a = "<<a<<" : b = "<<b<<endl;
	Swap<int>(a, b);
	cout<<"a = "<<a<<" : b = "<<b<<endl;

	double d1=12.34, d2=23.45;
	cout<<"d1 = "<<d1<<" : d2 = "<<d2<<endl;
	Swap<double>(d1, d2);
	cout<<"d1 = "<<d1<<" : d2 = "<<d2<<endl;

}

/*
void Swap(char &a, char &b)
{
	char tmp = a;
	a = b;
	b = tmp;
}

void Swap(int &a, int &b)
{
	int tmp = a;
	a = b;
	b = tmp;
}

void Swap(double &a, double &b)
{
	double tmp = a;
	a = b;
	b = tmp;
}

void main()
{
	char ch1='a', ch2='b';
	cout<<"ch1 = "<<ch1<<" : ch2 = "<<ch2<<endl;
	Swap(ch1, ch2);
	cout<<"ch1 = "<<ch1<<" : ch2 = "<<ch2<<endl;

	int a=10, b=20;
	Swap(a, b);

	double d1=12.34, d2=23.45;
	Swap(d1, d2);
}
*/