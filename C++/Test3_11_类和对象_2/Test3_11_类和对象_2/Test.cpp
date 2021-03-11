#include<iostream>
#include<vld.h>
using namespace std;

#define DISPLAY

class Test
{
public:
	Test(int d=0)
	{
		m_data = d;
#ifdef DISPLAY
		cout<<"Cretea Test Obj:"<<this<<endl;
#endif
	}
	//�﷨Ҫ��
	//����Ҫ��
	Test(const Test &t)
	{
		m_data = t.m_data;
#ifdef DISPLAY
		cout<<"Copy Create Test Obj:"<<this<<endl;
#endif
	}
	Test& operator=(const Test &t) //�Ⱥŵ�����
	{
#ifdef DISPLAY
		cout<<"Assign,"<<this<<" : "<<&t<<endl;
#endif
		if(this != &t) //�Ƿ��Լ����Լ���ֵ
		{
			m_data = t.m_data;
		}
		return *this;
	}
	~Test()
	{
#ifdef DISPLAY
		cout<<"Free Test Obj:"<<this<<endl;
#endif
	}
public:
	Test* operator&()
	{
		return this;
	}
	const Test* operator&()const
	{
		return this;
	}
public:
	void fun()     //Test * const this
	{
		cout<<"This is fun()."<<endl;
	}
	void fun()const //const Test * const this
	{
		cout<<"This is fun()const."<<endl;
	}
public:
	//int GetData(const Test *const this)
	int GetData()const
	{return m_data;}
private:
	int m_data;
};

void main()
{
	Test t;
	cout<<"data = "<<t.GetData()<<endl;
	t = 100;
	cout<<"data = "<<t.GetData()<<endl;

	int value = (int)t;
	cout<<"value = "<<value<<endl;
}

/*
void main()
{
	const Test t;
	t.fun();
}

/*
void main()
{
	const Test t(100);
	const Test *pt = &t;
}

/*
Test fun(const Test &x)   //������
{
	int value = x.GetData();
	return Test(value);
}

void main()
{
	Test t1(10);
	Test t2 = fun(t1);
}

/*
Test fun(const Test &x)   //������
{
	int value = x.GetData();
	Test tmp(value);    //������ʱ������﷨
	return tmp;
}

void main()
{
	Test t1(10);
	Test t2 = fun(t1);
}

/*
Test fun(Test x)   //������
{
	int value = x.GetData();
	Test tmp(value);    //������ʱ������﷨
	return tmp;
}

void main()
{
	Test t1(10);
	Test t2 = fun(t1);
}

/*
Test fun(Test &x)   //������
{
	int value = x.GetData();
	return Test(value);    //������ʱ������﷨
}

void main()
{
	Test t1(10);
	Test t2;
	t2 = fun(t1);
}

/*
Test& fun(const Test &x)   //������
{
	int value = x.GetData();
	Test tmp(value);
	return tmp;
}

void main()
{
	Test t1(10);
	Test t2;
	t2 = fun(t1);
}

/*
Test fun(const Test &x)
{
	int value = x.GetData();
	Test tmp(value);
	return tmp;
}

void main()
{
	Test t1(10);
	Test t2;
	t2 = fun(t1);
}

/*
Test fun(Test x)
{
	int value = x.GetData();
	Test tmp(value);
	return tmp;
}

void main()
{
	Test t1(10);
	Test t2;
	t2 = fun(t1);
}

/*
class String
{
public:
	String(const char *str="")
	{
		m_data = (char*)malloc(strlen(str)+1);
		strcpy(m_data, str);
	}
	~String()
	{
		free(m_data);
		m_data = nullptr;
	}
private:
	char *m_data;
};

void main()
{
	char ar[] = "Hello Cpp";
	String str(ar);  //1 
	String str1 = str;
}

/*
class Test
{
public:
	Test(int d=0)
	{
		m_data = d;
		m_value = d;
	}
private:
	int m_data;
	int m_value;
};

void main()
{
	Test t(100);
	Test t1(t);   //����Ա����  ��ֵ����
	Test t2;
	t2 = t1;      //����Ա��ֵ  ��ֵ��ֵ
}

/*
class Test
{
public:
	Test(int d=0)
	{
		m_data = d;
		cout<<"Cretea Test Obj:"<<this<<endl;
	}
	//�﷨Ҫ��
	//����Ҫ��
	Test(const Test &t)
	{
		m_data = t.m_data;
		cout<<"Copy Create Test Obj:"<<this<<endl;
	}
	Test& operator=(const Test &t) //�Ⱥŵ�����
	{
		cout<<"Assign,"<<this<<" : "<<&t<<endl;
		if(this != &t) //�Ƿ��Լ����Լ���ֵ
		{
			m_data = t.m_data;
		}
		return *this;
	}
	~Test()
	{
		cout<<"Free Test Obj:"<<this<<endl;
	}
public:
	int GetData()const
	{return m_data;}
private:
	int m_data;
};

void main()
{
	int a = 1;
	int b;
	int c;
	c = b = a;

	Test t1(10);
	Test t2; //1
	Test t3;
	
	//t2.operator=(t1); //operator=(&t2, t1); this  &t1
	t3 = t2 = t1;  //��ֵ���

	//t3.operator=(t2.operator=(t1))
}

/*
Test fun(Test x)
{
	int value = x.GetData();
	Test tmp(value);
	return tmp;
}

void main()
{
	Test t1(10);
	Test t2 = t1;  //1
	fun(fun(t2));
}

/*
void main()
{
	Test t1(10);
	//t2.Test(t1);
	Test t2 = t1;  //Test t2(t1);
}
/*
class Test
{
public:
	//Test(Test *const this, int data=0)
	Test(int data = 0)
	{
		m_data = data;
		cout<<"Cretea Test Obj:"<<this<<endl;
	}
	Test(const Test &t)
	{
		m_data = t.m_data;
		cout<<"Copy Create Test Obj:"<<this<<endl;
	}
	Test& operator=(const Test &t)
	{
		cout<<"Assign,"<<this<<" : "<<&t<<endl;
		if(this != &t)
		{
			m_data = t.m_data;
		}
		return *this;
	}
	~Test()
	{
		cout<<"Free Test Obj:"<<this<<endl;
	}
public:
	void Show()const
	{
		cout<<m_data<<endl;
	}
private:
	int m_data;
};

void main()
{
	Test t(100);   //t.Test(10)==> Test(&t, 10)
	Test t1 = t;   //��ʼ��
	Test t2;
	t2 = t1;       //��ֵ

}
*/