#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void ps(int n)
{
	while(n>0)
	{
		printf(" ");
		n--;
	}
}
int main()
{
	int n=0,i,j;
	scanf("%d",&n);
	for(i=1;i<=n;i++)
	{
		ps((n-i)*2);
		for(j=1;j<i+1;j++)
		{
			printf("%d ",j);
		}
		for(j=i-1;j>0;j--)
		{
			printf("%d ",j);
		}
		printf("\n");
	}
	return 0;
}

