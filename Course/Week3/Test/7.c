#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	int num=0,day=0;
	while(1)
	{
		day++;
		if(num+pow(2,day)>=100)break;
		num+=pow(2,day);
	}
	printf("%.2lf",num*0.6/(day-1));
	return 0;
}

