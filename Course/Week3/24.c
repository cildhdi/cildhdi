#include <stdio.h>
#include <math.h>

int main()
{
	int i;
	for(i=1; i<1000; i++)
	{
		if(i%3==1&&i%5==2&&i%7==3)
			printf("%d ",i);
	}
	return 0;
}




