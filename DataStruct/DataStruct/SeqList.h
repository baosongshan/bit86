#include"Sysutil.h"
//顺序表

#define ElemType int
#define SEQLIST_DEFAULT_SIZE 8

//定义顺序表的数据结构
typedef struct SeqList
{
	ElemType *base;
	size_t    capacity;
	size_t    size;
}SeqList;

bool IsFull(SeqList *pst);
bool IsEmpty(SeqList *pst);
void SeqListInit(SeqList *pst);
void SeqListPushBack(SeqList *pst, ElemType x);
void SeqListPushFront(SeqList *pst, ElemType x);
void SeqListPopBack(SeqList *pst);
void SeqListPopFront(SeqList *pst);
void SeqListShow(SeqList *pst);

size_t SeqListLength(SeqList *pst);
size_t SeqListCapacity(SeqList *pst);
void SeqListClear(SeqList *pst);
void SeqListDestroy(SeqList *pst);
int SeqListFind(SeqList *pst, ElemType key);
void SeqListSort(SeqList *pst);
void SeqListDeleteByVal(SeqList *pst, ElemType key);
void SeqListDeleteByPos(SeqList *pst, int pos);

////////////////////////////////////////////////////////////

bool IsFull(SeqList *pst)
{return pst->size >= pst->capacity;}
bool IsEmpty(SeqList *pst)
{return pst->size == 0;}

void SeqListInit(SeqList *pst)
{
	assert(pst);
	pst->base = (ElemType*)malloc(sizeof(ElemType) * SEQLIST_DEFAULT_SIZE);
	assert(pst->base != NULL); //开辟空间成功
	memset(pst->base, 0, sizeof(ElemType) * SEQLIST_DEFAULT_SIZE);
	pst->capacity = SEQLIST_DEFAULT_SIZE;
	pst->size = 0;
}

void SeqListPushBack(SeqList *pst, ElemType x)
{
	assert(pst);
	//判满
	if(IsFull(pst))
	{
		printf("顺序表已满，%d 不能尾部插入.\n", x);
		return;
	}
	pst->base[pst->size++] = x;
}

void SeqListPushFront(SeqList *pst, ElemType x)
{
	assert(pst);
	//判满
	if(IsFull(pst))
	{
		printf("顺序表已满，%d 不能头部插入.\n", x);
		return;
	}
	//移动数据
	for(int i=pst->size; i>0; --i)
		pst->base[i] = pst->base[i-1];

	//头插数据
	pst->base[0] = x;

	//元素++
	pst->size++;
}

void SeqListPopBack(SeqList *pst)
{
	assert(pst);
	if(IsEmpty(pst))
	{
		printf("顺序表已空, 不能尾部删除.\n");
		return;
	}
	pst->size--;
}

void SeqListPopFront(SeqList *pst)
{
	assert(pst);
	if(IsEmpty(pst))
	{
		printf("顺序表已空, 不能头部删除.\n");
		return;
	}

	for(int i=0; i<pst->size-1; ++i)
		pst->base[i] = pst->base[i+1];
	pst->size--;
}

void SeqListShow(SeqList *pst)
{
	assert(pst);
	for(int i=0; i<pst->size; ++i)  //0 1 2 3 4 5
	{
		printf("%d ", pst->base[i]);
	}
	printf("\n");
}

size_t SeqListLength(SeqList *pst)
{return pst->size;}
size_t SeqListCapacity(SeqList *pst)
{return pst->capacity;}
void SeqListClear(SeqList *pst)
{pst->size = 0;}

void SeqListDestroy(SeqList *pst)
{
	assert(pst);
	free(pst->base);
	pst->base = NULL; // 预防野指针
	pst->capacity = pst->size = 0;
}

int SeqListFind(SeqList *pst, ElemType key)
{
	for(int i=0; i<pst->size; ++i)
	{
		if(key == pst->base[i])
			return i;
	}
	return -1;
}

void SeqListSort(SeqList *pst)
{
	//冒泡排序
	for(int i=0; i<pst->size-1; ++i) //控制趟数
	{
		for(int j=0; j<pst->size-i-1; ++j)
		{
			if(pst->base[j] > pst->base[j+1])
			{
				//交换数据
				ElemType tmp = pst->base[j];
				pst->base[j] = pst->base[j+1];
				pst->base[j+1] = tmp;
			}
		}
	}
}

void SeqListDeleteByVal(SeqList *pst, ElemType key)
{
	assert(pst);
	int index = SeqListFind(pst, key);
	if(index == -1)
	{
		printf("要删除的元素%d不存在，不能删除.\n", key);
		return;
	}
	//for(int i=index; i<pst->size; ++i)
	//	pst->base[i] = pst->base[i+1];
	//pst->size--;
	SeqListDeleteByPos(pst, index);
}

void SeqListDeleteByPos(SeqList *pst, int pos)
{
	//判断位置的合法性
	assert(pst && (pos>=0&&pos<pst->size));
	for(int i=pos; i<pst->size; ++i)
		pst->base[i] = pst->base[i+1];
	pst->size--;
}