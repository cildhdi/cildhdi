#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <string.h>

int main()
{
	char* strs = calloc(3 * 40, sizeof(char)), i;
	printf("Enter 3 strings:\n");
	for (i = 0; i < 3; i++)
		scanf("%[^\n]", strs + i * 40);
	qsort(strs, 3, 40 * sizeof(char), (int(*)(const void*, const void*))strcmp);
	printf("The largest string is %s", strs + 2 * 40);
	return 0;
}




