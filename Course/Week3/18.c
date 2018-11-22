#include <stdio.h>
#include <string.h>
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
	long n;
	scanf("%ld",&n);
	if(is_h(n))
		printf("Y");
	else
		printf("N");
	return 0;
}




