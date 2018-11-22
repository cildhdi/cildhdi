#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num;
	scanf("%d", &num);
	putchar(num % 3 == 0 || num % 5 == 0 || num % 7 == 0 ? 'Y' : 'N');
	return 0;
}

