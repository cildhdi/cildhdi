#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
	int i,sum=0;
	for(i=2; i<101; i+=2)
		sum+=i;
	printf("%d",sum);
	return 0;
}




