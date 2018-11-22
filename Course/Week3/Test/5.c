#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int is_z(int num)
{
	if(num==2)return 0;
	unsigned int i=2;
	for(i=2;i<num;i++)
	{
		if(num%i==0)return 0;
	}
	return 1;
}
int main()
{
	char szNum[4]={0};
	char szRev[4]={0};
	scanf("%s",szNum);
	int num1=atoi(szNum);
	int i;
	for(i=0;i<3;i++)
	{
		szRev[i]=szNum[2-i];
	}
	int num2=atoi(szRev);
	if(is_z(num1)&&is_z(num2))
	{
		printf("OK");
	}
	else
	{
		printf("Err");
	}
	return 0;
}

