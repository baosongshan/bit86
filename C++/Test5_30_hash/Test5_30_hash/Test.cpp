#include<iostream>
#include<vector>
using namespace std;

template <class Value>
struct __hashtable_node
{
	Value val;
	__hashtable_node* next;
};  

struct MyHash
{
	int operator()(int key)
	{
		return key;
	}
};

struct MyExtractKey
{
	int operator()(int key)
	{
		return key;
	}
};


static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
  53,         97,           193,         389,       769,
  1543,       3079,         6151,        12289,     24593,
  49157,      98317,        196613,      393241,    786433,
  1572869,    3145739,      6291469,     12582917,  25165843,
  50331653,   100663319,    201326611,   402653189, 805306457, 
  1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long __stl_next_prime(unsigned long n)
{
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	
	while(first != last)
	{
		if(*first >= n)
			break;
		++first;
	}
	return first == last ? *(last - 1) : *first;
}

////////////////////////////////////////////////////////////////////////
//iterator

template <class Key, class Value, class HashFcn=MyHash,class ExtractKey=MyExtractKey>
class hashtable;

template <class Key, class Value, class HashFcn, class ExtractKey>
struct __hashtable_iterator 
{
public:
	typedef __hashtable_iterator<Key, Value, HashFcn,ExtractKey> self;
	typedef __hashtable_node<Value> node;
	typedef hashtable<Key, Value, HashFcn,ExtractKey> hashtable;
public:
	__hashtable_iterator(node* n, hashtable* tab)
		: cur(n), ht(tab) 
	{}
public:
	Value& operator*()
	{
		return cur->val;
	}
	Value* operator->()
	{
		return &(cur->val);
	}

	self& operator++()
	{
		const node* old = cur;
		cur = cur->next;
		if (!cur) 
		{
			size_t bucket = ht->bkt_num(old->val);
			while (!cur && ++bucket < ht->buckets.size())
				cur = ht->buckets[bucket];
		}
		return *this;
	}

	bool operator!=(self &s)
	{
		return cur != s.cur;
	}
	bool operator==(self &s)
	{
		return cur == s.cur;
	}
private:
	node *cur;
	hashtable *ht;
};


///////////////////////////////////////////////////////////////////////

template <class Key, class Value, class HashFcn=MyHash,class ExtractKey=MyExtractKey>
class hashtable 
{
	friend __hashtable_iterator <Key,  Value, HashFcn, ExtractKey>; 
public:
	typedef __hashtable_iterator<Key, Value, HashFcn, ExtractKey> iterator;
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef HashFcn hasher;
	typedef size_t size_type;
public:
	typedef __hashtable_node<Value> node;
public:
	hashtable(size_t n = 53)  
		:  hash(HashFcn()), 
		get_key(ExtractKey()),
		num_elements(0)
	{
		initialize_buckets(n);
	}
public:
	size_type bucket(const Key &k)const
	{
		return k % buckets.size();
	}
	size_type bucket_count() const 
	{
		return buckets.size();
	}
	size_type bucket_size(size_type bucket) const
	{
		size_type result = 0;
		for (node* cur = buckets[bucket]; cur; cur = cur->next)
			result += 1;
		return result;
	}

	size_type size() const 
	{
		return num_elements; 
	}
public:
	iterator begin()
	{
		for (size_type n = 0; n < buckets.size(); ++n)
		{
			if (buckets[n])
				return iterator(buckets[n], this);
		}
		return end();
	}
	iterator end()
	{
		return iterator(NULL, this);
	}
public:
	bool insert_equal(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_equal_noresize(obj);
	}
	bool insert_equal_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
		{
			if(cur->val == obj)
			{
				node* tmp = new_node(obj);
				tmp->next = cur->next;
				cur->next = tmp;
				++num_elements;
				return true;
			}
		}
		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return true;
	}

	bool insert_unique(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_unique_noresize(obj);
	}
	bool insert_unique_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
			if (obj == cur->val)
				return false;

		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return true;
	}
public:
	size_type bkt_num_key(const key_type& key)
	{
		return bkt_num_key(key, buckets.size());
	}

	size_type bkt_num(const value_type& obj)
	{
		return bkt_num_key(get_key(obj));
	}

	size_type bkt_num_key(const key_type& key, size_t n)
	{
		return hash(key) % n; //
	}

	size_type bkt_num(const value_type& obj, size_t n)
	{
		return bkt_num_key(get_key(obj), n);
	}
	node* new_node(const value_type& obj)
	{
		node* n = (node*)malloc(sizeof(node));
		n->next = 0;
		n->val = obj;
		return n;
	}
public:
	void resize(size_type num_elements_hint)
	{
		const size_type old_n = buckets.size();
		if (num_elements_hint > old_n)
		{
			const size_type n = next_size(num_elements_hint);
			if (n > old_n)
			{
				vector<node*> tmp(n, (node*)0);

				for (size_type bucket = 0; bucket < old_n; ++bucket) 
				{
					node* first = buckets[bucket];
					while (first) 
					{
						size_type new_bucket = bkt_num(first->val, n);
						buckets[bucket] = first->next;
						first->next = tmp[new_bucket];
						tmp[new_bucket] = first;
						first = buckets[bucket];
					}
				}
				buckets.swap(tmp);
			}
		}
	}
	void print_hash_table()
	{
		for(int i=0; i<buckets.size(); ++i)
		{
			cout<<i<<" : ";
			node *first = buckets[i];
			while(first != NULL)
			{
				cout<<first->val<<"-->";
				first = first->next;
			}
			cout<<"Nil."<<endl;
		}
	}
private:
	size_type next_size(size_type n) const 
	{
		return __stl_next_prime(n); 
	}
	void initialize_buckets(size_type n)
	{
		const size_type n_buckets = next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*)0);
		num_elements = 0;
	}
private:
	hasher hash;
	ExtractKey get_key;
	vector<node*> buckets; //桶节点
	size_t        num_elements;
};

////////////////////////////////////////////////////////////////
//unordered_map

template<class Key, class Value,class HashFcn=MyHash, class ExtractKey=MyExtractKey>
class Unordered_map
{
public:
	struct MapExtractKey
	{
		Key operator()(pair<Key, Value> k)
		{
			return k.first;
		}
	};
public:
	typedef pair<Key,Value> value_type;
public:
	typedef hashtable<Key, value_type, HashFcn,MapExtractKey> hashtable;
	typedef __hashtable_iterator<Key, value_type, HashFcn, MapExtractKey> iterator;

public:
	Unordered_map()
	{}
	size_t size() const
	{
		return _ht.size();
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	bool insert ( const value_type& val)
	{
		return _ht.insert_unique(val);
	}
private:
	hashtable _ht;
};

//unordered_multimap
template<class Key, class Value,class HashFcn=MyHash, class ExtractKey=MyExtractKey>
class Unordered_multimap
{
	struct MapExtractKey
	{
		Key operator()(pair<Key, Value> k)
		{
			return k.first;
		}
	};
public:
	typedef pair<Key,Value> value_type;
public:
	typedef hashtable<Key, value_type, HashFcn,MapExtractKey> hashtable;
	typedef __hashtable_iterator<Key, value_type, HashFcn, MapExtractKey> iterator;

public:
	Unordered_multimap()
	{}
	size_t size() const
	{
		return _ht.size();
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	bool insert ( const value_type& val)
	{
		return _ht.insert_equal(val);
	}
private:
	hashtable _ht;
};

//unordered_set
template<class Key, class Value=Key,class HashFcn=MyHash, class ExtractKey=MyExtractKey>
class Unordered_set
{
public:
	struct SetExtractKey
	{
		 Key operator()(Key k)
		{
			return k;
		}
	};
public:
	typedef Value value_type;
public:
	typedef hashtable<Key, value_type, HashFcn,SetExtractKey> hashtable;
	typedef __hashtable_iterator<Key, value_type, HashFcn, SetExtractKey> iterator;

public:
	Unordered_set()
	{}
	size_t size() const
	{
		return _ht.size();
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	bool insert ( const value_type& val)
	{
		return _ht.insert_unique(val);
	}
private:
	hashtable _ht;
};


template<class Key, class Value=Key,class HashFcn=MyHash, class ExtractKey=MyExtractKey>
class Unordered_multiset
{
public:
	struct SetExtractKey
	{
		 Key operator()(Key k)
		{
			return k;
		}
	};
public:
	typedef Value value_type;
public:
	typedef hashtable<Key, value_type, HashFcn,SetExtractKey> hashtable;
	typedef __hashtable_iterator<Key, value_type, HashFcn, SetExtractKey> iterator;

public:
	Unordered_multiset()
	{}
	size_t size() const
	{
		return _ht.size();
	}
	iterator begin()
	{
		return _ht.begin();
	}
	iterator end()
	{
		return _ht.end();
	}
	bool insert ( const value_type& val)
	{
		return _ht.insert_equal(val);
	}
private:
	hashtable _ht;
};

void main()
{
	Unordered_set<int> Uset;
	Uset.insert(1);
	Uset.insert(10);
	Uset.insert(100);

	for(const auto &e : Uset)
		cout<<e<<" ";
	cout<<endl;

}

/*
void main()
{
	pair<int, int> v[] = {{1,10},{2,20},{3,30},{2,200}};
	Unordered_map<int,int> Umap;
	Umap.insert(v[0]);
	Umap.insert(v[1]);
	Umap.insert(v[2]);
	Umap.insert(v[3]);

	auto it = Umap.begin();
	while(it != Umap.end())
	{
		cout<<it->first<<" : "<<it->second<<endl;
		++it;
	}
}


/*
void main()
{
	hashtable<int, int> ht(53);
	//ht.insert_unique(1);
	ht.insert_unique(53);
	ht.insert_unique(108);
	ht.insert_unique(2);
	ht.insert_unique(55);
	ht.insert_unique(59);
	ht.insert_unique(63);

	hashtable<int, int>::iterator it = ht.begin();
	while(it != ht.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	cout<<"bucket count = "<<ht.bucket_count()<<endl;
	cout<<"bucket size = "<<ht.bucket_size(2)<<endl;
	cout<<"bucket index = "<<ht.bucket(55)<<endl;
}

/*
template <class Value>
struct __hashtable_node
{
	Value val;
	__hashtable_node* next;
};  

static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
  53,         97,           193,         389,       769,
  1543,       3079,         6151,        12289,     24593,
  49157,      98317,        196613,      393241,    786433,
  1572869,    3145739,      6291469,     12582917,  25165843,
  50331653,   100663319,    201326611,   402653189, 805306457, 
  1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long __stl_next_prime(unsigned long n)
{
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	
	while(first != last)
	{
		if(*first >= n)
			break;
		++first;
	}
	return first == last ? *(last - 1) : *first;
}

template <class Key>
class hashtable 
{
public:
	typedef Key   Value;
	typedef Key   value_type;
	typedef size_t size_type;
public:
	typedef __hashtable_node<Value> node;
public:
	hashtable(size_t n)  : num_elements(0)
	{
		initialize_buckets(n);
	}
public:
	bool insert_unique(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_unique_noresize(obj);
	}
	bool insert_unique_noresize(const value_type& obj)
	{
		const size_type n = Hash(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
			if (obj == cur->val)
				return false;

		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return true;
	}
public:
	int Hash(Key key)
	{
		return key % buckets.capacity();
	}
	int Hash(Key key, int n)
	{
		return key % n;
	}
	node* new_node(const value_type& obj)
	{
		node* n = (node*)malloc(sizeof(node));
		n->next = 0;
		n->val = obj;
		return n;
	}
public:
	void resize(size_type num_elements_hint)
	{
		const size_type old_n = buckets.size();
		if (num_elements_hint > old_n)
		{
			const size_type n = next_size(num_elements_hint);
			if (n > old_n)
			{
				vector<node*> tmp(n, (node*)0);

				for (size_type bucket = 0; bucket < old_n; ++bucket) 
				{
					node* first = buckets[bucket];
					while (first) 
					{
						size_type new_bucket = Hash(first->val,n);
						buckets[bucket] = first->next;
						first->next = tmp[new_bucket];
						tmp[new_bucket] = first;
						first = buckets[bucket];
					}
				}
				buckets.swap(tmp);
			}
		}
	}
	void print_hash_table()
	{
		for(int i=0; i<buckets.size(); ++i)
		{
			cout<<i<<" : ";
			node *first = buckets[i];
			while(first != NULL)
			{
				cout<<first->val<<"-->";
				first = first->next;
			}
			cout<<"Nil."<<endl;
		}
	}
private:
	size_type next_size(size_type n) const 
	{
		return __stl_next_prime(n); 
	}
	void initialize_buckets(size_type n)
	{
		const size_type n_buckets = next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*)0);
		num_elements = 0;
	}
private:
	vector<node*> buckets; //桶节点
	size_t        num_elements;
};

void main()
{
	hashtable<int> ht(53);
	for(int i=0; i<53; ++i)
		ht.insert_unique(i+2);

	ht.print_hash_table();
	cout<<"============"<<endl;
	ht.insert_unique(100);
	ht.print_hash_table();
}


/*
template <class Value>
struct __hashtable_node
{
	Value val;
	__hashtable_node* next;
};  

struct MyHash
{
	int operator()(int key)
	{
		return key;
	}
};

struct MyExtractKey
{
	int operator()(int key)
	{
		return key;
	}
};


static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] =
{
  53,         97,           193,         389,       769,
  1543,       3079,         6151,        12289,     24593,
  49157,      98317,        196613,      393241,    786433,
  1572869,    3145739,      6291469,     12582917,  25165843,
  50331653,   100663319,    201326611,   402653189, 805306457, 
  1610612741, 3221225473ul, 4294967291ul
};

inline unsigned long __stl_next_prime(unsigned long n)
{
	const unsigned long* first = __stl_prime_list;
	const unsigned long* last = __stl_prime_list + __stl_num_primes;
	
	while(first != last)
	{
		if(*first >= n)
			break;
		++first;
	}
	return first == last ? *(last - 1) : *first;
}

template <class Key, class Value, class HashFcn=MyHash,class ExtractKey=MyExtractKey>
class hashtable 
{
public:
	typedef Key key_type;
	typedef Value value_type;
	typedef HashFcn hasher;
	typedef size_t size_type;
public:
	typedef __hashtable_node<Value> node;
public:
	hashtable(size_t n)  
		:  hash(HashFcn()), 
		get_key(ExtractKey()),
		num_elements(0)
	{
		initialize_buckets(n);
	}
public:
	bool insert_unique(const value_type& obj)
	{
		resize(num_elements + 1);
		return insert_unique_noresize(obj);
	}
	bool insert_unique_noresize(const value_type& obj)
	{
		const size_type n = bkt_num(obj);
		node* first = buckets[n];

		for (node* cur = first; cur; cur = cur->next)
			if (obj == cur->val)
				return false;

		node* tmp = new_node(obj);
		tmp->next = first;
		buckets[n] = tmp;
		++num_elements;
		return true;
	}
public:
	size_type bkt_num_key(const key_type& key)
	{
		return bkt_num_key(key, buckets.size());
	}

	size_type bkt_num(const value_type& obj)
	{
		return bkt_num_key(get_key(obj));
	}

	size_type bkt_num_key(const key_type& key, size_t n)
	{
		return hash(key) % n; //
	}

	size_type bkt_num(const value_type& obj, size_t n)
	{
		return bkt_num_key(get_key(obj), n);
	}
	node* new_node(const value_type& obj)
	{
		node* n = (node*)malloc(sizeof(node));
		n->next = 0;
		n->val = obj;
		return n;
	}
public:
	void resize(size_type num_elements_hint)
	{
		const size_type old_n = buckets.size();
		if (num_elements_hint > old_n)
		{
			const size_type n = next_size(num_elements_hint);
			if (n > old_n)
			{
				vector<node*> tmp(n, (node*)0);

				for (size_type bucket = 0; bucket < old_n; ++bucket) 
				{
					node* first = buckets[bucket];
					while (first) 
					{
						size_type new_bucket = bkt_num(first->val, n);
						buckets[bucket] = first->next;
						first->next = tmp[new_bucket];
						tmp[new_bucket] = first;
						first = buckets[bucket];
					}
				}
				buckets.swap(tmp);
			}
		}
	}
	void print_hash_table()
	{
		for(int i=0; i<buckets.size(); ++i)
		{
			cout<<i<<" : ";
			node *first = buckets[i];
			while(first != NULL)
			{
				cout<<first->val<<"-->";
				first = first->next;
			}
			cout<<"Nil."<<endl;
		}
	}
private:
	size_type next_size(size_type n) const 
	{
		return __stl_next_prime(n); 
	}
	void initialize_buckets(size_type n)
	{
		const size_type n_buckets = next_size(n);
		buckets.reserve(n_buckets);
		buckets.insert(buckets.end(), n_buckets, (node*)0);
		num_elements = 0;
	}
private:
	hasher hash;
	ExtractKey get_key;
	vector<node*> buckets; //桶节点
	size_t        num_elements;
};

void main()
{
	hashtable<int, int> ht(53);
}

/*
void main()
{
	hashtable<int, int> ht(53);
	for(int i=0; i<53; ++i)
		ht.insert_unique(i+2);

	ht.print_hash_table();
	cout<<"============"<<endl;
	ht.insert_unique(100);
	ht.print_hash_table();

}

/*
//标记状态
enum State{EMPTY, EXIST, DELETE};

template<class K, class V>
class HashTable
{
	struct Elem
	{
		pair<K, V> _val;
		State _state;
	};
public:
	HashTable(size_t capacity = 3): _ht(capacity), _size(0)
	{
		for (size_t i = 0; i < capacity; ++i)
			_ht[i]._state = EMPTY;
	}

	
	bool Insert(const pair<K, V>& val)
	{
		// 检测哈希表底层空间是否充足
		// _CheckCapacity();
		size_t hashAddr = HashFunc(val.first);
		// size_t startAddr = hashAddr;
		while (_ht[hashAddr]._state != EMPTY)
		{
			if (_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val.first == val.first)
				return false;
			hashAddr++;
			if (hashAddr == _ht.capacity())
				hashAddr = 0;
			
		}
		// 插入元素
		_ht[hashAddr]._state = EXIST;
		_ht[hashAddr]._val = val;
		_size++;
		return true;
	}
	int Find(const K& key)
	{
		size_t hashAddr = HashFunc(key);
		while (_ht[hashAddr]._state != EMPTY)
		{
			if (_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val.first == key)
				return hashAddr;
			hashAddr++;
		}
		return hashAddr;
	}
	bool Erase(const K& key)
	{
		int index = Find(key);
		if (-1 != index)
		{
			_ht[index]._state = DELETE;
			_size++;
			return true;
		}
		return false;
	}
	size_t Size()const;
	bool Empty() const;
	//void Swap(HashTable<K, V, HF>& ht);
private:
	size_t HashFunc(const K& key)
	{
		return key % _ht.capacity();
	}
private:
	vector<Elem> _ht;  //数组空间
	size_t _size;
};

void main()
{
	pair<int, string> v[] = {{1,"abc"}, {2,"xyz"},{3,"opq"},{5,"qwe"}};

	HashTable<int, string> ht;
	ht.Insert(v[0]);
	ht.Insert(v[1]);
	ht.Insert(v[2]);
	ht.Insert(v[3]);

}

/*
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
#define BUCKET_SIZE 3
#define NULL_DATA -1

struct bucket_node	
{
	int data[BUCKET_SIZE];
	struct bucket_node *next;
};
bucket_node hash_table[P];

int Hash(int key)
{
	return key % P;
}

void init_hash_table()
{
	for(int i=0; i<P; ++i)
	{
		for(int j=0; j<BUCKET_SIZE; ++j)
		{
			hash_table[i].data[j] = NULL_DATA;
		}
		hash_table[i].next = NULL;
	}
}

int insert_new_element(int new_element)
{
	//完成此函数
	int index = Hash(new_element);
	for(int i=0; i<BUCKET_SIZE; ++i)
	{
		if(hash_table[index].data[i] == NULL_DATA)
		{
			hash_table[index].data[i] = new_element;
			return true;
		}
	}

	bucket_node *p = &hash_table[index];
	while(p->next != NULL)
	{
		p = p->next;
		for(int i=0; i<BUCKET_SIZE; ++i)
		{
			if(p->data[i] == NULL_DATA)
			{
				p->data[i] = new_element;
				return true;
			}
		}
	}
	bucket_node *new_bucket = (bucket_node*)malloc(sizeof(bucket_node));
	for(int i=0; i<BUCKET_SIZE; ++i)
		new_bucket->data[i] = NULL_DATA;
	new_bucket->next = NULL;
	new_bucket->data[0] = new_element;

	p->next = new_bucket;
	return 0;
}

int main()
{
	init_hash_table();
	//int array[] = { 15, 14, 21, 87, 96, 293, 35, 24, 149, 19, 63, 16, 103, 77, 5, 153, 145, 356, 51, 68, 705, 453 };
	int array[] = {1,8,15,22,29,36, 43};
	int n = sizeof(array) / sizeof(array[0]);
	
	for (int i = 0; i < n; i++)
	{
		insert_new_element(array[i]);
	}
	return 0;
}
*/