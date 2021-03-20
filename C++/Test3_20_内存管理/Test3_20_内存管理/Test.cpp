#include<iostream>
#include<vld.h>
#include<assert.h>
using namespace std;

//#define DISPLAY

class String;

class String_rep
{
	friend class String;
public:
	String_rep(const char *str="") : m_count(0)
	{
#ifdef DISPLAY
		cout<<"Create String_rep Obj."<<endl;
#endif
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
	String_rep(const String_rep &rep):m_count(0)
	{
		m_data = rep.m_data; //浅拷贝
	}
	String_rep& operator=(const String_rep &rep)
	{
		if(this != &rep)
		{
			m_data = rep.m_data; //浅赋值
		}
		return *this;
	}
	~String_rep()
	{
#ifdef DISPLAY
		cout<<"Free String_rep Obj."<<endl;
#endif
		delete []m_data;
		m_data = nullptr;
	}
public:
	void increment()
	{
		m_count++;
	}
	void decrement()
	{
		//this pn
		if(--m_count == 0)
			delete this;   //自杀式释放
	}
	char* GetData()const
	{return m_data;}
private:
	char *m_data;
	int   m_count;
};

///////////////////////////////////////////////////////////
class String
{
	friend ostream& operator<<(ostream &out, const String &s);
public:
	String(const char *str=""):pn(new String_rep(str))
	{
#ifdef DISPLAY
		cout<<"Create String  Obj."<<endl;
#endif
		pn->increment();
	}
	String(const String &s):pn(s.pn)
	{
		pn->increment();
	}
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			pn->decrement();
			pn = s.pn;
			pn->increment();
		}
		return *this;
	}
	~String()
	{
#ifdef DISPLAY
		cout<<"Free String Obj."<<endl;
#endif
		pn->decrement();
	}
public:
	//写时拷贝
	void to_upper()
	{
		String_rep *new_pn = new String_rep(pn->m_data);
		pn->decrement();
		pn = new_pn;
		pn->increment();
		
		char *p = pn->m_data;
		while(*p != '\0')
		{
			if(*p>='a' && *p<='z')
				*p -= 32;
			p++;
		}
	}
private:
	String_rep *pn;
};

ostream& operator<<(ostream &out, const String &s)
{
	out<<s.pn->GetData();
	return out;
}

void main()
{
	String s1("abc");
}

/*
void main()
{
	String s1("abc");
	String s2 = s1;
	String s3 = s2;

	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;

	s1.to_upper();

	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;

}

/*
class String
{
	friend ostream& operator<<(ostream &out, const String &s);
public:
	String(const char *str = "")
	{
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
		m_count++;
	}
	String(const String &s)
	{
		m_data = s.m_data; //浅拷贝
		m_count++;
	}
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			m_data = s.m_data; //浅赋值
			m_count++;
		}
		return *this;
	}
	~String()
	{
		if(--m_count == 0)
		{
			delete []m_data;
			m_data = nullptr;
		}
	}
public:
	void to_upper()
	{
		char *p = m_data;
		while(*p != '\0')
		{
			if(*p>='a' && *p<='z')
				*p -= 32;
			p++;
		}
	}
private:
	char *m_data;
	static int   m_count;
};

int   String::m_count = 0;

ostream& operator<<(ostream &out, const String &s)
{
	out<<s.m_data;
	return out;
}

//深拷贝 vs 浅拷贝

void main()
{
	String s1("abc");
	String s2 = s1;

	String s3("xyz");
	
	//s3 = s2;
	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;
	//cout<<"s3 = "<<s3<<endl;
	s1.to_upper();
	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;
}

/*
class String
{
	friend ostream& operator<<(ostream &out, const String &s);
public:
	String(const char *str = "")
	{
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}
	String(const String &s)
	{
		m_data = new char[strlen(s.m_data)+1];
		strcpy(m_data, s.m_data);
	}
	String& operator=(const String &s)
	{
		if(this != &s)
		{
			delete []m_data;

			m_data = new char[strlen(s.m_data)+1];
			strcpy(m_data, s.m_data);
		}
		return *this;
	}
	~String()
	{
		delete []m_data;
		m_data = nullptr;
	}
private:
	char *m_data;
};

ostream& operator<<(ostream &out, const String &s)
{
	out<<s.m_data;
	return out;
}

//深拷贝 vs 浅拷贝

void main()
{
	String s1("abc");
	String s2 = s1;
	String s3;
	s3 = s2;
	cout<<"s1 = "<<s1<<endl;
	cout<<"s2 = "<<s2<<endl;
	cout<<"s3 = "<<s3<<endl;
}

/*
void* operator new(size_t sz, void *ptr, int pos)
{
	return &((int*)ptr)[pos];
}

class Test
{
public:
	Test(int data=0) : m_data(data)
	{
		cout<<"Create Test Obj."<<endl;
	}
	~Test()
	{
		cout<<"Free Test Obj."<<endl;
	}
private:
	int m_data;
};

void main()
{
	//int *ptr = (int *)malloc(sizeof(int) * 10);
	Test ptr[10];
	//定位new
	new(ptr, 5) Test(200);
}


void main()
{
	int *ptr1 = (int *)malloc(sizeof(int)*10);
	int *ptr2 = new int;
}

/*
void* operator new(size_t sz)
{
	void *ptr = malloc(sz);
	return ptr;
}
void operator delete(void *ptr)
{
	free(ptr);
}

void* operator new[](size_t sz)
{
	void *ptr = malloc(sz);
	return ptr;
}
void operator delete[](void *ptr)
{
	free(ptr);
}

class Test
{
public:
	Test(int data=0) : m_data(data)
	{
		cout<<"Create Test Obj."<<endl;
	}
	~Test()
	{
		cout<<"Free Test Obj."<<endl;
	}
public:
	void* operator new(size_t sz)
	{
		void *ptr = malloc(sz);
		return ptr;
	}
	void operator delete(void *ptr)
	{
		free(ptr);
	}

	void* operator new[](size_t sz)
	{
		void *ptr = malloc(sz);
		return ptr;
	}
	void operator delete[](void *ptr)
	{
		free(ptr);
	}
private:
	int m_data;
};

void main()
{
	int *pt = new int; 
	Test *pt1 = new Test;
}


/*
void OutOfMemory(void)
{
	cout<<"Out Of Memory."<<endl;
	//exit(1);
}

void main()
{
	set_new_handler(OutOfMemory);
	int *pt = new int[536870911];
}

/*
//C++ 

void* operator new(size_t sz)
{
	void *ptr = malloc(sz);
	return ptr;
}
void operator delete(void *ptr)
{
	free(ptr);
}

void* operator new[](size_t sz)
{
	void *ptr = malloc(sz);
	return ptr;
}
void operator delete[](void *ptr)
{
	free(ptr);
}

class Test
{
public:
	Test(int data=0) : m_data(data)
	{
		cout<<"Create Test Obj."<<endl;
	}
	~Test()
	{
		cout<<"Free Test Obj."<<endl;
	}
private:
	int m_data;
};

void main()
{
	Test *pt = new Test[10]; //1-申请空间     2-调动构造函数
	//free(pt);
	//delete []pt;               //1-调动析构函数 2-释放空间
}


/*
void main()
{
	Test *pt = (Test*)operator new(sizeof(Test));
	operator delete(pt);
}

/*
void main()
{                            //operator new   
	Test *pt = new Test(10); //1-申请空间     2-调动构造函数
	delete pt;               //1-调动析构函数 2-释放空间
}


/*
void main()
{
	//Test *pt = (Test*)malloc(sizeof(Test));  //空间申请
	//free(pt);

	Test *pt = new Test[10]; //1-申请空间     2-调动构造函数
	//free(pt);
	delete []pt;               //1-调动析构函数 2-释放空间
}

/*
void main()
{
	//Test *pt = (Test*)malloc(sizeof(Test));  //空间申请
	//free(pt);

	Test *pt = new Test(10); //1-申请空间     2-调动构造函数
	delete pt;               //1-调动析构函数 2-释放空间
}

/*
void main()
{
	int *ptr = (int *)malloc(sizeof(int));
	*ptr = 10;

	int *ptr1 = new int(100);
}

/*
void main()
{
	//C
	int *ptr = (int*)malloc(sizeof(int)*10);
	if(NULL == ptr)
	{
		cout<<"Out Of Memory."<<endl;
		return;
	}
	free(ptr);


	//C++
	int *ptr1 = new int[10];
	delete []ptr1;
}

/*
void main()
{
	//C
	int *ptr = (int*)malloc(sizeof(int));
	if(NULL == ptr)
	{
		cout<<"Out Of Memory."<<endl;
		return;
	}
	free(ptr);


	//C++
	int *ptr1 = new int;
	delete ptr1;
}

/*
//malloc calloc realloc _alloca

class Stu
{
public:
	Stu(char *name, int age)
	{
		//m_name = name;
		m_name = (char*)malloc(strlen(name)+1);
		assert(m_name != NULL);
		strcpy(m_name, name);
		this->age = age;
	}
private:
	char *m_name;
	int age;
};

void main()
{
	Stu s("abc", 20);
}

/*
//void *_alloca( size_t size );
void main()
{
	int *ptr = (int*)_alloca(sizeof(int) * 10);
	//free(ptr);
}

/*
void main()
{
	int n;
	cin>>n;  //10
	
	int *ptr = (int*)malloc(sizeof(int) * n);
	if(NULL == ptr)
	{
		cout<<"Out Of Memory."<<endl;
		return;
	}

	free(ptr);
	//ptr = NULL;

	if(ptr != NULL)
		*ptr = 10;
}
*/