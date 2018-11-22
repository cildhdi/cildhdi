#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char sz[127]= {0};
	int sum=0;
	scanf("%[^\n]",sz);
	char* token=strtok(sz," ");
	while(token)
	{
		sum++;
		token=strtok(NULL," ");
	}
	printf("%d",sum);
	return 0;
}

