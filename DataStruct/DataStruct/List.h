#ifndef _LIST_H_
#define _LIST_H_

#include"Sysutil.h"

#define ElemType int

//��ͷ������
typedef struct SListNode
{
	ElemType data; //������
	struct SListNode *next; //ָ����
}SListNode;

typedef struct SList
{
	SListNode *head;  //��Ա��װ
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

	//���������β��
	SListNode *p = plist->head;

	//����Ľڵ��ǵ�һ���ڵ�
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
	assert(plist);//�Ϸ����
	SListNode* s = _Buynode(); //�����½ڵ㣬�洢����
	s->data = x;

	s->next = plist->head;
	plist->head = s;
}

void SListPopBack(SList *plist)
{
	assert(plist);
	SListNode *p = plist->head;
	
	if(p != NULL) //����Ϊ��
	{
		if(p->next == NULL) // ֻ��һ���ڵ�
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
	//�ҵ����ؽڵ�ĵ�ַ
	//�Ҳ�������NULL
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
		plist->head = p->next;  //ͷɾ
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
	//���ҽڵ�
	SListNode *p = plist->head;
	SListNode *pre = NULL;
	while(p!=NULL && p->data!=key)
	{
		pre = p;
		p = p->next;
	}

	if(p != NULL)  //�ҵ�ɾ���Ľڵ�
	{
		if(pre == NULL) //ɾ���Ľڵ�Ϊ��һ���ڵ�
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

		if(pre == NULL) //˵���������ͷ������
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

	if(plist->head->next == NULL) //����Ҫת��
		return;
	
	//1 �и�����
	p = plist->head->next;
	plist->head->next = NULL;

	//2 ��ʣ�������ڵ����һһͷ��
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
	int data; //������
	struct ListNode *next;
}ListNode;

typedef ListNode* List;

void ListInit(List *head)  //ListNode **head
{
	*head = (ListNode *)malloc(sizeof(ListNode));
	*head != NULL;
	(*head)->next = NULL;
}

//β�巨
void ListCreate_Tail(List *head)
{
	ListNode *p = *head;
	for(int i=1; i<=10; ++i)
	{
		ListNode *s = (ListNode*)malloc(sizeof(ListNode));
		assert(s != NULL);
		s->data = i;
		s->next = NULL;

		//���ӽڵ�
		p->next = s;
		p = s;
	}
}

//��������
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
//β�巨
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