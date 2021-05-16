#include<iostream>
#include<vector>
using namespace std;


//BST

template<class _Ty>
class BSTree;

template<class _Ty>
class BSTNode
{
	friend class BSTree<_Ty>;
public:
	BSTNode() : data(_Ty()), leftChild(nullptr),rightChild(nullptr)
	{}
	BSTNode(_Ty val, BSTNode *left=nullptr, BSTNode *right=nullptr)
		: data(val), leftChild(left), rightChild(right)
	{}
	~BSTNode()
	{}
private:
	_Ty data;
	BSTNode *leftChild;
	BSTNode *rightChild;
};

template<class _Ty>
class BSTree
{
public:
	BSTree() : root(nullptr)
	{}
	BSTree(vector<_Ty> &nums) : root(nullptr)
	{
		for(const auto &e : nums)
			Insert(e);
	}
public:
	void Order()const
	{
		Order(root);
	}
	BSTNode<_Ty>* Min()const
	{
		return Min(root);
	}
	BSTNode<_Ty>* Max()const
	{
		return Max(root);
	}
	BSTNode<_Ty>* Search(const _Ty &key)const
	{
		return Search(root, key);
	}
	BSTNode<_Ty>* Parent(BSTNode<_Ty> *key)const
	{
		return Parent(root, key);
	}
	bool Insert(const _Ty &x)
	{
		return Insert(root, x);  //
	}
	bool Remove(const _Ty &key)
	{
		return Remove(root, key);
	}
protected:
	void Order(BSTNode<_Ty> *t)const
	{
		if(t != nullptr)
		{
			Order(t->leftChild);
			cout<<t->data<<" ";
			Order(t->rightChild);
		}
	}
	BSTNode<_Ty>* Parent(BSTNode<_Ty> *t, BSTNode<_Ty> *key)const
	{
		if(t==nullptr || key==t)
			return nullptr;
		if(key==t->leftChild || key==t->rightChild)
			return t;
		if(key->data < t->data)
			return Parent(t->leftChild, key);
		else if(key->data > t->data)
			return Parent(t->rightChild, key);
	}
	BSTNode<_Ty>* Search(BSTNode<_Ty> *t, const _Ty &key)const
	{
		if(t == nullptr)
			return t;
		if(key < t->data)
			return Search(t->leftChild, key);
		else if(key > t->data)
			return Search(t->rightChild, key);
		return t;
	}
	BSTNode<_Ty>* Min(BSTNode<_Ty> *t)const
	{
		while(t && t->leftChild != nullptr)
			t = t->leftChild;
		return t;
	}
	BSTNode<_Ty>* Max(BSTNode<_Ty> *t)const
	{
		while(t && t->rightChild != nullptr)
			t = t->rightChild;
		return t;
	}
	bool Insert(BSTNode<_Ty> *&t, int x)
	{
		if(t == nullptr)
		{
			t = new BSTNode<_Ty>(x);
			return true;
		}
		if(x < t->data)
			return Insert(t->leftChild, x);
		else if(x > t->data)
			return Insert(t->rightChild, x);

		return false;
	}
	bool Remove(BSTNode<_Ty> *&t, const _Ty &key)
	{
		if(t == nullptr)
			return false;
		BSTNode<_Ty> *p = t, *pr=nullptr;
		while(p != nullptr)
		{
			if(key == p->data)
				break;
			pr = p;
			if(key < p->data)
				p = p->leftChild;
			else
				p = p->rightChild;
		}

		if(p->leftChild!=nullptr && p->rightChild!=nullptr)
		{
			BSTNode<_Ty> *q = p->leftChild;
			while(q->rightChild != nullptr)
			{
				pr = q;
				q = q->rightChild;
			}
			p->data = q->data;
			p = q;
		}

		if(pr == nullptr)
		{
			if(p->leftChild != nullptr)
				t = p->leftChild;
			else
				t = p->rightChild;
		}
		else
		{
			if(pr->leftChild == p)
			{
				if(p->leftChild != nullptr)
					pr->leftChild = p->leftChild;
				else
					pr->leftChild = p->rightChild;
			}
			else
			{
				if(p->leftChild != nullptr)
					pr->rightChild = p->leftChild;
				else
					pr->rightChild = p->rightChild;
			}
		}
		delete p;
	}
private:
	BSTNode<_Ty> *root;
};

void main()
{
	//vector<int> iv{5,3,4,1,7,8,2,6,0,9};
	//vector<int> iv{50,30,40,10,70,80,2,60,90 };
	vector<int> iv{50,30,40};
	BSTree<int> bst(iv);

	BSTNode<int> *p = bst.Search(10);
	BSTNode<int> *pr = bst.Parent(p);

	bst.Remove(50);
	return;
}

/*
bool Remove(BSTNode<_Ty> *&t, const _Ty &key)
	{
		if(t == nullptr)
			return false;
		BSTNode<_Ty> *p = Search(t, key);
		if(p == nullptr)
			return false;

		if(p->leftChild!=nullptr && p->rightChild!=nullptr)
		{
			BSTNode<_Ty> *q = p->leftChild;
			while(q->rightChild != nullptr)
				q = q->rightChild;
			p->data = q->data;
			p = q;
		}

		BSTNode<_Ty> *pr = Parent(t, p);
		if(pr == nullptr) //删除根节点
		{
			if(p->leftChild != nullptr)
				t = p->leftChild;
			else
				t = p->rightChild;
		}
		else
		{
			if(pr->leftChild == p)
			{
				if(p->leftChild != nullptr)
					pr->leftChild = p->leftChild;
				else
					pr->leftChild = p->rightChild;
			}
			else
			{
				if(p->leftChild != nullptr)
					pr->rightChild = p->leftChild;
				else
					pr->rightChild = p->rightChild;
			}
		}
		delete p;
	}

bool Remove(BSTNode<_Ty> *&t, const _Ty &key)
	{
		if(t == nullptr)
			return false;
		if(key < t->data)
			return Remove(t->leftChild, key);
		else if(key > t->data)
			return Remove(t->rightChild, key);
		else
		{
			BSTNode<_Ty> *p = nullptr;
			//找到了， 删除
			if(t->leftChild!=nullptr && t->rightChild!=nullptr)
			{
				p = t->leftChild;
				while(p->rightChild != nullptr)
					p = p->rightChild;
				t->data = p->data;
				Remove(t->leftChild, p->data);
			}
			else
			{
				p = t;
				if(t->leftChild != nullptr)
					t = t->leftChild;
				else
					t = t->rightChild;
				delete p;
			}
			return true;
		}
	}

bool Remove(BSTNode<_Ty> *&t, const _Ty &key)
	{
		if(t == nullptr)
			return false;
		if(key < t->data)
			return Remove(t->leftChild, key);
		else if(key > t->data)
			return Remove(t->rightChild, key);
		else
		{
			BSTNode<_Ty> *p = nullptr;
			//找到了， 删除
			if(t->leftChild==nullptr && t->rightChild==nullptr)
			{
				delete t;
				t = nullptr;
			}
			else if(t->leftChild!=nullptr && t->rightChild==nullptr)
			{
				p = t;
				t = t->leftChild;
				delete p;
			}
			else if(t->leftChild==nullptr && t->rightChild!=nullptr)
			{
				p = t;
				t = t->rightChild;
				delete p;
			}
			else
			{
				p = t->leftChild;
				while(p->rightChild != nullptr)
					p = p->rightChild;
				t->data = p->data;
				Remove(t->leftChild, p->data);
			}
			return true;
		}
	}

void main()
{
	vector<int> iv{5,3,4,1,7,8,2,6,0,9};
	BSTree<int> bst;
	for(int i=0; i<iv.size(); ++i)
		bst.Insert(iv[i]);
	return;
}

/*
class A
{
public:
	virtual void func(int val=0)
	{ 
		std::cout << "A->" << val << std::endl;
	}
	virtual void test()
	{
		func(); //
	}
};
class B : public A
{
public:
	void func(int val=1)
	{
		std::cout << "B->" << val<< std::endl; 
	}
};

int main(int argc, char* argv[])
{
	B *p = new B;
	p->test();
	return 0;
}

/*
class Base1 
{
public: 
	int _b1; 
};
class Base2 
{ 
public: 
	int _b2; 
};

class Derive : public Base2, public Base1 
{
public: 
	int _d;
};
int main()
{
	Derive d;

	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;
	return 0;
}

/*
class A
{
public:
	A(char *s) { cout << s << endl; }
	~A(){}
};
class B :virtual public A
{
public:
	B(char *s1, char*s2) :A(s1) { cout << s2 << endl; }
};
class C :virtual public A
{
public:
	C(char *s1, char*s2) :A(s1) { cout << s2 << endl; }
};
class D :public B, public C
{
public:
	D(char *s1, char *s2, char *s3, char *s4) :B(s1, s2), C(s1, s3), A(s1)
	{
		cout << s4 << endl;
	}
};
int main() {
	D *p = new D("class A", "class B", "class C", "class D");
	delete p;
	return 0;
}
*/