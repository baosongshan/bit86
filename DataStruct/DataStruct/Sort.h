#ifndef _SORT_H_
#define _SORT_H_

#include"Sysutil.h"

void Swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void PrintArray(int *ar, int left, int right)
{
	for(int i=left; i<right; ++i)
		printf("%d ", ar[i]);
	printf("\n");
}

//直接插入排序-从前往后比较
void InsertSort_1(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		int k=left;
		while(ar[i] > ar[k])
			k++;

		int tmp = ar[i];
		for(int j=i; j>k; --j)
			ar[j] = ar[j-1];

		ar[k] = tmp;
	}
}
//直接插入排序-从后往前比较
void InsertSort_2(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		int j = i;
		while(j>left && ar[j] < ar[j-1])
		{
			Swap(&ar[j], &ar[j-1]);
			j--;
		}
	}
}

//直接插入排序-从后往前比较不调用交换函数
void InsertSort_3(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		int j = i;
		int tmp = ar[j];
		while(j>left && tmp < ar[j-1])
		{
			ar[j] = ar[j-1];
			j--;
		}

		ar[j] = tmp;
	}
}


void TestSortEfficient()
{
	int n = 20000;
	int *a = (int*)malloc(sizeof(int) * n);
	int *a1 = (int *)malloc(sizeof(int) * n);
	int *a2 = (int *)malloc(sizeof(int) * n);
	srand(time(0));
	for(int i=0; i<n; ++i)
	{
		a[i] = rand();
		a1[i] = a[i];
		a2[i] = a[i];
	}

	time_t start = clock();
	InsertSort_1(a, 0, n);
	time_t end = clock();
	printf("InsertSort_1 : %u\n", end - start);

	start = clock();
	InsertSort_2(a1, 0, n);
	end = clock();
	printf("InsertSort_2 : %u\n", end - start);

	start = clock();
	InsertSort_3(a2, 0, n);
	end = clock();
	printf("InsertSort_3 : %u\n", end - start);
}

#endif /* _SORT_H_ */