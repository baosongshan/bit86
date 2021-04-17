#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<string>
using namespace std;


void MulItem(string num, int s, string &tmp)
{
	int res, sign = 0;

	for (int i = 0; i < num.size(); ++i)
	{
		res = s * (num[i] - '0') + sign;
		if (res >= 10)
		{
			sign = res / 10;
			res = res % 10;
		}
		else
			sign = 0;
		tmp += (res + '0');
	}
	if(sign > 0)
		tmp += (sign+'0');
}

int AddItem(int a, int b, int &sign)
{
	int sum = a + b + sign;
	if (sum >= 10)
	{
		sum -= 10;
		sign = 1;
	}
	else
		sign = 0;
	return sum;
}
void AddMove(string &num, string tmp, int k)
{
	int i = k;
	int j = 0;
	int sign = 0;
	while (i < num.size() && j < tmp.size())
	{
		num[i] = AddItem(num[i] - '0', tmp[j] - '0', sign) + '0';
		i++;
		j++;
	}
	while (i < num.size())
	{
		num[i] = AddItem(num[i] - '0', 0, sign) + '0';
		i++;
	}
	while (j<tmp.size())
	{
		int sum = AddItem(0, tmp[j] - '0', sign);
		num += (sum + '0');
		j++;
	}
	if (sign > 0)
		num += (sign + '0');
}
string multiply(string num1, string num2)
{
	reverse(num1.begin(), num1.end());
	reverse(num2.begin(), num2.end());

	string result, tmp;
	for (int i = 0; i < num2.size(); ++i)
	{
		MulItem(num1, num2[i] - '0', tmp);
		AddMove(result, tmp, i);
		tmp.clear();
	}
	while(result.size()>1 && result.back() == '0')
		result.pop_back();
	reverse(result.begin(), result.end());
	return result;
}

void  main()
{
	string num1 = "974124";
	string num2 = "0";

	string res = multiply(num1, num2);
	cout<<res<<endl;
}

/*
//find()
//reverse()
void main()
{
	string str = "123456789";
	cout<<str<<endl;
	reverse(str.begin(), str.end());
	cout<<str<<endl;
}

/*
namespace bit
{
   //bit::priority_queue<int> 
	template<class T, class Container = vector<T>, 
			 class Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{}
		priority_queue(const T *first, const T *last,
						const Compare& pr = Compare()):c(first, last),comp(pr)
		{
			//最后一个分支的位置
			int curpos = c.size()/2 - 1;
			while(curpos >= 0)
			{
				_adjustdown(curpos);
				curpos--;
			}
		}

		bool empty() const
		{
			return c.empty();
		}
		size_t size() const
		{
			return c.size();
		}
       
		T& top()
		{
			return c.front();
		}
		void push(const T& x)
		{
			c.push_back(x);
			_adjustup(c.size()-1);
		}
		void pop()
		{
			std::swap(*c.begin(), *--c.end());
			c.pop_back();
			_adjustdown(0);
		}
		void Show()const
		{
			for(int i=0; i<c.size(); ++i)
				cout<<c[i]<<" ";
			cout<<endl;
		}
	protected:
		void _adjustdown(int start)
		{
			int n = c.size();
			int i = start;
			int j = 2 * i + 1;
			while(j < n)
			{
				//less c[j]<c[j+1]
				if(j+1<n && comp(c[j],c[j+1]))
					j++;

				//truee
				if(comp(c[i], c[j]))
				{
					T tmp = c[i];
					c[i] = c[j];
					c[j] = tmp;

					i = j;
					j = 2*i+1;
				}
				else
					break;
			}
		}
		void _adjustup(int start)
		{
			int j = start;
			int i = (j-1) / 2;

			while(j > 0)
			{
				if(comp(c[i], c[j]))
				{
					T tmp = c[i];
					c[i] = c[j];
					c[j] = tmp;

					j = i;
					i = (j-1) / 2;
				}
				else
					break;
			}
		}
	private:
		Container c;
		Compare comp;
	};
};

void main()
{
	int ar[] = {53,17,78,9,45,65,87,23};
	int n = sizeof(ar)/sizeof(ar[0]);

	bit::priority_queue<int,vector<int>, greater<int>> 
		pq(ar, ar+n, greater<int>());

	//bit::priority_queue<int> pq(ar, ar+n);
	//bit::priority_queue<int> pq;
	//pq.push(50);

	//pq.pop();
	pq.Show();

}


/*
namespace bit
{
	template<class T, class Cont = vector<T>, class Pred = less<T> >
	class priority_queue
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
	public:
		explicit priority_queue(const Pred& pr = Pred()) : sz(0)
		{}
		
		priority_queue(const value_type *first, const value_type *last,
						const Pred& pr = Pred()):c(first, last)
		{
			//less 大    ：   greater 小
			make_heap(c.begin(), c.end(), pr);
			sz = c.size();
		}
		
		bool empty() const
		{
			return sz == 0;
		}
		size_type size() const
		{
			return sz;
		}
		value_type& top()
		{
			return c.front();
		}
		const value_type& top() const
		{
			return c.front();
		}
		
		void pop()
		{
			pop_heap(c.begin(), c.end());
			sz--;
		}
		
		void push(const value_type& x)
		{
			c.push_back(x);
			push_heap(c.begin(), c.end());
			sz++;
		}

		void Show()const
		{
			for(int i=0; i<c.size(); ++i)
				cout<<c[i]<<" ";
			cout<<endl;
		}
	protected:
		Cont c;
		Pred comp;
		size_t sz;
	};
};

void main()
{
	int ar[] = {5,9,2,4,1};
	int n = sizeof(ar)/sizeof(ar[0]);

	//bit::priority_queue<int,vector<int>, greater<int>> 
	//	pq(ar, ar+n, greater<int>());

	bit::priority_queue<int> pq(ar, ar+n);

	pq.Show();
}

/*
void main()
{
	bit::priority_queue<int> pq;
	//5 9 2 4 1
	pq.push(5);
	pq.push(9);
	pq.push(2);
	pq.push(4);
	pq.push(1);

	cout<<"size = "<<pq.size()<<endl;;
	//pq.Show();
	pq.pop();
	//cout<<pq.top()<<endl;
	cout<<"size = "<<pq.size()<<endl;;
}

*/