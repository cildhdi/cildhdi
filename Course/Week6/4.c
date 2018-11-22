#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

int strmcpy(char* s, const char* t, unsigned int m)
{
	if (s == 0 || t == 0)
	{
		return 0;
	}
	unsigned int len = strlen(t);
	if (m > len)
	{
		return 0;
	}
	memcpy(s, t + m - 1, (len - m + 1) * sizeof(char));
	return 1;
}

int main()
{
	char str[80] = { 0 }, dest[80] = { 0 };
	int m;
	printf("Input a string:");
	scanf("%[^\n]", str);
	printf("Input an integer:");
	scanf("%d", &m);
	strmcpy(dest, str, m);
	printf("Output is:");
	printf(dest);
	return 0;
}
