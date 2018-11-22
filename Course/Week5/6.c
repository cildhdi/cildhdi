#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_reverse(char* str, unsigned int size)
{
	if (size <= 1)return;
	char c = *(str);
	*str = *(str + size - 1);
	*(str + size - 1) = c;
	str_reverse(str + 1, size - 2);
}

int main()
{
	char str[127] = { 0 };
	printf("Enter a string: ");
	scanf("%s", str);
	str_reverse(str, strlen(str));
	printf(str);
	return 0;
}

