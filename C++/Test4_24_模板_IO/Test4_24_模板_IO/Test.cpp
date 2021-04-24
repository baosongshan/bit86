#include<iostream>
#include<bitset>
#include<assert.h>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;

void main()
{
	stringstream sstream;
	
	sstream << "first" << " " << "string,";
	sstream << " second string";
	

	string strobj = sstream.str();

	cout<<strobj<<endl;

	const char *res = strobj.c_str();
	

}

/*
void main()
{
	int a = 12345;
	string str;
	stringstream ss;
	ss<<a;
	ss>>str;
	cout<<"str = "<<str<<endl;

	ss.clear();//

	double d = 12.34;
	ss << d;
	ss >> str; //12345\012.34\0
	cout << str << endl;
}

/*
void main()
{
	int a = 4618461;
	char str[30] = {0};

	//itoa(a, str, 10);
	sprintf(str, "%d", a);

	cout<<"str = "<<str<<endl;
}

/*
struct ServerInfo
{
	char _ip[32]; // ip
	int  _port; // 端口
};

class ConfigManager
{
public:
	ConfigManager(string cfg = "bitserver.cfg")
		:_configFile(cfg)
	{}
	~ConfigManager()
	{}
public:
	void ReadInfo(ServerInfo &info)
	{
		ifstream ifile(_configFile.c_str(), ios::in);
		assert(ifile);
		ifile>>info._ip>>info._port;
		ifile.close();
	}
	void WriteInfo(ServerInfo &info)
	{
		ofstream ofile(_configFile.c_str(), ios::out);
		assert(ofile);
		ofile<<info._ip<<" "<<info._port;
		ofile.close();
	}

private:
	string _configFile;
};

void main()
{
	ConfigManager config;
	ServerInfo ser_info = {"10.125.18.131", 8989};

	//config.ReadInfo(ser_info);
	config.WriteInfo(ser_info);

	

}

/*
//二进制

void main()
{
	int ar[10];

	ifstream ifile;  //cin  //cout
	ifile.open("Test22.txt", ios::in | ios::binary);
	assert(ifile);

	ifile.read((char *)ar, sizeof(int)*10);

	ifile.close();
}

/*
void main()
{
	int ar[] = {12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar) / sizeof(ar[0]);

	ofstream ofile;
	ofile.open("Test22.txt", ios::out | ios::binary);
	assert(ofile);

	ofile.write((const char*)ar, sizeof(int)*n);

	ofile.close();
}

/*
void main()
{
	int ar[10];

	FILE *fp = fopen("Test11.txt", "rb");
	assert(fp != NULL);

	fread(ar, sizeof(int), 10, fp);

	fclose(fp);
}

/*
void main()
{
	int ar[] = {12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar) / sizeof(ar[0]);

	FILE *fp = fopen("Test11.txt", "wb");
	assert(fp != NULL);

	fwrite(ar, n, sizeof(int), fp);

	fclose(fp);
}

/*
//文本文件  
void main()
{
	int ar[10];

	ifstream ifile;
	ifile.open("Test2.txt", ios::in);
	assert(ifile);

	for(int i=0; i<10; ++i)
		ifile>>ar[i];

	ifile.close();
}

/*
void main()
{
	int ar[10];

	FILE *fp = fopen("Test1.txt", "r");
	assert(fp != NULL);

	for(int i=0; i<10; ++i)
		fscanf(fp, "%d", &ar[i]);

	fclose(fp);
}

/*
void main()
{
	int ar[] = {12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar) / sizeof(ar[0]);

	ofstream ofile("Test3.txt");
	//ofile.open("Test2.txt", ios::out);
	//assert(ofile);

	for(int i=0; i<n; ++i)
		ofile<<ar[i]<<" ";

	ofile.close();
}

/*
void main()
{
	int ar[] = {12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar) / sizeof(ar[0]);

	ofstream ofile;
	ofile.open("Test2.txt", ios::out);
	assert(ofile);

	for(int i=0; i<n; ++i)
		ofile<<ar[i]<<" ";

	ofile.close();
}

/*
void main()
{
	int ar[] = {12,23,34,45,56,67,78,89,90,100};
	int n = sizeof(ar) / sizeof(ar[0]);

	FILE *fp = fopen("Test1.txt", "w");
	assert(fp != NULL);

	for(int i=0; i<n; ++i)
	{
		fprintf(fp, "%d ", ar[i]);
	}

	fclose(fp);
}

/*
void main()
{
	string str;
	while(getline(cin, str))
	{
		cout<<str<<endl;
	}
}

/*
class IntArray
{
public:
	IntArray()
	{
		for(int i=1; i<=10; ++i)
		{
			ar[i-1] = i;
		}
	}

	int GetSum(int time)
	{
		int sum = 0;
		for(int i=0; i<10; ++i)
		{
			sum += ar[i];
		}
		return sum *time;
	}

private:
	int ar[10];
};

class FloatArray
{
public:
	FloatArray()
	{
		for(int i=0; i<10; ++i)
		{
			ar[i] = i + 1.11;
		}
	}

	float GetSum(float time)
	{
		 float sum = 0.0f;
		for(int i=0; i<10; ++i)
		{
			sum += ar[i];
		}
		return sum *time;
	}
private:
	float ar[10];
};

////////////////////////////////////////////////////////////
template<class Type>
class NumTraits
{};

template<>
class NumTraits<IntArray>
{
public:
	typedef int return_type; 
	typedef int arg_type;
};

template<>
class NumTraits<FloatArray>
{
public:
	typedef float return_type; 
	typedef float arg_type;
};

template<class Type>
class CApply
{
public:
	//完美兼顾
	typename NumTraits<Type>::return_type GetSum(Type &obj,typename NumTraits<Type>::arg_type time)
	{
		return obj.GetSum(time);
	}
};

void  main()
{
	IntArray intA;
	FloatArray floatA;  //

	CApply<IntArray> obj;
	cout<<obj.GetSum(intA,3)<<endl;

	CApply<FloatArray> obj1;
	cout<<obj1.GetSum(floatA,2.3)<<endl;
}

/*
void  main()
{
	IntArray intA;
	//cout<<"int sum = "<<intA.GetSum()<<endl;

	FloatArray floatA;
	//cout<<"float sum = "<<floatA.GetSum()<<endl;
}

/*
template<class T1, class T2>
class Data
{
public:
	Data() 
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};

//全特化
template<>
class Data<int, char>
{
public:
	Data() 
	{
		cout << "Data<int, char>" << endl; 
	}
private:
	int _d1;
	char _d2;
};

//偏特化
template<class T>
class Data<T,T>
{
public:
	Data() 
	{
		cout << "Data<T1, T2>" << endl;
	}
private:
	T _d1;
	T _d2;
};

template<class T>
class Data<T,int>
{
public:
	Data() 
	{
		cout << "Data<T, int>" << endl;
	}
private:
	T _d1;
	T _d2;
};


template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data() 
	{
		cout << "Data<T1*, T2*>" << endl;
	}
private:
	T1 _d1;
	T2 _d2;
};

void main()
{
	Data<int, short> dt;
	Data<int, char> dt1;
	Data<char, char> dt2;
	Data<char*, int*> dt3;
}

/*
//90%
template<class T>
bool IsEqual(T left, T right)
{
	cout<<"T type = "<<typeid(T).name()<<endl;
	return left == right;
}

template<>
bool IsEqual<char*>(char *left, char *right)
{
	return strcmp(left, right)==0;
}

bool IsEqual(char *left, char *right)
{
	return strcmp(left, right)==0;
}

void Test()
{
	char p1[] = "hello";
	char p2[] = "hello";
	//int p1 = 10;
	//int p2 = 20;

	if (IsEqual(p1, p2))
		cout <<"p1 == p2"<< endl;
	else
		cout << "p1 != p2"<< endl;
}

void main()
{
	Test();
}
/*
template<typename Type, size_t _N=8>
class SeqList
{
public:
	SeqList()
	{
		capacity = sz > _N ? sz : _N;
		base = new Type[capacity];
		size = 0;
	}
private:
	Type *base;
	size_t capacity;
	size_t size;
};


void main()
{
	SeqList<int, 100> list;
}

/*
//#define SEQLIST_DEFAULT_SIZE 8

template<typename Type, size_t _N=8>
class SeqList
{
public:
	SeqList(int sz = SEQLIST_DEFAULT_SIZE)
	{
		capacity = sz > SEQLIST_DEFAULT_SIZE ? sz : SEQLIST_DEFAULT_SIZE;
		base = new Type[capacity];
		size = 0;
	}
private:
	//enum{SEQLIST_DEFAULT_SIZE = 8};
	//const int SEQLIST_DEFAULT_SIZE = 8;
private:
	Type *base;
	size_t capacity;
	size_t size;
};


void main()
{
	SeqList<int> list(10);
}
*/