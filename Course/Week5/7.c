#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void str_cpy(char* _Dst, char* _Src, unsigned int pos)
{
	memcpy(_Dst, _Src + pos - 1, (strlen(_Src) - pos + 1) * sizeof(char));
}


int main()
{
	char str[127] = { 0 }, oStr[127] = { 0 };
	printf("Enter a string: ");
	scanf("%[^\n]", str);
	printf("Enter m: ");
	unsigned int m;
	scanf("%d", &m);
	str_cpy(oStr, str, m);
	printf(oStr);
	return 0;
}
