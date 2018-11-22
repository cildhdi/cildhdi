#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
int is_h(int num)
{
	char szNum[4]={0};
	sprintf(szNum,"%d",num);
	unsigned int length=strlen(szNum),i;
	for(i=0;i<(length+1)/2;i++)
	{
		if(szNum[i]!=szNum[length-i-1])
			return 0;
	}
	return 1;
}
int main()
{
	int i=2;
	for(i=2; i<1000; i++)
	{
		if(is_z(i)&&is_h(i))
			printf("%d ",i);
	}
	return 0;
}





