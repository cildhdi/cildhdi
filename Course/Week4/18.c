#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	long num;
	scanf("%ld", &num);
	char szNum[100] = { 0 };
	unsigned int i = 0, lsize = sizeof(long) * 8;
	for (i = 0; i < lsize; i++, num >>= 1)
		szNum[lsize - i - 1] = '0' + (num & 1);
	for (i = 0; i < strlen(szNum); i++)
		if (szNum[i] != '0')
		{
			while (szNum[i] != 0)
				putchar(szNum[i++]);
			return 0;
		}
	putchar('0');
	return 0;
}

































// 	if ((a + b > c) && (b + c > a) && (a + c > b))
// 	{
// 		printf();
// 	}
// 	else
// 	{
// 		printf();
// 	}

