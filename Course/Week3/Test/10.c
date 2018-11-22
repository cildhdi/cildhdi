#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int is_z(int num)
{
	if(num==2)return 0;
	unsigned int i=2;
	for(i=2; i<num; i++)
	{
		if(num%i==0)return 0;
	}
	return 1;
}

int main()
{
	int n=0;
	scanf("%d",&n);
	int i,j;
	for(i=3;; i++)
	{
		int ret=1;
		for(j=i; j<=i+n-1; j++)
		{
			if(is_z(j))
			{
				ret=0;
				break;
			}
		}
		if(ret)
		{
			for(j=i; j<=i+n-1; j++)
			{
				printf("%d ",j);
			}
			break;
		}
	}
	return 0;
}

