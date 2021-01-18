#ifndef _TEST_H_
#define _TEST_H_

#include"Max.h"

int fun(int a, int b, int c)
{
	return Max(Max(a, b), c);
}

#endif /* _TEST_H_ */