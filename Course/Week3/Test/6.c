#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char szNum[6]= {0};
	scanf("%s",szNum);
	int size=strlen(szNum);
	printf("%d ",size);
	int i;
	for(i=size-1; i!=-1; i--)
	{
		if(szNum[i]-'0'!=0)
			printf("%d",szNum[i]-'0');
	}
	return 0;
}


