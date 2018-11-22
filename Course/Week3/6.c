#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num = 0;
	scanf("%d", &num);
	putchar('A' + 9 - ((num < 60 ? 50 : num) / 10));
	return 0;
}

