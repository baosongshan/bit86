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

//直接插入排序-哨兵位
void InsertSort_4(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		ar[0] = ar[i];  //哨兵位
		int j = i;
		while(ar[0] < ar[j-1])
		{
			ar[j] = ar[j-1];
			j--;
		}
		ar[j] = ar[0];
	}
}

//折半插入排序
void BinInsertSort(int *ar, int left, int right)
{
	for(int i=left+1; i<right; ++i)
	{
		int tmp = ar[i];
		int low = left;
		int high = i-1;
		int mid;
		while(low <= high)  //折半查找插入位置
		{
			mid = (low + high) / 2;
			if(tmp >= ar[mid])
				low = mid + 1;
			if(tmp < ar[mid])
				high = mid - 1;
		}

		for(int j=i; j>low; --j)
			ar[j] = ar[j-1];

		ar[low] = tmp;
	}
}
//二路插入排序   空间复杂度 O(n)
void TwoWayInsertSort(int *ar, int left, int right)
{
	int n = right - left;
	int *tmp = (int*)malloc(sizeof(int) * n);

	tmp[0] = ar[left];
	int first, final;
	first = final = 0;

	for(int i=left+1; i<right; ++i)
	{
		if(ar[i] < tmp[first])
		{
			first = (first-1+n) % n;
			tmp[first] = ar[i];
		}
		else if(ar[i] >= tmp[final])
		{
			tmp[++final] = ar[i];
		}
		else
		{
			int end = final;
			while(ar[i] < tmp[end])
			{
				tmp[(end+1)%n] = tmp[end];
				end = (end-1+n) % n;
			}
			tmp[(end+1)%n] = ar[i];
			final++;
		}
	}

	int k = 0;
	for(int i=first; k<n; ++k)
	{
		ar[k] = tmp[i];
		i = (i+1) % n;
	}
	free(tmp);
}

//希尔排序
/*
void _ShellInsert(int *ar, int left, int right, int gap)
{
	for(int i=left+gap; i<right; ++i)
	{
		int tmp = ar[i];
		int j = i;
		while(j>left && tmp < ar[j-gap])
		{
			ar[j] = ar[j-gap];
			j -= gap;
		}
		ar[j] = tmp;
	}
}

int dlta[] = {5, 3, 2, 1};  //素数
void ShellSort(int *ar, int left, int right)
{
	int n = sizeof(dlta) / sizeof(dlta[0]); //增量的个数
	for(int i=0; i<n; ++i)
	{
		_ShellInsert(ar, left, right, dlta[i]);
	}
}
*/

void ShellSort(int *ar, int left, int right)
{
	int gap = right - left;
	while(gap > 1)
	{
		gap = gap / 3 + 1; //4  2  1  设计文档
		for(int i=left+gap; i<right; ++i)
		{
			if(ar[i] < ar[i-gap])
			{
				int tmp = ar[i];
				int j = i;
				while(j>left && tmp<ar[j-gap])
				{
					ar[j] = ar[j-gap];
					j = j-gap;
				}

				ar[j] = tmp;
			}
		}
	}
}

//简单选择排序
int GetMinIndex(int *ar, int left, int right)
{
	int min_value = ar[left];
	int index = left;

	for(int i=left+1; i<right; ++i)
	{
		if(ar[i] < min_value)
		{
			min_value = ar[i];
			index = i;
		}
	}
	return index;
}

void SelectSort(int *ar, int left, int right)
{
	for(int i=left; i<right-1; ++i)
	{
		int index = GetMinIndex(ar, i, right);
		if(index != i)
			Swap(&ar[i], &ar[index]);
	}
}

//堆排
void _AdjustDown(int *ar, int left, int right, int start)
{
	int n = right - left;
	int i = start;    //代表父节点
	int j = 2*i + 1;  //代表i节点的左子树

	int tmp = ar[i];

	while(j < n)
	{
		if(j+1<n && ar[j]<ar[j+1])
			j = j+1;

		if(tmp < ar[j])
		{
			ar[i] = ar[j];
			i = j;
			j = 2*i + 1;
		}
		else
			break;
	}

	ar[i] = tmp;
}
void HeapSort(int *ar, int left, int right)
{
	int n = right - left;
	int curpos = n/2 - 1+left; //找到二叉树的最后一个分支
	while(curpos >= 0)
	{
		_AdjustDown(ar, left, right, curpos);
		curpos--;
	}

	//排序
	int end = right-1;
	while(end > left)
	{
		Swap(&ar[left], &ar[end]); //出堆
		_AdjustDown(ar, left, end, 0);
		end--;
	}
}

void TestSortEfficient()
{
	int n = 10000;
	int *a = (int*)malloc(sizeof(int) * n);
	int *a1 = (int *)malloc(sizeof(int) * n);
	int *a2 = (int *)malloc(sizeof(int) * n);
	int *a3 = (int *)malloc(sizeof(int) * n);
	int *a4 = (int *)malloc(sizeof(int) * n);
	int *a5 = (int *)malloc(sizeof(int) * n);
	int *a6 = (int *)malloc(sizeof(int) * n);
	int *a7 = (int *)malloc(sizeof(int) * n);
	int *a8 = (int *)malloc(sizeof(int) * n);
	srand(time(0));
	for(int i=0; i<n; ++i)
	{
		a[i] = rand();
		a1[i] = a[i];
		a2[i] = a[i];
		a3[i] = a[i];
		a4[i] = a[i];
		a5[i] = a[i];
		a6[i] = a[i];
		a7[i] = a[i];
		a8[i] = a[i];
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

	start = clock();
	InsertSort_4(a3, 0, n);
	end = clock();
	printf("InsertSort_4 : %u\n", end - start);

	start = clock();
	BinInsertSort(a4, 0, n);
	end = clock();
	printf("BinInsertSort : %u\n", end - start);

	start = clock();
	TwoWayInsertSort(a5, 0, n);
	end = clock();
	printf("TwoWayInsertSort : %u\n", end - start);
	
	start = clock();
	ShellSort(a6, 0, n);
	end = clock();
	printf("ShellSort : %u\n", end - start);

	start = clock();
	SelectSort(a7, 0, n);
	end = clock();
	printf("SelectSort : %u\n", end - start);

	start = clock();
	HeapSort(a8, 0, n);
	end = clock();
	printf("HeapSort : %u\n", end - start);
}

#endif /* _SORT_H_ */