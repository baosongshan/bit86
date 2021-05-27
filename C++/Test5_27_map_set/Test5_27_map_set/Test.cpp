#include<iostream>
#include<string>
#include<map>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<hash_map>
#include<hash_set>
#include<functional>
using namespace std;

//现在有一个用来存放整数的Hash表，
//Hash表的存储单位称为桶，
//每个桶能放3个整数，当一个桶中要放的元素超过3个时，
//则要将新的元素存放在溢出桶中，每个溢出桶也能放3个元素，
//多个溢出桶使用链表串起来。
//此Hash表的基桶数目为素数P，Hash表的hash函数对P取模。代码定义如下：

//现在假设hash_table已经初始化好了，
//insert_new_element()函数目的是把一个新的值插入hash_table中，
//元素插入成功时，函数返回0，否则返回-1，完成函数。
#define P 7
#define NULL_DATA -1
struct bucket_node	
{
	int data[3];
	struct bucket_node *next;
};
bucket_node hash_table[P];

int insert_new_element(int new_element)
{
	//完成此函数
}

int main()
{
	Init_bucket_node();
	int array[] = { 15, 14, 21, 87, 96, 293, 35, 24, 149, 19, 63, 16, 103, 77, 5, 153, 145, 356, 51, 68, 705, 453 };
	for (int i = 0; i < sizeof(array) / sizeof(int); i++)
	{
		insert_new_element(array[i]);
	}
	return 0;
}




/*
template<class Type>
class HashTable;

template<class Type>
class HashNode
{
	friend class HashTable<Type>;
public:
	HashNode(Type d):data(d), link(nullptr)
	{}
private:
	Type data;
	HashNode *link;
};

template<class Type>
class HashTable
{
public:
	HashTable()
	{
		memset(hashtable, 0, sizeof(HashNode<Type>*)*HASH_DEFAULT_SIZE);
	}
public:
	void Insert(const Type &x)
	{
		int index = Hash(x);
		HashNode<Type> *s = new HashNode<Type>(x);
		s->link = hashtable[index];
		hashtable[index] = s;
	}
	void Remove(const Type &key)
	{
		int index = Hash(key);
		HashNode<Type> *prev = nullptr;
		HashNode<Type> *p = hashtable[index];
		while(p!=nullptr && p->data!=key)
		{
			prev = p;
			p = p->link;
		}

		if(p == nullptr)
			return;

		if(prev == nullptr)
			hashtable[index] = p->link;
		else
			prev->link = p->link;
		delete p;
	}
public:
	void Show()const
	{
		for(int i=0; i<HASH_DEFAULT_SIZE; ++i)
		{
			cout<<i<<" : ";
			HashNode<Type> *p = hashtable[i];
			while(p != nullptr)
			{
				cout<<p->data<<"-->";
				p = p->link;
			}
			cout<<"Nul."<<endl;
		}
	}
protected:
	int Hash(const Type &key)
	{
		return key % HASH_DEFAULT_SIZE;
	}
private:
	enum {HASH_DEFAULT_SIZE = 7};
	HashNode<Type>* hashtable[HASH_DEFAULT_SIZE];
};

void main()
{
	vector<int> iv{37,2,5, 9,1,13,8,3,6,12};
	HashTable<int> ht;

	for(const auto &e : iv)
		ht.Insert(e);

	ht.Show();

	ht.Remove(9);
	ht.Show();
}

/*
void main()
{
	//hash
	hash_set<int> s{5,8,9,2,5,5,3,9,8,1,0,4,7};
	unordered_set<int> s1{5,8,9,2,5,5,3,9,8,1,0,4,7};

	for(const auto &e : s)
		cout<<e<<" ";
	cout<<endl;

	for(const auto &e : s1)
		cout<<e<<" ";
	cout<<endl;


}

/*
void main()
{
	//hash
	//hash_map<int,string> mp{{3,"abc"},{2,"xyz"},{5,"opq"},{3,"abc"},{3,"abc"},{4,"lmn"},	{20,"hjk"}};
	hash_multimap<int,string> mp{{3,"abc"},{2,"xyz"},{5,"opq"},{3,"abc"},{3,"abc"},{4,"lmn"},	{20,"hjk"}};
	
	auto it = mp.find(50);

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}


/*
void main()
{
	//hash
	unordered_multiset<int> s{5,8,9,2,5,5,3,9,8,1,0,4,7};

	for(const auto &e : s)
		cout<<e<<" ";
	cout<<endl;


}

/*
void main()
{
	//hash
	unordered_multimap<int,string> mp{{3,"abc"},{2,"xyz"},{5,"opq"},{3,"abc"},{3,"abc"},{4,"lmn"},	{20,"hjk"}};
	
	auto it = mp.find(50);

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	//hash
	unordered_map<int,string> mp{{3,"abc"},{2,"xyz"},{5,"opq"},{3,"abc"},{3,"abc"},{4,"lmn"},	{20,"hjk"}};
	
	auto it = mp.find(50);

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	multimap<int,string> mmp{
		{3,"abc"},{2,"xyz"},
		{5,"opq"},{4,"lmn"},
		{20,"hjk"},{2,"qwe"},
		{5,"tyu"}};

	//size_t count = mmp.erase(2);
	mmp.erase(mmp.begin());

	for(const auto &e : mmp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
struct Test
{
	Test(int a, int b) : m_a(a), m_b(b)
	{}
	int m_a;
	int m_b;
};

void main()
{
	Test t1(1,1);
	Test t2(2,2);
	Test t3(3,3);
	set<Test> s;
	s.insert(t1);
	s.insert(t2);
	s.insert(t3);
}
/*
void main()
{
	pair<int, string> v1{1,"abc"};
	pair<int, string> v2{2,"xyz"};
	set<pair<int,string>> s;
	s.insert(v1);
	s.insert(v2);

	for(const auto &e : s)
		cout<<e.first<<" : "<<e.second<<endl;

	set<pair<int,string>>::iterator it = s.begin();
	while(it != s.end())
	{
		cout<<it->first<<" : "<<it->second<<endl;
		++it;
	}
}

/*
void main()
{
	set<int, greater<int>> s{5,8,9,2,3,1,0,4,7};
	
	set<int>::iterator it = s.begin();
	while(it != s.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	set<int> s{5,8,9,2,3,1,0,4,7};
	
	s.insert(6);
	s.insert(6);

	set<int>::iterator it = s.begin();
	while(it != s.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;
}

/*
void main()
{
	multimap<int,string> mp{
		{3,"abc"},{2,"xyz"},
		{5,"opq"},{4,"lmn"},
		{20,"hjk"},{2,"qwe"},
		{5,"tyu"}};
	
	cout<<mp.count(5)<<endl;

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	map<int,string> mp{
		{3,"abc"},{2,"xyz"},
		{5,"opq"},{4,"lmn"},
		{20,"hjk"},{2,"qwe"},
		{5,"tyu"}};
	
	cout<<mp.count(3)<<endl;

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	map<int,string> mp{{3,"abc"},{2,"xyz"},{5,"opq"},{4,"lmn"},	{20,"hjk"}};
	
	auto it = mp.find(50);

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	map<int,string> mp{{3,"abc"},{2,"xyz"},{5,"opq"},{4,"lmn"},	{20,"hjk"}};

	mp.insert(make_pair<int,string>(8,"bit"));

	auto pos = mp.begin();
	cout<<pos->first<<" : "<<pos->second<<endl;
	pos = mp.erase(pos);
	//auto it = mp.erase(mp.begin(), mp.end());
	//size_t it = mp.erase(5);
	//cout<<it->first<<" : "<<it->second<<endl;
	cout<<pos->first<<" : "<<pos->second<<endl;

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	map<int, int> mp{{3,300},{1,100},{5,500},{4,400}};
}

/*
void main()
{
	pair<int,int> va[] = {{3,300},{1,100},{5,500},{4,400}};
	int n = sizeof(va) / sizeof(va[0]);

	map<int, int> mp;
	for(int i=0; i<n; ++i)
		mp.insert(va[i]);

	mp[1] = 1000;
	mp[2] = 200;  //插入数据

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	pair<int,int> va[] = {{3,300},{1,100},{5,500},{4,400}};
	int n = sizeof(va) / sizeof(va[0]);

	  //key  value
	map<int, int> mp;
	for(int i=0; i<n; ++i)
		mp.insert(va[i]);

	for(int i=0; i<mp.size(); ++i)
		cout<<mp[i]<<endl;
}

/*
void main()
{
	pair<int,int> va[] = {{3,300},{1,100},{5,500},{4,400}};
	int n = sizeof(va) / sizeof(va[0]);

	  //key  value
	map<int, int> mp;
	for(int i=0; i<n; ++i)
		mp.insert(va[i]);

	for(const auto &e : mp)
		cout<<e.first<<" : "<<e.second<<endl;
}

/*
void main()
{
	pair<int,int> va[] = {{3,300},{1,100},{5,500},{4,400}};
	int n = sizeof(va) / sizeof(va[0]);

	  //key  value
	map<int, int> mp;
	for(int i=0; i<n; ++i)
		mp.insert(va[i]);

	map<int,int>::iterator it = mp.begin();
	while(it != mp.end())
	{
		cout<<it->first<<" : "<<it->second<<endl;
		++it;
	}
}

/*
void main()
{
	pair<int,int> v1(1,100);
	pair<int,int> v2(2,200);
	pair<int,int> v3(3,100);
	map<int, int> mp;

	mp.insert(v1);
	mp.insert(v2);
	mp.insert(v3);
}

/*
void main()
{
	pair<int, string> v = make_pair(1,"abc");
	cout<<v.first<<" : "<<v.second<<endl;
}

/*
template<class _Ty1, class _Ty2>
struct KeyValue
{
	_Ty1 first;
	_Ty2 second;
};

template<class _T1, class _T2> 
struct pair 
{
	typedef _T1 first_type;
	typedef _T2 second_type;
	pair(): first(_T1()), second(_T2()) 
	{}
	pair(const _T1& _V1, const _T2& _V2)
		: first(_V1), second(_V2) 
	{}
	template<class U, class V> 
	pair(const pair<U, V> &p)
		: first(p.first), second(p.second) 
	{}
	_T1 first;
	_T2 second;
};

void main()
{
	//值对
	pair<int, int> p1;  //first second
	cout<<p1.first<<" : "<<p1.second<<endl;
	
	pair<int, int> p2(1, 100);
	cout<<p2.first<<" : "<<p2.second<<endl;
}
*/