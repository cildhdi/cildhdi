#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	int i=100;
	for(i=100; i<1000; i++)
	{
		char num[4]= {0};
		sprintf(num,"%d",i);
		if((pow(num[0]-'0',3)+pow(num[1]-'0',3)+pow(num[2]-'0',3))==i)
			printf("%d ",i);
	}
	return 0;
}





