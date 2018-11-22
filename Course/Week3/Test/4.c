#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_z(int num)
{
	if(num==2)return 1;
	unsigned int i=2;
	for(i=2; i<num; i++)
	{
		if(num%i==0)return 0;
	}
	return 1;
}
int main()
{
	unsigned int a,b,mr=1,i;
	scanf("%d%d",&a,&b);
	if(a==2&&b==2)
	{
		printf("OK");
		return 0;
	}
	for(i=1; i<a; i++)
	{
		if(a%i==0&&is_z(i))
		{
			//printf("%d ",i);
			mr*=i;
		}
	}
	printf(mr==b?"OK":"Err");
	return 0;
}


