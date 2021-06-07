#include<iostream>
#include<vector>
#include<string>
using  namespace std;

typedef enum{RED=0, BLACK}Color_Type;

template<class Type>
class RBTree;

template<class Type>
class rb_iterator;

template<class Type>
class RBNode
{
	friend class rb_iterator<Type>;
	friend class RBTree<Type>;
public:
	RBNode()
		:data(Type()),leftChild(nullptr),
		rightChild(nullptr),parent(nullptr),color(RED)
	{}
	RBNode(Type d)
		:data(d),leftChild(nullptr),
		rightChild(nullptr),parent(nullptr),color(RED)
	{}
	~RBNode()
	{}
private:
	Type data;
	RBNode<Type> *leftChild;
	RBNode<Type> *rightChild;
	RBNode<Type> *parent;
	Color_Type    color;
};

/////////////////////////////////////////////////////////////////
template<class Type>
class rb_iterator
{
public: 
	rb_iterator(RBNode<Type> *n=nullptr, 
				RBNode<Type>*nil=nullptr,
				RBNode<Type> *end=nullptr) 
		: cur(n),Nil(nil),end_node(end)
	{}
public:
	rb_iterator& operator++()
	{
		increment();
		return *this;
	}
	rb_iterator& operator--()
	{

	}
	Type& operator*()
	{
		return cur->data;
	}
	Type* operator->()
	{
		return &(cur->data);
	}

	bool operator!=(const rb_iterator<Type> &rbit)
	{
		return cur != rbit.cur;
	}
	bool operator==(const rb_iterator<Type> &rbit)
	{
		return cur == rbit.cur;
	}
protected:
	void increment()
	{
		if(cur->rightChild != Nil)
		{
			cur = cur->rightChild;
			if(cur == end_node)
				return;
			while(cur->leftChild != Nil)
				cur = cur->leftChild;
		}
		else
		{
			RBNode<Type> *pr = cur->parent;
			while(cur == pr->rightChild)
			{
					cur = pr;
					pr = cur->parent;
			}
			if(pr->rightChild != cur)
				cur = pr;
		}
	}
	void decrement()
	{

	}
private:
	RBNode<Type> *cur;
	RBNode<Type> *Nil;
	RBNode<Type> *end_node;
};
/////////////////////////////////////////////////////////////////

template<class Type>
class RBTree
{
public:
	typedef rb_iterator<Type> iterator;
public:
	RBTree():root(Nil),Nil(_Buynode()),end_node(_Buynode())
	{
		Nil->leftChild = Nil->rightChild = Nil->parent = nullptr;
		Nil->color = BLACK;
		end_node->leftChild = end_node->rightChild = end_node->parent = nullptr;
	}
public:
	size_t size()const
	{
		return size(root);
	}
protected:
	size_t size(RBNode<Type> *t)const
	{
		if(t == Nil)
			return 0;
		else 
			return size(t->leftChild) + size(t->rightChild) + 1;
	}
public:
	iterator begin()
	{
		RBNode<Type> *p = root;
		while(p!=Nil && p->leftChild!=Nil)
			p = p->leftChild;
		return iterator(p,Nil,end_node);
	}
	iterator end()
	{
		return iterator(end_node,Nil,end_node);
	}
	void set_end_node()
	{
		RBNode<Type> *p = root;
		while(p!=Nil && p->rightChild != Nil)
			p = p->rightChild;
		p->rightChild = end_node;
	}
public:
	bool Insert(const Type &x)
	{
		return Insert(root, x);
	}
	bool Remove(const Type &key)
	{
		return Remove(root, key);
	}
protected:
	bool Insert(RBNode<Type> *&t, const Type &x);
	bool Remove(RBNode<Type> *&t, const Type &key);
protected:
	void Insert_Fixup(RBNode<Type> *&t, RBNode<Type> *x);
	void Remove_Fixup(RBNode<Type> *&t, RBNode<Type> *x);
protected:
	void RotateR(RBNode<Type> *&t, RBNode<Type> *x)
	{
		RBNode<Type> *y = x->leftChild;
		x->leftChild = y->rightChild;
		if(y->rightChild != Nil)
			y->rightChild->parent = x;

		if(x == t)
			t = y;
		else if(x == x->parent->leftChild)
			x->parent->leftChild = y;
		else 
			x->parent->rightChild = y;

		y->parent = x->parent;

		y->rightChild = x;
		x->parent = y;
	}
	void RotateL(RBNode<Type> *&t, RBNode<Type> *x)
	{
		RBNode<Type> *y = x->rightChild;
		x->rightChild = y->leftChild;
		if(y->leftChild != Nil)
			y->leftChild->parent = x;
		if(x == t)
			t = y;
		else if(x == x->parent->leftChild)
			x->parent->leftChild = y;
		else
			x->parent->rightChild = y;

		y->parent = x->parent;
		y->leftChild = x;
		x->parent = y;
	}
protected:
	RBNode<Type>* _Buynode(const Type &x=Type())
	{
		RBNode<Type> *s = new RBNode<Type>(x);
		s->leftChild = s->rightChild = s->parent = Nil;
		return s;
	}
private:
	RBNode<Type> *Nil;  //终端空节点
	RBNode<Type> *root;
	RBNode<Type> *end_node;
};

template<class Type>
bool RBTree<Type>::Insert(RBNode<Type> *&t, const Type &x)
{
	//按照bst的规则插入节点
	RBNode<Type> *s = t;
	RBNode<Type> *pr = Nil;
	while(s != Nil)
	{
		if(s->data == x)
			return false;
		pr = s;
		if(x < s->data)
			s = s->leftChild;
		else
			s = s->rightChild; 
	}

	s = _Buynode(x);
	if(pr == Nil)
		t = s;     //插入跟节点
	else if(x < pr->data)
		pr->leftChild = s;
	else
		pr->rightChild = s;
	s->parent = pr;

	//调整平衡
	Insert_Fixup(t, s);
	return true;
}

template<class Type>
bool RBTree<Type>::Remove(RBNode<Type> *&t, const Type &key)
{
	//1 按照bst的规则删除节点
	RBNode<Type> *p = t, *c; //child
	while(p != Nil)
	{
		if(key == p->data)
			break;
		if(key < p->data)
			p = p->leftChild;
		else
			p = p->rightChild;
	}
	if(p == Nil)
		return false;

	if(p->leftChild!=Nil &&p->rightChild!=Nil)
	{
		RBNode<Type> *q = p->rightChild;
		while(q->leftChild != Nil)
			q = q->leftChild;

		p->data = q->data;
		p = q;
	}

	if(p->leftChild != Nil)
		c = p->leftChild;
	else
		c = p->rightChild;

	//if(c != Nil)
	c->parent = p->parent;
	
	if(p->parent == Nil)
		t = c;
	else if(p == p->parent->leftChild)
		p->parent->leftChild = c;
	else
		p->parent->rightChild = c;
	
	//2 调整平衡
	if(p->color == BLACK)
		Remove_Fixup(t, c);

	delete p;
	return true;
}

template<class Type>
void RBTree<Type>::Insert_Fixup(RBNode<Type> *&t, RBNode<Type> *x)
{
	while(x->parent->color == RED)
	{
		RBNode<Type> *s = Nil;
		if(x->parent == x->parent->parent->leftChild)  //左分支
		{
			s = x->parent->parent->rightChild;
			//情形3
			if(s!=Nil && s->color == RED)
			{
				x->parent->color = BLACK;
				s->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				//情形2
				if(x == x->parent->rightChild)
				{
					x = x->parent;
					RotateL(t, x);
				}
				//情形1
				x->parent->color = BLACK;      //p
				x->parent->parent->color = RED;//g
				RotateR(t, x->parent->parent);
			}
		}
		else //右分支
		{
			s = x->parent->parent->leftChild;
			//情形3
			if(s!=Nil && s->color==RED)
			{
				x->parent->color = BLACK;
				s->color = BLACK;
				x->parent->parent->color = RED;
				x = x->parent->parent;
			}
			else
			{
				//情形2
				if(x == x->parent->leftChild)
				{
					x = x->parent;
					RotateR(t, x);
				}
				//情形1
				x->parent->color = BLACK;
				x->parent->parent->color = RED;
				RotateL(t, x->parent->parent);
			}
		}
	}
	t->color = BLACK;
}

template<class Type>
void RBTree<Type>::Remove_Fixup(RBNode<Type> *&t, RBNode<Type> *x)
{
	RBNode<Type> *w;
	while(x!=t && x->color==BLACK)
	{
		if(x == x->parent->leftChild) //左分支
		{
			w = x->parent->rightChild; //

			//情形4
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				w = w->leftChild;
				RotateL(t, x->parent);
			}

			//情形3
			if(w->leftChild->color!=RED &&w->rightChild->color!=RED)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				//情形2
				if(w->leftChild != Nil)
				{
					w->leftChild->color = BLACK;
					w->color = RED;
					w = w->leftChild;
					RotateR(t, w->parent);
				}
				//情形1
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->rightChild->color = BLACK;
				RotateL(t, x->parent);
				x = t;
			}
		}
		else
		{
			//情形4
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				w = w->rightChild;
				RotateR(t, x->parent);
			}

			//情形3
			if(w->leftChild->color!=RED &&w->rightChild->color!=RED)
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				//情形2
				if(w->rightChild != Nil)
				{
					w->rightChild->color = BLACK;
					w->color = RED;
					w = w->rightChild;
					RotateL(t, w->parent);
				}
				//情形1
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->leftChild->color = BLACK;
				RotateR(t, x->parent);
				x = t;
			}
		}
	}
	x->color = BLACK; //
}

////////////////////////////////////////////////////////////////////////////
template<class Key>
class Set
{
public:
	typedef Key value_type;
	typedef typename RBTree<value_type>::iterator iterator;
public:
	iterator begin()
	{
		return _Tr.begin();
	}
	iterator end()
	{
		return _Tr.end();
	}

public:
	size_t size()const
	{
		return _Tr.size();
	}
	void insert(const value_type &x)
	{
		_Tr.Insert(x);
	}
	void set_end_node()
	{
		_Tr.set_end_node();
	}

private:
	RBTree<value_type> _Tr;
};

template<class Key, class Value>
class Map
{
public:
	typedef pair<Key, Value> value_type;
	typedef typename RBTree<value_type>::iterator iterator;
public:
	iterator begin()
	{
		return _Tr.begin();
	}
	iterator end()
	{
		return _Tr.end();
	}
public:
	size_t size()const
	{
		return _Tr.size();
	}
	void insert(const value_type &x)
	{
		_Tr.Insert(x);
	}
	void set_end_node()
	{
		_Tr.set_end_node();
	}
private:
	RBTree<value_type> _Tr;
};

void main()
{
	pair<int, string> v[] = 
	{{3,"Student"}, {1,"Teacher"}, {5,"Firend"},{2,"Family"}};

	Map<int, string> mymap;

	mymap.insert(v[0]);
	mymap.insert(v[1]);
	mymap.insert(v[2]);
	mymap.insert(v[3]);

	mymap.set_end_node();

	Map<int,string>::iterator it = mymap.begin();
	while(it != mymap.end())
	{
		cout<<it->first<<" : "<<it->second<<endl;
		++it;
	}
}

/*
void main()
{
	vector<int> iv{10, 7, 8, 15, 5, 6, 11, 13, 12};
	Set<int> myset;
	for(const auto &e : iv)
		myset.insert(e);

	//cout<<"size = "<<myset.size()<<endl;
	myset.set_end_node();

	Set<int>::iterator it = myset.begin();
	while(it != myset.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

}


/*
void main()
{
	vector<int> iv{10, 7, 8, 15, 5, 6, 11, 13, 12};
	//vector<int> iv{10};
	//vector<int> iv{10, 7, 8, 15, 5, 6, 11, 13};
	RBTree<int> rb;
	for(const auto &e : iv)
		rb.Insert(e);

	rb.set_end_node();
	//rb.Remove(6);

	RBTree<int>::iterator it = rb.begin();
	while(it != rb.end())
	{
		cout<<*it<<" ";
		++it;

	}

	return;
}
*/