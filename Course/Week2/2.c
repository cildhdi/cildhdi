#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int main()
{
	char cs[2];
	scanf("%s",cs);
	int i;
	for( i= 0;i<2;i++)
		cs[i]-=('A'-'a');
	printf("Use putchar:");
	putchar(cs[0]);
	putchar(' ');
	putchar(cs[1]);
	printf("\nUse printf:%c %c",cs[0],cs[1]);
	system("PAUSE");	
	return 0;
}
