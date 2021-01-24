#ifndef _STACK_H_
#define _STACK_H_

#include"Sysutil.h"
#define StackElemType int

#define SEQSTACK_DEFAULT_SIZE 8

//顺序栈
typedef struct SeqStack
{
	StackElemType *base; //
	size_t         capacity;
	int            top;
}SeqStack;


void SeqStackInit(SeqStack *pst, int sz);
void SeqStackDestroy(SeqStack *pst);
void SeqStackPush(SeqStack *pst, StackElemType x);
void SeqStackPop(SeqStack *pst);
StackElemType SeqStackTop(SeqStack *pst);
void SeqStackShow(SeqStack *pst);

bool IsFull(SeqStack *pst)
{return pst->top >= pst->capacity;}
bool IsEmpty(SeqStack *pst)
{return pst->top == 0;}

void SeqStackInit(SeqStack *pst, int sz)
{
	assert(pst);
	pst->capacity = sz > SEQSTACK_DEFAULT_SIZE ? sz : SEQSTACK_DEFAULT_SIZE;
	pst->base = (StackElemType*)malloc(sizeof(StackElemType) * pst->capacity);
	assert(pst->base != NULL);
	pst->top = 0;
}

void SeqStackPush(SeqStack *pst, StackElemType x)
{
	assert(pst);
	if(IsFull(pst))
	{
		printf("栈空间已满，%d不能入栈\n", x);
		return;
	}
	pst->base[pst->top++] = x;
}

void SeqStackPop(SeqStack *pst)
{
	assert(pst);
	if(IsEmpty(pst))
	{
		printf("栈已空，不能出栈.\n");
		return;
	}
	pst->top--;
}

StackElemType SeqStackTop(SeqStack *pst)
{
	assert(pst && !IsEmpty(pst));
	return pst->base[pst->top-1];
}

void SeqStackShow(SeqStack *pst)
{
	assert(pst);
	for(int i=pst->top-1; i>=0; --i)
		printf("%d\n", pst->base[i]);
}

void SeqStackDestroy(SeqStack *pst)
{
	assert(pst);
	free(pst->base);
	pst->base = NULL;
	pst->capacity = pst->top = 0;
}

///////////////////////////////////////////////////////////
//链栈
typedef struct LinkStackNode
{
	StackElemType data;
	struct LinkStackNode *next;
}LinkStackNode;
typedef struct LinkStack
{
	LinkStackNode *head;
}LinkStack;

void LinkStackInit(LinkStack *pst);
void LinkStackDestroy(LinkStack *pst);
void LinkStackPush(LinkStack *pst, StackElemType x);
void LinkStackPop(LinkStack *pst);
StackElemType LinkStackTop(LinkStack *pst);
void LinkStackShow(LinkStack *pst);

void LinkStackInit(LinkStack *pst)
{
	assert(pst);
	pst->head = NULL;
}

void LinkStackPush(LinkStack *pst, StackElemType x)
{
	assert(pst);
	LinkStackNode *s = (LinkStackNode*)malloc(sizeof(LinkStackNode));
	assert(s != NULL);
	s->data = x;

	s->next = pst->head;
	pst->head = s;
}

void LinkStackPop(LinkStack *pst)
{
	assert(pst);
	if(pst->head != NULL)
	{
		LinkStackNode *p = pst->head;
		pst->head = p->next;
		free(p);
	}
}

StackElemType LinkStackTop(LinkStack *pst)
{
	assert(pst && pst->head != NULL);
	return pst->head->data;
}

void LinkStackShow(LinkStack *pst)
{
	assert(pst);
	LinkStackNode *p = pst->head;
	while(p != NULL)
	{
		printf("%d\n", p->data);
		p = p->next;
	}
}

void LinkStackDestroy(LinkStack *pst)
{
	assert(pst);
	while(pst->head != NULL)
	{
		LinkStackNode *p = pst->head;
		pst->head = p->next;
		free(p);
	}
}

#endif /* _STACK_H_ */