#include<iostream>
//#include"Test.h"
using namespace std;

//平等 --> 
//构造函数  析构函数
class Test
{
public:
	//Test t;
	Test(int data=0)
	{
		m_data = data;
		cout<<"Create Test Obj : "<<this<<endl;
	}
	//Test t2 = t1;
	Test(const Test &t)  //拷贝构造函数  Test(Test * const this, Test &t)
	{
		m_data = t.m_data;
		cout<<"Copy Create Test Obj : "<<this<<endl;
	}

	//t2 = t1
	//void operator=( Test t)  //赋值语句  等号的重载
	Test& operator=(const Test &t)
	{
		cout<<"Assign "<<this<<" = "<<&t<<endl;
		if(this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}

	//对象脱离生存作用域
	~Test() //析构函数  --> 销毁对象  自己说的算
	{
		cout<<"Free Test Obj : "<<this<<endl;
	}
private:
	int m_data;
};
void main()
{
	Test t1(10); 
	Test t2 = t1;  //初始化    Test(&t2, t1)
	Test t3(t2);   //拷贝构造函数

	Test t4;
	t4 = t3; //赋值
}

/*
void main()
{
	Test t1(10);   //构造函数

	{
		Test t2(20);
	}

	Test t3(30);
}

/*
class Test
{
public:
	Test()
	{}
	Test(int data)
	{
		m_data = data;
	}
	Test(int data1, int data2)
	{
		m_data = data1 + data2;
	}
	~Test() //析构函数  -->
	{
		cout<<"Free Test Obj. "<<endl;
	}
private:
	int m_data;
};

void main()
{
	Test t;
	Test t1(10);
	Test t2(10, 20);
}

/*
//C++
class Test
{
public:
	//构造函数 -->初始化
	Test(int data = 0)
	{
		m_data = data;
		cout<<"Create Test Object : "<<this<<endl;
	}
public:
	void InitTest(int data = 0)
	{
		m_data = data;
	}
private:
	int m_data;
};


void main()
{
	Test t;  //
	Test t1; //
	Test t2; //

}

/*
//1 先识别类名
//2 识别数据成员
//3 改写函数成员

class Test
{
public:
	//void SetData(Test *const this, int data)
	void SetData(int data)
	{
		this->m_data = data;
	}
	//int GetData(const Test *const this)
	int GetData()const   //常方法
	{
		return m_data;
	}
private:
	int m_data;
};
void main()
{
	Test t;
	t.SetData(100);   //SetData(&t, 100);
	cout<<"t = "<<t.GetData()<<endl;
}

/*
class CGoods
{
public:
	//void Register(CGoods *const this, char *name , int count, int price)
	//c1.Register() --> Register(&c1, ....)
	void Register(char *name , int count, int price)
	{
		strcpy(this->m_name, name);
		this->m_count = count;
		this->m_price = price;
		this->m_total_price = m_price * m_count;
	}
	char* GetName()
	{
		return this->m_name;
	}
	void GetName(char *name)
	{
		strcpy(name, this->m_name);
	}
	//int GetCount(CGoods *this)
	int GetCount()
	{
		return this->m_count;  //c1  c2?
	}
	float GetPrice()
	{
		return m_price;
	}
	float GetTotalPrice()
	{
		return this->m_total_price;
	}
private:
	char m_name[10];
	int  m_count;
	float m_price;
	float m_total_price;
};

void main()
{
	CGoods c1, c2;
	c1.Register("C++", 10, 50);  //--> Register(&c1, "C++", 10, 50)
	c2.Register("Java", 8, 56);

	int count1 = c1.GetCount();  //GetCount(&c1);  
	int count2 = c2.GetCount();  //GetCount(&c2);  
}

/*
struct CGoods
{
	char name[10];
	int count;
	float price;
	float total_price;
};

void InitGoods(CGoods *_this, char *name, int count, float price)
{
	strcpy(_this->name, name);
	_this->count = count;
	_this->price = price;
	_this->total_price = _this->price * _this->count;
}

void main()
{
	CGoods  c1, c2;
	InitGoods(&c1, "C++", 10, 50);
	InitGoods(&c2, "Java", 8, 56);
}

class Test
{
public:
	void SetData(int data)
	{
		m_data = data;
	}
	void SetValue(double value)
	{
		m_value = value;
	}
private:
	int m_data;     //4 + 4
	double m_value; //8
	char m_char;    //1 + 7
};

void main()
{
	cout<<sizeof(Test)<<endl;
}

/*
class CGoods
{
public:
	inline void Register(char *name , int count, int price)
	{
		strcpy(m_name, name);
		m_count = count;
		m_price = price;
		m_total_price = m_price * m_count;
	}
	char* GetName()
	{
		return m_name;
	}
	void GetName(char *name)
	{
		strcpy(name, m_name);
	}
	int GetCount()
	{
		return m_count;
	}
	float GetPrice()
	{
		return m_price;
	}
	float GetTotalPrice()
	{
		return m_total_price;
	}
private:
	char m_name[10];
	int  m_count;
	float m_price;
	float m_total_price;
};

/*
class Test
{
public:
	void SetData(int data)
	{
		m_data = data;
	}
private:
	int m_data;     //4 + 4
	double m_value; //8
	char m_char;    //1 + 7
};

void main()
{
	cout<<sizeof(Test)<<endl;
}

/*
void main()
{
	Test t, t1, t2, t3 ; //实例化

	t.m_data = 10;
	t1.m_data = 100;
	
}

/*
class CGoods
{
public:
	inline void Register(char *name , int count, int price)
	{
		strcpy(m_name, name);
		m_count = count;
		m_price = price;
		m_total_price = m_price * m_count;
	}
	char* GetName()
	{
		return m_name;
	}
	void GetName(char *name)
	{
		strcpy(name, m_name);
	}
	int GetCount()
	{
		return m_count;
	}
	float GetPrice()
	{
		return m_price;
	}
	float GetTotalPrice()
	{
		return m_total_price;
	}
private:
	char m_name[10];
	int  m_count;
	float m_price;
	float m_total_price;
};

void main()
{
	CGoods c;
	c.Register("C++", 10, 56);   

	//char name[10];
	//c.GetName(name);
	char *name = c.GetName();
	cout<<"name = "<<name<<endl;
}

/*
class CGoods
{
public:
	inline void Register(char *name , int count, int price)
	{
		strcpy(m_name, name);
		m_count = count;
		m_price = price;
		m_total_price = m_price * m_count;
	}
public:
	inline void SetName(char *name)   //内联
	{
		strcpy(m_name, name);
	}
	void SetCount(int count)
	{
		m_count = count;
	}
	void SetPrice(float price)
	{
		m_price = price;
	}
	void  SetTotalPrice()
	{
		m_total_price = m_count * m_price;
	}
public:
	void GetName(char *name)
	{
		strcpy(name, m_name);
	}
	int GetCount()
	{
		return m_count;
	}
	float GetPrice()
	{
		return m_price;
	}
	float GetTotalPrice()
	{
		return m_total_price;
	}
private:
	char m_name[10];
	int  m_count;
	float m_price;
	float m_total_price;
};

void main()
{
	CGoods c;
	c.SetName("Python");
	c.SetCount(10);
	c.SetPrice(45);
}

/*
void main()
{
	CGoods c, c1;
	c.Register("C++", 10, 56);   
	c1.Register("Java", 8, 75);

	char name[10];
	c1.GetName(name);
	cout<<"name = "<<name<<endl;

	cout<<"count = "<<c1.GetCount()<<endl;

}
*/