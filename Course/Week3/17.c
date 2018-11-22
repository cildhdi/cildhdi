#include <stdio.h>

int rec(int n)
{
	if(n==1)return 1;
	return n*rec(n-1);
}

int main()
{
	int n,i,sum=0;
	scanf("%d",&n);
	for(i=1; i<=n; i++)
		sum+=rec(i);
	printf("%d",sum);
	return 0;
}




