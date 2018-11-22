#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	char ch;
	scanf("%c", &ch);
	putchar(((ch <= 'Z'&&ch >= 'A') || (ch <= 'z'&&ch >= 'a')) ? (ch <= 'Z'&&ch >= 'A') ? ch - 'A' + 'a' : ch - 'a' + 'A' : ch);
	return 0;
}

