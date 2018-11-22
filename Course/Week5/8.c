#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int str2i(char* str)
{
	unsigned int len = strlen(str), i = 0, digit = 0;
	char num[127] = { 0 };
	for (i = 0; i < len; i++)
	{
		if (str[i] >= '0'&&str[i] <= '9')
		{
			num[digit] = str[i];
			digit++;
		}
	}
	return atoi(num);
}



int main()
{
	char str[127] = { 0 };
	printf("Enter a string: ");
	scanf("%[^\n]", str);
	printf("digit=%d,%d", str2i(str), str2i(str) * 2);
	return 0;
}

