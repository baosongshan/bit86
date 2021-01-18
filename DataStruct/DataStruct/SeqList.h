#ifndef _SEQLIST_H_
#define _SEQLIST_H_

#include"Sysutil.h"
//˳���

#define ElemType int
#define SEQLIST_DEFAULT_SIZE 8
#define SEQLIST_INC_SIZE 4

//����˳�������ݽṹ
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

void SeqListReverse(SeqList *pst);
void SeqListInsertByVal(SeqList *pst, ElemType x);
void SeqListInsertByPos(SeqList *pst, int pos, ElemType x);
int SeqListFindByBinary(SeqList *pst, ElemType key);
void SeqListRemoveAll(SeqList *pst, ElemType key);

////////////////////////////////////////////////////////////

bool IsFull(SeqList *pst)
{return pst->size >= pst->capacity;}
bool IsEmpty(SeqList *pst)
{return pst->size == 0;}

//�»��ߴ����������ֻ�����ڲ�����
bool _Inc(SeqList *pst)
{
	//�����¿ռ�
	//ElemType *new_base = (ElemType*)malloc(sizeof(ElemType)*(pst->capacity+SEQLIST_INC_SIZE));
	ElemType *new_base = (ElemType*)malloc(sizeof(ElemType)*(pst->capacity * 2));
	if(new_base == NULL)
	{
		printf("����ʧ��.\n");
		return false;
	}
	//��������
	memcpy(new_base, pst->base, sizeof(ElemType)*pst->capacity);

	//�ͷžɿռ�
	free(pst->base);

	//����base��ָ��
	pst->base = new_base;
	pst->capacity += SEQLIST_INC_SIZE;
	return true;
}


void SeqListInit(SeqList *pst)
{
	assert(pst);
	pst->base = (ElemType*)malloc(sizeof(ElemType) * SEQLIST_DEFAULT_SIZE);
	assert(pst->base != NULL); //���ٿռ�ɹ�
	memset(pst->base, 0, sizeof(ElemType) * SEQLIST_DEFAULT_SIZE);
	pst->capacity = SEQLIST_DEFAULT_SIZE;
	pst->size = 0;
}

void SeqListPushBack(SeqList *pst, ElemType x)
{
	assert(pst);
	//����
	if(IsFull(pst) && !_Inc(pst))
	{
		printf("˳���������%d ����β������.\n", x);
		return;
	}
	pst->base[pst->size++] = x;
}

void SeqListPushFront(SeqList *pst, ElemType x)
{
	assert(pst);
	//����
	if(IsFull(pst) && !_Inc(pst))
	{
		printf("˳���������%d ����ͷ������.\n", x);
		return;
	}
	//�ƶ�����
	for(int i=pst->size; i>0; --i)
		pst->base[i] = pst->base[i-1];

	//ͷ������
	pst->base[0] = x;

	//Ԫ��++
	pst->size++;
}

void SeqListPopBack(SeqList *pst)
{
	assert(pst);
	if(IsEmpty(pst))
	{
		printf("˳����ѿ�, ����β��ɾ��.\n");
		return;
	}
	pst->size--;
}

void SeqListPopFront(SeqList *pst)
{
	assert(pst);
	if(IsEmpty(pst))
	{
		printf("˳����ѿ�, ����ͷ��ɾ��.\n");
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
	pst->base = NULL; // Ԥ��Ұָ��
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
	//ð������
	for(int i=0; i<pst->size-1; ++i) //��������
	{
		for(int j=0; j<pst->size-i-1; ++j)
		{
			if(pst->base[j] > pst->base[j+1])
			{
				//��������
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
		printf("Ҫɾ����Ԫ��%d�����ڣ�����ɾ��.\n", key);
		return;
	}
	//for(int i=index; i<pst->size; ++i)
	//	pst->base[i] = pst->base[i+1];
	//pst->size--;
	SeqListDeleteByPos(pst, index);
}

void SeqListDeleteByPos(SeqList *pst, int pos)
{
	//�ж�λ�õĺϷ���
	assert(pst && (pos>=0&&pos<pst->size));
	for(int i=pos; i<pst->size; ++i)
		pst->base[i] = pst->base[i+1];
	pst->size--;
}

void SeqListReverse(SeqList *pst)
{
	assert(pst);
	int start = 0, end = pst->size-1;
	while(start < end)
	{
		ElemType tmp = pst->base[start];
		pst->base[start] = pst->base[end];
		pst->base[end] = tmp;

		start++;
		end--;
	}
}

void SeqListInsertByVal(SeqList *pst, ElemType x)
{
	//����֮ǰҪ��֤��������
	assert(pst);
	if(IsFull(pst) && !_Inc(pst))
	{
		printf("˳���������%d ���ܰ�ֵ����.\n", x);
		return;
	}

	//Ѱ��λ�ò���
	int pos = 0;
	while(pos<pst->size && x>pst->base[pos])
		pos++;

	for(int i=pst->size; i>pos; --i)
		pst->base[i] = pst->base[i-1];

	pst->base[pos] = x;
	pst->size++;
}

void SeqListInsertByPos(SeqList *pst, int pos, ElemType x)
{
	assert(pst);
	if(IsFull(pst) && !_Inc(pst))
	{
		printf("˳���������%d ���ܰ�λ�ò���.\n", x);
		return;
	}
	if(pos<0 || pos>pst->size)
	{
		printf("�����λ�÷Ƿ���%d ���ܰ�λ�ò���.\n", x);
		return;
	}

	for(int i=pst->size; i>pos; --i)
	{
		pst->base[i] = pst->base[i-1];
	}
	pst->base[pos] = x;
	pst->size++;
}

int SeqListFindByBinary(SeqList *pst, ElemType key)
{
	assert(pst);
	SeqListSort(pst); //�ȱ�֤���ҵ���������

	int low = 0, high = pst->size-1, mid;
	while(low <= high)
	{
		mid = (low + high) / 2;
		if(key == pst->base[mid])
			return mid;
		else if(key < pst->base[mid])
			high = mid - 1;
		else 
			low = mid + 1;
	}
	return -1;
}

void SeqListRemoveAll(SeqList *pst, ElemType key)
{
	assert(pst);
	int index;
	do
	{
		index = SeqListFind(pst, key);
		if(index == -1)
			break;
		SeqListDeleteByPos(pst, index);
	}while(1);
}

#endif /* _SEQLIST_H_ */

/*
bool _Inc(SeqList *pst)
{
	ElemType *new_base = (ElemType*)realloc(pst->base, sizeof(ElemType)*(pst->capacity + SEQLIST_INC_SIZE));
	if(new_base == NULL)
	{
		printf("����ʧ��.\n");
		return false;
	}
	pst->base = new_base;
	pst->capacity += SEQLIST_INC_SIZE;
	return true;
}

void SeqListRemoveAll(SeqList *pst, ElemType key)
{
	assert(pst);
	int index;
	do
	{
		index = SeqListFind(pst, key);
		if(index == -1)
			break;
		SeqListDeleteByPos(pst, index);
	}while(1);
}
*/