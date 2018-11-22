#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	char num[10];
	scanf("%s",num);
	unsigned int size=strlen(num),i;
	for(i=0;i<size;i++)
		printf("%2c",num[i]);
	return 0;
} 

