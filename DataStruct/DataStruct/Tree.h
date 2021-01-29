#ifndef _TREE_H_
#define _TREE_H_

#include"Sysutil.h"

#define TreeElemType char

//定义树形节点
typedef struct BinTreeNode
{
	TreeElemType data;
	struct BinTreeNode *leftChild;
	struct BinTreeNode *rightChild;
}BinTreeNode;

//定义树形结构
typedef BinTreeNode* BinTree;

void BinTreeInit(BinTree *t);
void BinTreeCreate_1(BinTree *t);
BinTree BinTreeCreate_2();
BinTree BinTreeCreate_3(const char *str, int *i);
BinTree BinTreeCreate_VLR_LVR(const char *vlr, const char *lvr, int n);
BinTree BinTreeCreate_LVR_LRV(const char *lvr, const char *lrv, int n);

//递归遍历
void PreOrder(BinTree t);
void InOrder(BinTree t);
void PostOrder(BinTree t);
void LevelOrder(BinTree t);

//非递归遍历
void PreOrder_Nor(BinTree t);
void InOrder_Nor(BinTree t);
void PostOrder_Nor(BinTree t);


size_t Size(BinTree t);
size_t Height(BinTree t);
BinTreeNode* Find(BinTree t, TreeElemType key);
BinTreeNode* Parent(BinTree t, BinTreeNode *s);

BinTree Clone(BinTree t);
bool    Equal(BinTree t1, BinTree t2);

void BinTreeInit(BinTree *t)
{
	*t = NULL;
}

//ABC##DE##F##G#H##  按照前序创建二叉树
void BinTreeCreate_1(BinTree *t)
{
	TreeElemType item;
	scanf("%c", &item);
	if(item == '#')
		*t = NULL;
	else
	{
		*t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(*t != NULL);
		(*t)->data = item;
		BinTreeCreate_1(&((*t)->leftChild));
		BinTreeCreate_1(&((*t)->rightChild));
	}
}

BinTree BinTreeCreate_2()
{
	TreeElemType item;
	scanf("%c", &item);
	if(item == '#')
		return NULL;
	else
	{
		BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = item;
		t->leftChild = BinTreeCreate_2();
		t->rightChild = BinTreeCreate_2();
		return t;
	}
}

//"ABC##DE##F##G#H##";
BinTree BinTreeCreate_3(const char *str, int *i)
{
	if(str[*i]=='#' || str[*i]=='\0')
		return NULL;
	else
	{
		BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(t != NULL);
		t->data = str[*i];
		(*i)++;
		t->leftChild = BinTreeCreate_3(str, i);
		(*i)++;
		t->rightChild = BinTreeCreate_3(str, i);
		return t;
	}
}

BinTree BinTreeCreate_VLR_LVR(const char *vlr, const char *lvr, int n)
{
	if(n == 0)
		return NULL;
	
	int k = 0;
	while(lvr[k] != vlr[0])
		k++;

	BinTreeNode *t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
	assert(t != NULL);
	t->data = lvr[k];

	t->leftChild = BinTreeCreate_VLR_LVR(vlr+1, lvr, k);
	t->rightChild = BinTreeCreate_VLR_LVR(vlr+k+1, lvr+k+1, n-k-1);

	return t;
}

BinTree BinTreeCreate_LVR_LRV(const char *lvr, const char *lrv, int n)
{
	//同学自行完成

	//1、现从后续在中序中找到根节点
	//2、先创建右树
	//3、在创建左树

	return NULL;
}

void PreOrder(BinTree t)
{
	if(t != NULL)
	{
		printf("%c ", t->data);
		PreOrder(t->leftChild);
		PreOrder(t->rightChild);
	}
}
void InOrder(BinTree t)
{
	if(t != NULL)
	{
		InOrder(t->leftChild);
		printf("%c ", t->data);
		InOrder(t->rightChild);
	}
}
void PostOrder(BinTree t)
{
	if(t != NULL)
	{
		PostOrder(t->leftChild);
		PostOrder(t->rightChild);
		printf("%c ", t->data);
	}
}

#include"Stack.h"
void PreOrder_Nor(BinTree t)
{
	if(t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		LinkStackPush(&st, t);
		while(!LinkStackEmpty(&st))
		{
			BinTreeNode *p = LinkStackTop(&st);
			LinkStackPop(&st);

			printf("%c ", p->data);
			if(p->rightChild != NULL)
				LinkStackPush(&st, p->rightChild);
			if(p->leftChild != NULL)
				LinkStackPush(&st, p->leftChild);
		}
	}
}

void InOrder_Nor(BinTree t)
{
	if(t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		BinTreeNode *p;

		LinkStackPush(&st, t);

		while(!LinkStackEmpty(&st))
		{
			while(t && t->leftChild != NULL)
			{
				LinkStackPush(&st, t->leftChild);
				t = t->leftChild;
			}

			p = LinkStackTop(&st);
			LinkStackPop(&st);
			printf("%c ", p->data);
			
			t = p->rightChild;
			if(t != NULL)
				LinkStackPush(&st, t);
		}
	}
}

void PostOrder_Nor(BinTree t)
{
	if(t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		BinTreeNode *p, *prev; //prev代表当前节点的前驱访问节点
		while(t || !LinkStackEmpty(&st))
		{
			while(t)
			{
				LinkStackPush(&st, t);
				t = t->leftChild;
			}

			p = LinkStackTop(&st);
			if(p->rightChild==NULL || p->rightChild==prev)
			{
				printf("%c ", p->data);
				LinkStackPop(&st); //要访问
				prev = p; //更新prev访问节点
			}
			else
				t = p->rightChild;
		}
	}
}


#include"Queue.h"
void LevelOrder(BinTree t)
{
	if(t != NULL)
	{
		LinkQueue Q;
		LinkQueueInit(&Q);

		LinkQueueEn(&Q, t);
		while(!LinkQueueEmpty(&Q))
		{
			BinTreeNode *p = LinkQueueFront(&Q);
			LinkQueueDe(&Q);
			printf("%c ", p->data);
			if(p->leftChild != NULL)
				LinkQueueEn(&Q, p->leftChild);
			if(p->rightChild != NULL)
				LinkQueueEn(&Q, p->rightChild);
		}
	}
}

size_t Size(BinTree t)
{
	if(t == NULL)
		return 0;
	else
		return Size(t->leftChild) + Size(t->rightChild) + 1;
}

size_t Height(BinTree t)
{
	if (t == NULL)
		return 0;
	else
	{
		int left_h = Height(t->leftChild);
		int right_h = Height(t->rightChild);
		return (left_h > right_h ? left_h : right_h)+1;
	}
}

BinTreeNode* Find(BinTree t, TreeElemType key)
{
	BinTreeNode *p;

	if(t==NULL || t->data==key)
		return t;
	
	p = Find(t->leftChild, key);
	if(p != NULL) //说明在左树找到了
		return p;
	return Find(t->rightChild, key);
}

BinTreeNode* Parent(BinTree t, BinTreeNode *s)
{
	BinTreeNode* p;

	if (t==NULL || t==s) //t==s是用于判断是否求的是根节点的父节点
		return NULL;

	if (t->leftChild == s || t->rightChild == s)
		return t;
	p = Parent(t->leftChild, s);
	if (p != NULL)
		return p;
	return Parent(t->rightChild, s);
}

BinTree Clone(BinTree t) 
{
	if(t == NULL)
		return NULL;
	else
	{
		BinTreeNode *new_t = (BinTreeNode*)malloc(sizeof(BinTreeNode));
		assert(new_t != NULL);
		new_t->data = t->data;
		new_t->leftChild = Clone(t->leftChild);
		new_t->rightChild = Clone(t->rightChild);

		return new_t;
	}
}

bool    Equal(BinTree t1, BinTree t2)
{
	if(t1==NULL && t2==NULL)
		return true;
	if(t1==NULL || t2==NULL)
		return false;

	return (t1->data==t2->data)
		   && Equal(t1->leftChild, t2->leftChild)
		   && Equal(t1->rightChild, t2->rightChild);
}

#endif /* _TREE_H_ */

/*
void InOrder_Nor(BinTree t)
{
	if(t != NULL)
	{
		LinkStack st;
		LinkStackInit(&st);

		BinTreeNode *p;

		while(t || !LinkStackEmpty(&st))
		{
			while(t)
			{
				LinkStackPush(&st, t);
				t = t->leftChild;
			}

			p = LinkStackTop(&st);
			LinkStackPop(&st);
			printf("%c ", p->data);
			
			t = p->rightChild;
		}
	}
}
*/