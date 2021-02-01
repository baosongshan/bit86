#include<stdio.h>
#include<assert.h>
#include<vld.h>  //检测是否有内存泄漏 F5


#define ROW 5
#define COL 5

void main()
{
	//动态
	int **pa = (int**)malloc(sizeof(int*) * ROW);
	for(int i=0; i<ROW; ++i)
	{
		pa[i] = (int *)malloc(sizeof(int) * COL);
	}

	for(int i=0; i<ROW; ++i)
	{
		for(int j=0; j<COL; ++j)
		{
			pa[i][j] = i + j;
		}
	}

	for(int i=0; i<ROW; ++i)
	{
		for(int j=0; j<COL; ++j)
		{
			printf("%d ", pa[i][j]);
		}
		printf("\n");
	}

	for(int i=0; i<ROW; ++i)
		free(pa[i]);

	free(pa);
}

/*
typedef struct ListNode
{
	int data;
	struct ListNode *next;
}ListNode;

typedef ListNode* List;

void InitList(List *head)
{
	//申请头结点
	*head = (ListNode*)malloc(sizeof(ListNode));
	(*head)->next = NULL;
}

void CreateList_Head(List *head)
{
	for(int i=1; i<=10; ++i)
	{
		ListNode *s = (ListNode*)malloc(sizeof(ListNode)); //申请节点
		assert(s != NULL);
		s->data = i;

		//头部插入节点
		s->next = (*head)->next;
		(*head)->next = s;
	}
}

void ShowList(List head)
{
	ListNode *p = head->next;
	while(p != NULL)
	{
		printf("%d-->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

void main()
{
	List mylist;
	InitList(&mylist);
	CreateList_Head(&mylist);
	ShowList(mylist);
}

/*
void InitList(List *head)
{
	*head = NULL;
}

void CreateList_Head(List *head)
{
	for(int i=1; i<=10; ++i)
	{
		ListNode *s = (ListNode*)malloc(sizeof(ListNode)); //申请节点
		assert(s != NULL);
		s->data = i;

		//头部插入节点
		s->next = *head;
		*head = s;
	}
}

void ShowList(List head)
{
	ListNode *p = head;
	while(p != NULL)
	{
		printf("%d-->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

void main()
{
	List mylist;
	InitList(&mylist);
	CreateList_Head(&mylist);
	ShowList(mylist);
}


/*
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