#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
long rec(int n)
{
	if(n==1||n==0)return 1;
	return n*rec(n-1);
}

long c(int m,int n)
{
	return (rec(m)/rec(m-n))/rec(n);
}
int main()
{
	int i,j,n;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		for(j=0;j<=i;j++)
			printf("%ld ",c(i,j));
		printf("\n");
	}
	return 0;
}





