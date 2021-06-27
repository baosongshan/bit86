#include<iostream>
using namespace std;

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