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

void SListSort(SList *plist);
void SListRemoveAll(SList *plist, ElemType key);

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

void SListSort(SList *plist)
{
	assert(plist);
	SListNode *p, *q;

	if(plist->head==NULL || plist->head->next==NULL)
		return;

	//�Ͽ�����
	p = plist->head->next;
	plist->head->next = NULL;

	//ѭ����ֵ����
	q = p;
	while(q != NULL)
	{
		q = q->next;
		SListNode *t = plist->head;
		SListNode *pre = NULL;
		while(t!=NULL && p->data>t->data)  //Ѱ�Ҳ���λ��
		{
			pre = t;
			t = t->next;
		}
		if(pre == NULL) //��ͷ������
		{
			p->next = plist->head;
			plist->head = p;
		}
		else
		{
			p->next = pre->next;
			pre->next = p;
		}
		p = q;
	}
}

void SListRemoveAll(SList *plist, ElemType key)
{
	assert(plist);
	SListNode* p = plist->head;
	SListNode* pre = NULL;
	
	while (p != NULL) 
	{
		while (p != NULL && p->data != key) 
		{
			pre = p;
			p = p->next;
		}
		if (p != NULL) 
		{
			if (pre == NULL)//��һ���ڵ�
				plist->head = p->next;
			else//�м�ڵ�
				pre->next = p->next;
			free(p);//�ͷ�data=key�Ľڵ�
		}
		if (NULL != pre)//
			p = pre->next;
		else
			p = plist->head;//��ͷ��ʼ
	}
}

/*
void SListRemoveAll(SList *plist, ElemType key)
{
	assert(plist);

	SListNode *p, *pre = NULL;
	
	if(plist->head == NULL)
		return;
	
	p = plist->head;

	while(p != NULL)
	{
		if(p->data == key)
		{
			if(pre == NULL)
				plist->head = p->next;
			else
				pre->next = p->next;

			free(p);
		}
		else
			pre = p;

		if(pre == NULL)
			p = plist->head;
		else
			p = pre->next;
	}
}
*/
//////////////////////////////////////////////////////////////////////////////////
//��ѭ������ --> �������
typedef struct SCListNode
{
	ElemType data;
	struct SCListNode *next;
}SCListNode;

typedef struct SCList
{
	SCListNode *head;
}SCList;
void SCListInit(SCList *plist);
void SCListPushBack(SCList *plist, ElemType x);
void SCListPushFront(SCList *plist, ElemType x);
void SCListPopBack(SCList *plist);
void SCListPopFront(SCList *plist);
void SCListShow(SCList *plist);

int SCListLength(SCList *plist);
SCListNode* SCListFind(SCList *plist, ElemType key);
void SCListClear(SCList *plist);
void SCListDestroy(SCList *plist);

void SCListDeleteByVal(SCList *plist, ElemType key);
void SCListInsertByVal(SCList *plist, ElemType x);
void SCListReverse(SCList *plist);

void SCListSort(SCList *plist);
void SCListRemoveAll(SCList *plist, ElemType key);

/////////////////////////////////////////////////////////////////////////////////////
//˫������ -->�������
typedef struct DListNode
{
	ElemType data;
	struct DListNode *prev;
	struct DListNode *next;
}DListNode;

typedef struct DList
{
	DListNode *head;
}DList;

void DListInit(DList *plist);
void DListPushBack(DList *plist, ElemType x);
void DListPushFront(DList *plist, ElemType x);
void DListShow(DList *plist);
void DListPopBack(DList *plist);
void DListPopFront(DList *plist);
size_t DListLength(DList *plist);
void DListClear(DList *plist);
void DListDestroy(DList *plist);
DListNode* DListFind(DList *plist, ElemType key);
void DListDeleteByVal(DList *plist, ElemType key);
void DListReverse(DList *plist);
void DListInsertByVal(DList *plist, ElemType x);

/////////////////////////////////////////////////////////////////////////////////////
//��ͷ���˫��ѭ������
typedef struct DCListNode
{
	ElemType data;
	struct DCListNode *prev;
	struct DCListNode *next;
}DCListNode;

typedef struct DCList
{
	DCListNode *first;
	DCListNode *last;
	size_t      size;
}DCList;

DCListNode* _BuyDCListNode(ElemType x)
{
	DCListNode *s = (DCListNode*)malloc(sizeof(DCListNode));
	assert(s != NULL);
	s->next = s->prev = NULL;
	s->data = x;
	return s;
}

void DCListInit(DCList *plist);
void DCListPushBack(DCList *plist, ElemType x);
void DCListPushFront(DCList *plist, ElemType x);
void DCListShow(DCList *plist);
void DCListPopBack(DCList *plist);
void DCListPopFront(DCList *plist);
size_t DCListLength(DCList *plist);
void DCListClear(DCList *plist);
void DCListDestroy(DCList *plist);
DCListNode* DCListFind(DCList *plist, ElemType key);
void DCListDeleteByVal(DCList *plist, ElemType key);
void DCListReverse(DCList *plist);
void DCListInsertByVal(DCList *plist, ElemType x);

void DCListInit(DCList *plist)
{
	assert(plist);
	DCListNode *s = _BuyDCListNode(0);
	plist->first = plist->last = s;

	plist->last->next = plist->first;
	plist->first->prev = plist->last;
	plist->size = 0;
}

void DCListPushBack(DCList *plist, ElemType x)
{
	assert(plist);
	DCListNode *s = _BuyDCListNode(x);
	s->prev = plist->last;
	plist->last->next = s;
	plist->last = s;

	plist->last->next = plist->first;
	plist->first->prev = plist->last;
	plist->size++;
}

void DCListPushFront(DCList *plist, ElemType x)
{
	assert(plist);
	DCListNode *s = _BuyDCListNode(x);

	s->next = plist->first->next;
	plist->first->next->prev = s;
	plist->first->next = s;
	s->prev = plist->first;

	if(plist->last == plist->first)
		plist->last = s;

	plist->size++;
}

void DCListShow(DCList *plist)
{
	DCListNode *p = plist->first->next;
	while(p != plist->first)
	{
		printf("%d-->", p->data);
		p = p->next;
	}
	printf("Over.\n");
}

void DCListPopBack(DCList *plist)
{
	assert(plist);
	DCListNode *p = plist->last;
	if(p != plist->first)
	{
		plist->last = p->prev;
		plist->last->next = plist->first;
		plist->first->prev = plist->last;

		free(p);
		plist->size--;
	}
}

void DCListPopFront(DCList *plist)
{
	assert(plist);

	DCListNode *p;
	if(plist->size == 0)
		return;

	p = plist->first->next;

	p->prev->next = p->next;
	p->next->prev = p->prev;

	free(p);
	plist->size--;
	if(plist->size == 0)
		plist->last = plist->first;

}

size_t DCListLength(DCList *plist)
{return plist->size;}

void DCListClear(DCList *plist)
{
	assert(plist);
	DCListNode *p = plist->first->next;
	if(plist->size == 0)
		return;
	while(p != plist->first)
	{
		p->prev->next = p->next;
		p->next->prev = p->prev;
		free(p);
		p = plist->first->next;
	}
	plist->size = 0;
	plist->last = plist->first;
}
void DCListDestroy(DCList *plist)
{
	DCListClear(plist);
	free(plist->first);
	plist->first = plist->last = NULL;
	plist->size = 0;
}

DCListNode* DCListFind(DCList *plist, ElemType key)
{
	assert(plist);
	DCListNode *p = plist->first->next;
	while(p!=plist->first && p->data!=key)
		p = p->next;
	if(p == plist->first)
		return NULL;
	return p;
}

void DCListDeleteByVal(DCList *plist, ElemType key)
{
	assert(plist);
	DCListNode *p = DCListFind(plist, key);
	if(p != NULL)
	{
		if(p == plist->last) //��Ҫ�ж��Ƿ������һ���ڵ�
			plist->last = p->prev;

		p->prev->next = p->next;
		p->next->prev = p->prev;

		free(p);
		plist->size--;
	}
}

void DCListReverse(DCList *plist)
{
	assert(plist);
	DCListNode *p, *q;
	if(plist->size <= 1)
		return;

	p = plist->first->next;
	q = p->next;
	plist->last = p;
	plist->last->next = plist->first;
	plist->first->prev = plist->last;

	while(q != plist->first)
	{
		p = q;
		q = q->next;

		p->next = plist->first->next;
		p->next->prev = p;
		p->prev = plist->first;
		p->prev->next = p;
	}
}

void DCListInsertByVal(DCList *plist, ElemType x)
{
	assert(plist);
	DCListNode *s = _BuyDCListNode(x);
	DCListNode *p = plist->first->next;
	while(p!=plist->first && x>p->data)
		p = p->next;
	if(p == plist->first)
		plist->last = s;

	s->next = p;
	s->prev = p->prev;
	s->prev->next = s;
	s->next->prev = s;  
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