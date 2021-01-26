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

void BinTreeCreate(BinTree *t);
void PreOrder(BinTree t);
void InOrder(BinTree t);
void PostOrder(BinTree t);

//ABC##DE##F##G#H##
void BinTreeCreate(BinTree *t)
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
		BinTreeCreate(&((*t)->leftChild));
		BinTreeCreate(&((*t)->rightChild));
	}
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

#endif /* _TREE_H_ */