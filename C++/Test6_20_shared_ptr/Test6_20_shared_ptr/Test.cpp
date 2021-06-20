#include"shared_ptr.h"

void main()
{
	int *p = new int(100);
	shared_ptr<int> ps(p);
	
	shared_ptr<int> ps1 = ps;
	cout<<"p use_count = "<<ps.use_count()<<endl;

	int *q = new int(200);
	shared_ptr<int> ps2(q);
	ps2 = ps1;

	cout<<"q use_count = "<<ps2.use_count()<<endl;

	

}

/*
void main()
{
	int *p = new int(1);
	shared_ptr<int> ps(p);
	cout<<"use_count = "<<ps.use_count()<<endl;

	shared_ptr<int> ps1 = ps;
	cout<<"use_count = "<<ps.use_count()<<endl;

	{
		shared_ptr<int> ps2 = ps1;
		cout<<"use_count = "<<ps.use_count()<<endl;
	}
	cout<<"use_count = "<<ps.use_count()<<endl;
	cout<<*ps<<endl;
}
*/