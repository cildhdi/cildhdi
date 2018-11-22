#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	printf("Input a string:");
	char line[80]= {0};
	scanf("%[^\n]",line);
	printf("after converted:");
	unsigned int i,len=strlen(line);
	for(i=0; i<len; i++)
	{
		putchar(line[len-i-1]);
	}
	return 0;
}


