#include <stdio.h>
#include <stdlib.h>

void print(unsigned int num,char c)
{
	while(num!=0)
	{
		putchar(c);
		putchar(' ');
		num--;
	}
}

int main()
{
	int i;
	for(i=0; i<4; i++)
	{
		print(i+1,'1');
		print(3-i,'0');
		putchar('\n');
	}
	return 0;
}


