#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int hex2dec(char* num)
{
	char c;
	int i = 0;
	unsigned int len = strlen(num), digit = 0, sum = 0;
	for (i = 0; i < len; i++)
	{
		c = num[i];
		if (!((c >= '0'&&c <= '9') || (c >= 'a'&&c <= 'f') || (c >= 'A'&&c <= 'F')))
		{
			num[i] = 0;
			break;
		}
	}
	len = strlen(num);
	for (i = len - 1; i >= 0; i--)
	{
		c = num[i];
		if (c >= '0'&&c <= '9')
		{
			digit = c - '0';
		}
		else if (c >= 'a'&&c <= 'f')
		{
			digit = c - 'a' + 10;
		}
		else if (c >= 'A'&&c <= 'F')
		{
			digit = c - 'A' + 10;
		}
		sum += (pow(16, len - i - 1)*digit);
	}
	return sum;
}
int main()
{
	char num[127] = { 0 };
	printf("Enter a string: ");
	scanf("%s", num);
	printf("%d", hex2dec(num));
	return 0;
}
