#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int is(int num)
{
	char sn[5]= {0};
	sprintf(sn,"%d",num);
	unsigned int len=strlen(sn),sum=0,i;
	for(i=0; i<len; i++)
	{
		sum+=pow(sn[i]-'0',3);
	}
	return sum==num;
}

int main()
{
	unsigned int m=0,n=0,i;
	printf("Input m: ");
	scanf("%d",&m);
	printf("Input n: ");
	scanf("%d",&n);
	for(i=m; i<=n; i++)
	{
		if(is(i))
			printf("%d\n",i);
	}
	return 0;
}

