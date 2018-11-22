#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int char_cmp(const void* lc, const void* rc)
{
	return *(char*)lc - *(char*)rc > 0 ? 1 : 0;
}
int main()
{
	FILE* A = fopen("A", "r");
	char* buf = calloc(100, sizeof(char));
	fread(buf, sizeof(char), 81, A);
	unsigned int len = strlen(buf);
	FILE* B = fopen("B", "r");
	fread(buf + len, sizeof(char), 81, B);
	len = strlen(buf);
	qsort(buf, len, sizeof(char), char_cmp);
	FILE* o = fopen("C", "w");
	fputs(buf, o);
	fclose(A);
	fclose(B);
	fclose(o);
	return 0;
}





