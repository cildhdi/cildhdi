#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int call_times=0;

char to_upper(char ch)
{
	if(ch>='a'&&ch<='z')
	{
		ch=ch-'a'+'A';
		call_times++;
	}
	return ch;
}
int main()
{
	char str[80]= {0};
	printf("Enter a string: ");
	scanf("%[^\n]",str);
	unsigned int i,len=strlen(str);
	for(i=0; i<len; i++)
	{
		str[i]=to_upper(str[i]);
	}
	if(call_times==0)
		printf("no lowercase");
	else
		printf(str);
	return 0;
}


