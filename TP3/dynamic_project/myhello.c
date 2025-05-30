#include <stdio.h>
#include "mytools.h"
#include "myfunc.h"

int main()
{
	int a = 3;
	myHello();
	printf("The square of %d is %d\n",a,mySquare(a));
	return 0;
}
