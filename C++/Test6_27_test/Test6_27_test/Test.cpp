#include<iostream>
#include<vector>
#include<list>
#include<forward_list>
#include<algorithm>
#include<functional>
#include<queue>
#include<array>
#include<forward_list>
#include<string>
#include <numeric>
using namespace std;

void main()
{
	//vector<int> v1{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	auto it = unique(v1.begin(), v1.end());
	
	for(const auto &e : v1)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	//vector<int> v1{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	vector<int> v1{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
	auto it = unique(v1.begin(), v1.end());
	
	for(const auto &e : v1)
		cout<<e<<" ";
	cout<<endl;

	//reverse(v1.begin(), v1.end());
	sort(v1.begin(), v1.end());

	for(const auto &e : v1)
		cout<<e<<" ";
	cout<<endl;
}

/*
bool IsOdd(int i)
{
	return i >= 5;
}

int main()
{
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	// 将区间中元素分割成奇数和偶数两部分
	auto div = partition(v.begin(), v.end(), IsOdd);

	// 打印[begin, div)的元素
	for (auto it = v.begin(); it != div; ++it)
		cout << *it << " ";
	cout << endl;
	// 打印[div, end)的元素
	for (auto it = div; it != v.end(); ++it)
		cout << " " << *it;
	cout << endl;
	return 0;
}

/*
int main()
{
	// 找该区间中前4个最小的元素, 元素最终存储在v1的前4个位置
	vector<int> v1{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	partial_sort(v1.begin(), v1.begin()+3, v1.end());

	for(const auto &e : v1)
		cout<<e<<" ";
	cout<<endl;

		// 找该区间中前4个最大的元素, 元素最终存储在v1的前4个位置
	vector<int> v2{ 4, 1, 8, 0, 5, 9, 3, 7, 2, 6 };
	partial_sort(v2.begin(), v2.begin() + 4, v2.end(), greater<int>());
	return 0;
}

/*
void main()
{
	vector<int> v{ 2, 6, 5, 8 };
	list<int>   L{ 9, 3, 0, 5, 7 };
	sort(v.begin(), v.end());
	L.sort();

	vector<int> vRet(v.size() + L.size());

	merge(v.begin(), v.end(), L.begin(), L.end(), vRet.begin());
	for (auto e : vRet)
		cout << e << " ";
	cout << endl;
}


/*
bool IsOdd(const int &i)
{
	return i >= 6;
}

void main()
{
	vector<int> v{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	auto it = find_if(v.begin(), v.end(), IsOdd);

	if(it != v.end())
		v.erase(it);

	for(const auto &e : v)
		cout<<e<<" ";
	cout<<endl;
}

/*
bool IsOdd(int i)
{
	//return ((i % 2) == 1);
	return i>=6;

}
int main()
{
	vector<int> v1{ 10, 20, 30, 30, 20, 10, 20,20,20,10, 20 };
	cout << count(v1.begin(), v1.end(), 20) << endl;
	
	
	// 统计v2中有多少个偶数
	vector<int> v2{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	cout << count_if(v2.begin(), v2.end(), IsOdd) << endl;

	return 0;
}

/*
struct Mul2
{
	int operator()(int x, int y) 
	{
		return x + 2 * y; 
	}
};
int main()
{
	vector<int> v{ 10, 20, 30 };
	//cout << accumulate(v.begin(), v.end(), 0) << endl;
	// 对区间中的每个元素乘2，然后累加
	cout << accumulate(v.begin(), v.end(), 0, Mul2()) << endl;
	return 0;
}

/*
void main()
{
	string str = "jflajflFAFAfFAFaflafla";
	cout<<"str = "<<str<<endl;
	transform(str.begin(), str.end(), str.begin(), toupper);
	cout<<"str = "<<str<<endl;
	
}

/*
void main()
{
	forward_list<int> slist;
	for(int i=1; i<=10; ++i)
		slist.push_front(i);

	auto it = slist.begin();
	while(it != slist.end())
	{
		cout<<*it<<"->";
		++it;
	}
	cout<<"Over."<<endl;
}

/*
void main()
{
	array<int, 10> ar = {1,2,3,4,5,6,7,8,9,10};
	cout<<ar.size()<<endl;
	cout<<ar.back()<<endl;
	cout<<ar.front()<<endl;

	for(int i=0; i<ar.size(); ++i)
		cout<<ar.at(i)<<" ";
	cout<<endl;


	for(int i=0; i<ar.size(); ++i)
		cout<<ar[i]<<" ";
	cout<<endl;

	array<int, 10>::iterator it = ar.begin();
	while(it != ar.end())
	{
		cout<<*it<<" ";
		++it;
	}
	cout<<endl;

	for(const auto &e : ar)
		cout<<e<<" ";
	cout<<endl;
}

/*
//sort O(logN)
//topK
void main()
{
	vector<int> iv = {4,8,9,2,1,3,5,7,6};
	priority_queue<int> pq;
	for(const auto &e : iv)
		pq.push(e);

	cout<<pq.top()<<endl;
}

/*
void main()
{
	vector<int> iv = {4,8,9,2,1,3,5,7,6};
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
	//make_heap(iv.begin(), iv.end(), greater<int>());
	make_heap(iv.begin(), iv.end());
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	iv.push_back(12);
	push_heap(iv.begin(), iv.end());
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	pop_heap(iv.begin(), iv.end());
	iv.pop_back();
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;

	sort_heap(iv.begin(), iv.end());
	for(const auto &e : iv)
		cout<<e<<" ";
	cout<<endl;
}

/*
void main()
{
	forward_list<int> mylist;
	for(int i=1; i<=10; ++i)
		mylist.push_front(i);

	forward_list<int>::iterator it= mylist.begin();
	while(it != mylist.end())
	{
		cout<<*it<<"-->";
		++it;
	}
	cout<<"Over."<<endl;

}

/*
template<class Type>
class ListItem
{
public:
	Type value()
	{
		return _value;
	}
	ListItem* next()
	{
		return _next;
	}
private:
	Type _value;
	ListItem *_next;
};

template<class Type>
class List
{
private:
	ListItem<Type> *_front;
	ListItem<Type> *_end;
	size_t          _size;
};

////////////////////////////////////////////////////
template<class Type>
class ListIterator
{
public:
	ListIterator(Type *p=0) : _ptr(p)
	{}
private:
	Type *_ptr;
};

/*
void main()
{
	vector<int> iv = {3,9,8,5,0,1,2,4,6};
	auto it = find(iv.begin(),iv.end(), 2);

	list<int> lt = {3,9,8,5,0,1,2,4,6};
	auto it1 = find(lt.begin(),lt.end(), 2);
}

/*
void Out_Of_Memory()
{
	cout<<"Out_Of_Memory."<<endl;
	//exit(1);
}


void main()
{
	//int *ptr = (int*)malloc(sizeof(int) * 536870911);
	try
	{
		set_new_handler(Out_Of_Memory);
		int *ptr = new int[536870911];
	}
	catch(bad_alloc & e)
	{
		cout<<e.what()<<endl;
	}
	
	cout<<"OK"<<endl;
}
*/