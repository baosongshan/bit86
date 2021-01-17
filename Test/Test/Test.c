#include<stdio.h>
#include<assert.h>
#include<vld.h>  //¼ì²âÊÇ·ñÓÐÄÚ´æÐ¹Â© F5

//void *memset( void *dest, int c, size_t count );
void main()
{
	int *p = (int*)malloc(sizeof(int) * 10);
	int *q = (int*)malloc(sizeof(int));
	//free(p);
}

/*
void main()
{
	strlen();
	strcat();
	strcpy();
	strcmp();

	memset();
	memcpy();
	memcmp();
	memmove();
}

/*
int main()
{
	int a = 0;

	//////////////////////////////////////
	assert(a != 0); //¶ÏÑÔ Ô¤ÑÔ

	printf("OK.\n");

	return 0;
}
*/