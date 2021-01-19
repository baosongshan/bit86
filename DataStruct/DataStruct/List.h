#ifndef _LIST_H_
#define _LIST_H_

#include"Sysutil.h"

#define ElemType int

//无头单链表
typedef struct SListNode
{
	ElemType data; //数据域
	struct SListNode *next; //指针域
}SListNode;

typedef struct SList
{
	SListNode *head;  //成员封装
}SList;

void SListInit(SList *plist);
void SListPushBack(SList *plist, ElemType x);
void SListPushFront(SList *plist, ElemType x);
void SListPopBack(SList *plist);
void SListPopFront(SList *plist);
void SListShow(SList *plist);

int SListLength(SList *plist);
SListNode* SeqListFind(SList *plist, ElemType key);
void SListClear(SList *plist);
void SListDestroy(SList *plist);

void SListDeleteByVal(SList *plist, ElemType key);
void SListInsertByVal(SList *plist, ElemType x);
void SListReverse(SList *plist);

SListNode* _Buynode()
{
	SListNode *s = (SListNode *)malloc(sizeof(SListNode));
	assert(s != NULL);
	s->data = 0;
	s->next = NULL;
	return s;
}

void SListInit(SList *plist)
{
	plist->head = NULL;
}

void SListPushBack(SList *plist, ElemType x)
{
	assert(plist);
	SListNode *s = _Buynode();
	s->data = x;

	//查找链表的尾部
	SListNode *p = plist->head;

	//插入的节点是第一个节点
	if(p == NULL)
		plist->head = s;
	else
	{
		while(p->next != NULL)
			p = p->next;
		p->next = s;
	}
}

void SListPushFront(SList *plist, ElemType x)
{
	assert(plist);//合法检查
	SListNode* s = _Buynode(); //创建新节点，存储数据
	s->data = x;

	s->next = plist->head;
	plist->head = s;
}

void SListPopBack(SList *plist)
{
	assert(plist);
	SListNode *p = plist->head;
	
	if(p != NULL) //不能为空
	{
		if(p->next == NULL) // 只有一个节点
			plist->head = NULL;
		else
		{
			SListNode *pre = NULL;
			while(p->next != NULL)
			{
				pre = p;
				p = p->next;
			}
			pre->next = NULL;
		}
		free(p);
	}
}

void SListPopFront(SList *plist)
{
	assert(plist);
	SListNode *p = plist->head;
	if(p != NULL)
	{
		plist->head = p->next;
		free(p);
	}
}

void SListShow(SList *plist)
{
	SListNode *p = plist->head;
	while(p != NULL)
	{
		printf("%d-->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

int SListLength(SList *plist)
{
	assert(plist);
	int len = 0;
	SListNode *p = plist->head;

	while(p != NULL)
	{
		len++;
		p = p->next;
	}
	return len;
}

SListNode* SeqListFind(SList *plist, ElemType key)
{
	//找到返回节点的地址
	//找不到返回NULL
	assert(plist);
	SListNode *p = plist->head;

	while(p!=NULL && p->data!=key)
		p = p->next;
	return p;
}

void SListClear(SList *plist)
{
	assert(plist);
	SListNode *p = plist->head;
	while(p != NULL)
	{
		plist->head = p->next;  //头删
		free(p);
		p = plist->head;
	}
}

void SListDestroy(SList *plist)
{
	SListClear(plist);
}

void SListDeleteByVal(SList *plist, ElemType key)
{
	assert(plist);
	//查找节点
	SListNode *p = plist->head;
	SListNode *pre = NULL;
	while(p!=NULL && p->data!=key)
	{
		pre = p;
		p = p->next;
	}

	if(p != NULL)  //找到删除的节点
	{
		if(pre == NULL) //删除的节点为第一个节点
			plist->head = p->next;
		else
			pre->next = p->next;

		free(p);
	}
}

void SListInsertByVal(SList *plist, ElemType x)
{
	assert(plist);
	SListNode *s = _Buynode();
	s->data = x;

	if(plist->head == NULL)
		plist->head = s;
	else
	{
		SListNode *p = plist->head;
		SListNode *pre = NULL;
		while(p!=NULL && x>p->data)
		{
			pre = p;
			p = p->next;
		}

		if(pre == NULL) //说明在链表的头部插入
		{
			s->next = p;  //s->next = plist->head
			plist->head = s;
		}
		else
		{
			s->next = pre->next;
			pre->next = s;
		}
	}
}

void SListReverse(SList *plist)
{
	assert(plist);
	SListNode *p, *q;
	if(plist->head == NULL)
		return;

	if(plist->head->next == NULL) //不需要转置
		return;
	
	//1 切割链表
	p = plist->head->next;
	plist->head->next = NULL;

	//2 将剩余的链表节点进行一一头插
	q = p;
	while(q != NULL)
	{
		q = q->next;
		p->next = plist->head;
		plist->head = p;
		p = q;
	}
}


/////////////////////////////////////////////////////////////////////////////////
/*
typedef struct ListNode
{
	int data; //数据域
	struct ListNode *next;
}ListNode;

typedef ListNode* List;

void ListInit(List *head)  //ListNode **head
{
	*head = (ListNode *)malloc(sizeof(ListNode));
	*head != NULL;
	(*head)->next = NULL;
}

//尾插法
void ListCreate_Tail(List *head)
{
	ListNode *p = *head;
	for(int i=1; i<=10; ++i)
	{
		ListNode *s = (ListNode*)malloc(sizeof(ListNode));
		assert(s != NULL);
		s->data = i;
		s->next = NULL;

		//链接节点
		p->next = s;
		p = s;
	}
}

//分析函数
void ListCreate(List *head)
{
	ListNode *p = *head;
	for(int i=1; i<=10; ++i)
	{
		p = p->next = (ListNode *)malloc(sizeof(ListNode));
		assert(p != NULL);
		p->data = i;
		p->next = NULL;
	}
}

void ListShow(List head)
{
	ListNode *p = head->next;
	while(p != NULL)
	{
		printf("%d-->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

/*
void ListInit(List *head)  //ListNode **head
{
	*head = NULL;
}

//1->2->3->4->....->10
//尾插法
void ListCreate_Tail(List *head)
{
	*head = (ListNode*)malloc(sizeof(ListNode));
	assert(*head != NULL);
	(*head)->data = 1;
	
	ListNode *p = *head;
	for(int i=2; i<=10; ++i)
	{
		ListNode *s = (ListNode*)malloc(sizeof(ListNode));
		assert(s != NULL);
		s->data = i;
		s->next = NULL;

		p->next = s;
		p = s;
	}
}

void ListCreate_Head(List *head)
{
	*head = (ListNode*)malloc(sizeof(ListNode));
	assert(*head != NULL);
	(*head)->data = 1;
	(*head)->next = NULL;

	for(int i=2; i<=10; ++i)
	{
		ListNode *s = (ListNode*)malloc(sizeof(ListNode));
		assert(s != NULL);
		s->data = i;

		s->next = *head;
		*head = s;
	}
}

void ListShow(List head)
{
	ListNode *p = head;
	while(p != NULL)
	{
		printf("%d-->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}
*/
#endif /* _LIST_H_ */