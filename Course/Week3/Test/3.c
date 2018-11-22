#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char str[256];
	scanf("%s",str);
	int size=strlen(str);
	unsigned int i=0;
	if(str[0]=='-')
	{
		printf("-");
		for(i=1;i<size;i++)
		{
			if((str[i]-'0')%2==0)
			{
				printf("%d",str[i]-'0');
			}
		}
	}
	else
	{
		for(i=0;i<size;i++)
		{
			if((str[i]-'0')%2==0)
			{
				printf("%d",str[i]-'0');
			}
		}
	}
	return 0;
}

