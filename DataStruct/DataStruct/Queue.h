#ifndef _QUEUE_H_
#define _QUEUE_H_

#include"Sysutil.h"

struct BinTreeNode;
#define QueueElemType struct BinTreeNode*

//链队列
typedef struct LinkQueueNode
{
	QueueElemType data;
	struct LinkQueueNode *next;
}LinkQueueNode;

typedef struct LinkQueue
{
	LinkQueueNode *head;
	LinkQueueNode *tail; //指向队尾节点
}LinkQueue;

void LinkQueueInit(LinkQueue *pq);
void LinkQueueDestroy(LinkQueue *pq);
void LinkQueueEn(LinkQueue *pq, QueueElemType x);
void LinkQueueDe(LinkQueue *pq);
void LinkQueueShow(LinkQueue *pq);
QueueElemType LinkQueueBack(LinkQueue *pq);
QueueElemType LinkQueueFront(LinkQueue *pq);
bool LinkQueueEmpty(LinkQueue *pq)
{
	return pq->head == NULL;
}

void LinkQueueInit(LinkQueue *pq)
{
	assert(pq);
	pq->head = pq->tail = NULL;
}

void LinkQueueEn(LinkQueue *pq, QueueElemType x)
{
	assert(pq);
	LinkQueueNode *s = (LinkQueueNode *)malloc(sizeof(LinkQueueNode));
	assert(s != NULL);
	s->data = x;
	s->next = NULL;
	if(pq->head == NULL)
		pq->head = pq->tail = s;
	else
	{
		pq->tail->next = s;
		pq->tail = s;
	}
}

void LinkQueueDe(LinkQueue *pq)
{
	assert(pq);
	if(pq->head != NULL)
	{
		LinkQueueNode *p = pq->head;
		pq->head = p->next;
		if(pq->head == NULL)
			pq->tail = NULL;
		free(p);
	}
}

void LinkQueueShow(LinkQueue *pq)
{
	assert(pq != NULL);
	LinkQueueNode *p = pq->head;
	while(p != NULL)
	{
		printf("%d<--", p->data);
		p = p->next;
	}
	printf("Nil.\n");
}

QueueElemType LinkQueueBack(LinkQueue *pq)
{
	assert(pq && pq->head);
	return pq->tail->data;
}
QueueElemType LinkQueueFront(LinkQueue *pq)
{
	assert(pq && pq->head);
	return pq->head->data;
}

void LinkQueueDestroy(LinkQueue *pq)
{
	assert(pq);
	while(pq->head != NULL)
	{
		LinkQueueNode *p = pq->head;
		pq->head = p->next;
		free(p);
	}
	pq->head = pq->tail = NULL;
}


//顺序队列 --> 循环队列
#define QUEUE_DEFAULT_SIZE 8
typedef struct SeqQueue
{
	QueueElemType *base;
	size_t         capacity;
	int            front;
	int            rear;
}SeqQueue;

void SeqQueueInit(SeqQueue *pq, int sz);

void SeqQueueDestroy(SeqQueue *pq);

void SeqQueueEn(SeqQueue *pq, QueueElemType x);
void SeqQueueDe(SeqQueue *pq);
QueueElemType SeqQueueBack(SeqQueue *pq);
QueueElemType SeqQueueFront(SeqQueue *pq);
void SeqQueueShow(SeqQueue *pq);

void SeqQueueInit(SeqQueue *pq, int sz)
{
	assert(pq);
	pq->capacity = sz > QUEUE_DEFAULT_SIZE ? sz : QUEUE_DEFAULT_SIZE;
	pq->base = (QueueElemType*)malloc(sizeof(QueueElemType) * (pq->capacity+1));
	assert(pq->base != NULL);
	pq->front = pq->rear = 0;
}

void SeqQueueDestroy(SeqQueue *pq)
{
	assert(pq);
	free(pq->base);
	pq->base = NULL;
	pq->capacity = pq->front = pq->rear = 0;
}

void SeqQueueEn(SeqQueue *pq, QueueElemType x)
{
	assert(pq);
	if((pq->rear+1)%(pq->capacity+1) == pq->front)
	{
		printf("队列已满, %d 不能入队.\n", x);
		return;
	}

	pq->base[pq->rear] = x;
	pq->rear = (pq->rear+1) % (pq->capacity+1);
}
void SeqQueueDe(SeqQueue *pq)
{
	assert(pq);
	if(pq->front == pq->rear)
	{
		printf("队列已空，不能出队.\n");
		return;
	}
	pq->front = (pq->front+1) % (pq->capacity+1);
}
QueueElemType SeqQueueBack(SeqQueue *pq)
{
	assert(pq && (pq->front!=pq->rear));
	return pq->base[(pq->rear-1+pq->capacity+1) % (pq->capacity+1)];
}
QueueElemType SeqQueueFront(SeqQueue *pq)
{
	assert(pq && (pq->front!=pq->rear));
	return pq->base[pq->front];
}
void SeqQueueShow(SeqQueue *pq)
{
	assert(pq);
	for(int i=pq->front; i!=pq->rear; )
	{
		printf("%d<--", pq->base[i]);
		i = (i+1)%(pq->capacity+1);
	}
	printf("Nil.\n");
}
#endif /* _QUEUE_H_ */