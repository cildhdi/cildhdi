#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	char str[100] = { 0 };
	scanf("%[^\n]", str);
	unsigned int length = strlen(str), i;
	for (i = 0; i < (length + 1) / 2; i++)
	{
		if (str[i] != str[length - i - 1])
		{
			printf("NO");
			return 0;
		}
	}
	printf("YES");
	return 0;
}

