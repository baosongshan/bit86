#include<iostream>
#include<vector>
#include<stack>
using namespace std;

template<class Type>
class AVLTree;

template<class Type>
class AVLNode
{
	friend class AVLTree<Type>;
public:
	AVLNode():data(Type()),leftChild(nullptr),rightChild(nullptr),bf(0)
	{}
	AVLNode(Type d, AVLNode *left=nullptr, AVLNode *right=nullptr)
		:data(d),leftChild(left),rightChild(right),bf(0)
	{}
	~AVLNode()
	{}
private:
	Type data;
	AVLNode *leftChild;
	AVLNode *rightChild;
	int      bf;
};

template<class Type>
class AVLTree
{
public:
	AVLTree() : root(nullptr)
	{}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
	bool Remove(const Type &x)
	{
		return Remove(root, x);
	}
protected:
	bool Insert(AVLNode<Type> *&t, const Type &x);
	bool Remove(AVLNode<Type> *&t, const Type &key);
protected:
	void RotateL(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subL = ptr;
		ptr = subL->rightChild;
		subL->rightChild = ptr->leftChild;
		ptr->leftChild = subL;
		ptr->bf = subL->bf = 0;
	}
	void RotateR(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subR = ptr;
		ptr = subR->leftChild;
		subR->leftChild = ptr->rightChild;
		ptr->rightChild = subR;
		ptr->bf = subR->bf = 0;
	}
	void RotateLR(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subL, *subR;
		subR = ptr;
		subL = ptr->leftChild;
		ptr = subL->rightChild;

		//L
		subL->rightChild = ptr->leftChild;
		ptr->leftChild = subL;
		//调整subL bf
		if(ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		subR->leftChild = ptr->rightChild;
		ptr->rightChild = subR;
		//调整subR bf
		if(ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;

		ptr->bf = 0;
	}
	void RotateRL(AVLNode<Type> *&ptr)
	{
		AVLNode<Type> *subL, *subR;
		subL = ptr;
		subR = ptr->rightChild;
		ptr = subR->leftChild;

		//R
		subR->leftChild = ptr->rightChild;
		ptr->rightChild = subR;
		if(ptr->bf >= 0)
			subR->bf = 0;
		else
			subR->bf = 1;

		//L
		subL->rightChild = ptr->leftChild;
		ptr->leftChild = subL;
		if(ptr->bf <= 0)
			subL->bf = 0;
		else
			subL->bf = -1;

		ptr->bf = 0;
	}
private:
	AVLNode<Type> *root;
};

template<class Type>
bool AVLTree<Type>::Insert(AVLNode<Type> *&t, const Type &x)
{
	//1 先按照BST插入节点
	AVLNode<Type> *p = t;

	AVLNode<Type> *pr = nullptr;
	stack<AVLNode<Type>*> st;

	while(p != nullptr)
	{
		if(x == p->data)
			return false;

		pr = p;
		st.push(pr);

		if(x < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}

	p = new AVLNode<Type>(x);

	if(pr == nullptr)
	{
		t = p;
		return true;
	}

	if(p->data < pr->data)
		pr->leftChild = p;
	else
		pr->rightChild = p;

	//2 调整平衡
	while(!st.empty())
	{
		pr = st.top();
		st.pop();
		if(pr->leftChild == p)
			pr->bf--;
		else 
			pr->bf++;

		if(pr->bf == 0)
			break; //结束调整
		else if(pr->bf==1 || pr->bf==-1)
			p = pr; //向上回溯
		else
		{
			//不平衡，需要调整平衡
			if(pr->bf < 0)
			{
				if(p->bf < 0)  //   /
				{
					//cout<<"RotateR."<<endl;
					RotateR(pr);
				}
				else           //   <
				{
					//cout<<"RotateLR"<<endl;
					RotateLR(pr);
				}
			}
			else
			{
				if(p->bf > 0)   //  \ 
				{
					//cout<<"RotateL"<<endl;
					RotateL(pr);
				}
				else             //  >
				{
					//cout<<"RotateRL"<<endl;
					RotateRL(pr);
				}
			}
			break;
		}
	}

	if(st.empty())
		t = pr;
	else
	{
		AVLNode<Type> *q = st.top();
		if(pr->data< q->data)
			q->leftChild = pr;
		else
			q->rightChild = pr;
	}

	return true;
}

template<class Type>
bool AVLTree<Type>::Remove(AVLNode<Type> *&t, const Type &key)
{
	//1 根据BST删除节点
	AVLNode<Type> *pr = nullptr;
	AVLNode<Type> *p = t, *q=nullptr;

	stack<AVLNode<Type>*> st;

	while(p != nullptr)
	{
		if(p->data == key)
			break;

		pr = p;
		st.push(pr);

		if(key < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if(p == nullptr)
		return false;

	if(p->leftChild!=nullptr && p->rightChild!=nullptr)
	{
		q = p->leftChild;
		pr = p;
		st.push(pr);
		while(q->rightChild != nullptr)
		{
			pr = q;
			st.push(pr);
			q = q->rightChild;
		}
		p->data = q->data;
		p = q;
	}

	//p是要删除的节点 q是p节点子女节点
	if(p->leftChild != nullptr)
		q = p->leftChild;
	else
		q = p->rightChild;

	if(pr == nullptr)
	{
		t = q;
	}
	else
	{
		//断开p节点
		if(p == pr->leftChild)
			pr->leftChild = q;
		else
			pr->rightChild = q;
	}

	//2 平衡BST
	bool is_break_flag = false;
	while(!st.empty())
	{
		pr = st.top();
		st.pop();

		if(p->data < pr->data)
			pr->bf++;
		else
			pr->bf--;

		//考察pr的bf
		if(pr->bf==1 || pr->bf==-1)
			break;
		if(pr->bf == 0)
			q = pr;
		else
		{
			//|bf| == 2
			//让q指向pr的较高子树
			if(pr->bf < 0)
				q = pr->leftChild; //左树高
			else
				q = pr->rightChild;//右树高

			if(q->bf == 0)//单旋转
			{
				if(pr->bf < 0)
				{
					RotateR(pr);
					pr->bf = 1;
					pr->rightChild->bf = -1;
				}
				else
				{
					RotateL(pr);
					pr->bf = -1;
					pr->leftChild->bf = 1;
				}
				is_break_flag = true;
			}
			else
			{			
				if (pr->bf < 0)
				{
					if (q->bf < 0)  //   /
						RotateR(pr);
					else           //   <
						RotateLR(pr);
				}
				else
				{
					if (q->bf > 0)  //   \ 
						RotateL(pr);
					else           //   >
						RotateRL(pr);
				}

			}
			//重新链接
			if(st.empty())
				t = pr;
			else
			{
				q = st.top();
				if(pr->data < q->data)
					q->leftChild = pr;
				else
					q->rightChild = pr;
			}
			if(is_break_flag)
				break;
		}
	}
	delete p;
	return true;
}

void main()
{
	vector<int> iv{16, 3, 7, 11, 9, 26, 18, 14, 15};
	//vector<int> iv{16, 3, 7};
	AVLTree<int> avl;

	for(const auto &e : iv)
		avl.Insert(e);

	//avl.Remove(3);
	avl.Remove(16);
	avl.Remove(26);

	return;
}

/*
template<class Type>
bool AVLTree<Type>::Remove(AVLNode<Type> *&t, const Type &key)
{
	//1 根据BST删除节点
	AVLNode<Type> *pr = nullptr;
	AVLNode<Type> *p = t, *q=nullptr;
	AVLNode<Type> *Nil = new AVLNode<Type>(0);

	stack<AVLNode<Type>*> st;

	while(p != nullptr)
	{
		if(p->data == key)
			break;

		pr = p;
		st.push(pr);

		if(key < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if(p == nullptr)
		return false;

	if(p->leftChild!=nullptr && p->rightChild!=nullptr)
	{
		q = p->leftChild;
		pr = p;
		st.push(pr);
		while(q->rightChild != nullptr)
		{
			pr = q;
			st.push(pr);
			q = q->rightChild;
		}
		p->data = q->data;
		p = q;
	}

	//p是要删除的节点 q是p节点子女节点
	if(p->leftChild != nullptr)
		q = p->leftChild;
	else if(p->rightChild != nullptr)
		q = p->rightChild;
	else 
		q = Nil;

	bool isLeftChild = false;
	if(pr == nullptr)
	{
		if(q == Nil)
			t = nullptr;
		else
			t = q;
	}
	else
	{
		//断开p节点
		if(p == pr->leftChild)
		{
			if(q != Nil)
				pr->leftChild = q;
			else
				pr->leftChild = nullptr;
			isLeftChild = true;
		}
		else if(q != Nil)
			pr->rightChild = q;
		else
			pr->rightChild = nullptr;

	}

	//2 平衡BST
	while(!st.empty())
	{
		pr = st.top();
		st.pop();

		if(q == pr->leftChild || isLeftChild)
			pr->bf++;
		else
			pr->bf--;

		//考察pr的bf
		if(pr->bf==1 || pr->bf==-1)
			break;
		if(pr->bf == 0)
			q = pr;
		else
		{
			//|bf| == 2
			//让q指向pr的较高子树
			if(pr->bf < 0)
				q = pr->leftChild; //左树高
			else
				q = pr->rightChild;//右树高

			if(q->bf == 0)//单旋转
			{
				if(pr->bf < 0)
				{
					RotateR(pr);
					pr->bf = 1;
					pr->rightChild->bf = -1;
				}
				else
				{
					RotateL(pr);
					pr->bf = -1;
					pr->leftChild->bf = 1;
				}
			}
			else if(pr->bf < 0)
			{
				if(q->bf < 0)  //   /
				{
					RotateR(pr);
				}
				else           //   <
				{
					RotateLR(pr);
				}
			}
			else if(pr->bf > 0)
			{
				if(q->bf > 0)  //   \ 
				{
					RotateL(pr);
				}
				else           //   >
				{
					RotateRL(pr);
				}
			}

			//重新链接
			if(st.empty())
				t = pr;
			else
			{
				q = st.top();
				if(pr->data < q->data)
					q->leftChild = pr;
				else
					q->rightChild = pr;
			}
			break;
		}
	}
	delete p;
	delete Nil;
	return true;
}


template<class Type>
bool AVLTree<Type>::Remove(AVLNode<Type> *&t, const Type &key)
{
	//1 根据BST删除节点
	AVLNode<Type> *pr = nullptr;
	AVLNode<Type> *p = t, *q=nullptr;
	AVLNode<Type> *Nil = new AVLNode<Type>(0);

	stack<AVLNode<Type>*> st;

	while(p != nullptr)
	{
		if(p->data == key)
			break;

		pr = p;
		st.push(pr);

		if(key < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if(p == nullptr)
		return false;

	if(p->leftChild!=nullptr && p->rightChild!=nullptr)
	{
		q = p->leftChild;
		pr = p;
		st.push(pr);
		while(q->rightChild != nullptr)
		{
			pr = q;
			st.push(pr);
			q = q->rightChild;
		}
		p->data = q->data;
		p = q;
	}

	//p是要删除的节点 q是p节点子女节点
	if(p->leftChild != nullptr)
		q = p->leftChild;
	else if(p->rightChild != nullptr)
		q = p->rightChild;
	else 
		q = Nil;

	if(pr == nullptr)
		t = q;
	else
	{
		//断开p节点
		if(p == pr->leftChild)
		{
			if(q != Nil)
				pr->leftChild = q;
			else
				pr->leftChild = nullptr;
		}
		else if(q != Nil)
			pr->rightChild = q;
		else
			pr->rightChild = nullptr;

	}

	//2 平衡BST
	while(!st.empty())
	{
		pr = st.top();
		st.pop();

		if(q == pr->leftChild || q==Nil)
			pr->bf++;
		else
			pr->bf--;

		//考察pr的bf
		if(pr->bf==1 || pr->bf==-1)
			break;
		if(pr->bf == 0)
			q = pr;
		else
		{
			//|bf| == 2
			//让q指向pr的较高子树
			if(pr->bf < 0)
				q = pr->leftChild; //左树高
			else
				q = pr->rightChild;//右树高

			if(q->bf == 0)//单旋转
			{
				if(pr->bf < 0)
				{
					RotateR(pr);
					pr->bf = 1;
					pr->rightChild->bf = -1;
				}
				else
				{
					RotateL(pr);
					pr->bf = -1;
					pr->leftChild->bf = 1;
				}
			}
			else if(pr->bf < 0)
			{
				if(q->bf < 0)  //   /
				{
					RotateR(pr);
				}
				else           //   <
				{
					RotateLR(pr);
				}
			}
			else if(pr->bf > 0)
			{
				if(q->bf > 0)  //   \ 
				{
					RotateL(pr);
				}
				else           //   >
				{
					RotateRL(pr);
				}
			}

			//重新链接
			if(st.empty())
				t = pr;
			else
			{
				q = st.top();
				if(pr->data < q->data)
					q->leftChild = pr;
				else
					q->rightChild = pr;
			}
			break;
		}
	}
	delete p;
	delete Nil;
	return true;
}

*/