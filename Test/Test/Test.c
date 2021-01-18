#include<stdio.h>
#include<assert.h>
#include<vld.h>  //检测是否有内存泄漏 F5

void fun(int a, int b, int *v)
{
	*v = a + b;
}

void main()
{
	int a = 10;
	int b = 20;
	int v = 0;

	fun(a, b, &v);
	printf("v = %d\n", v);
}

/*
void main()
{
	malloc();
	calloc();
	realloc();
}

/*
void main()
{
	int a = 1;
	int b = 1;

	int v = a || ++b;  //短路求值

	printf("b = %d\n", b);
	printf("v = %d\n", v);
}

/*

#include"Max.h"   //头文件重复引入
#include"Test.h"



void main()
{
	int a = 10;
	int b = 20;
	int c = 100;

	int max_value = Max(a, b);
	printf("max value = %d\n", max_value);

	max_value = fun(a, b, c);
	printf("max value = %d\n", max_value);
}

/*
//void *memset( void *dest, int c, size_t count );
void main()
{
	int *p = (int*)malloc(sizeof(int) * 10);
	int *q = (int*)malloc(sizeof(int));
	//free(p);
}

/*
void main()
{
	strlen();
	strcat();
	strcpy();
	strcmp();

	memset();
	memcpy();
	memcmp();
	memmove();
}

/*
int main()
{
	int a = 0;

	//////////////////////////////////////
	assert(a != 0); //断言 预言

	printf("OK.\n");

	return 0;
}
*/