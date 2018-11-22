#include <stdio.h>
#include <stdlib.h>


int main()
{
	char c;
	scanf("%c",&c);
	putchar(c+5>'z'?c+4-'z'+'a':c+5);
	return 0;
}

