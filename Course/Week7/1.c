#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	FILE* f = fopen("f1.txt","r");
	char* buf = calloc(81 , sizeof(char));
	fread(buf, sizeof(char), 81, f);
	FILE* op = fopen("f1bak.txt", "w");
	unsigned int len = strlen(buf), i;
	for(i = 0;i < len;i++)
	{
		if(*(buf + i) >= 'a' && *(buf + i) <= 'z')
		{
			*(buf + i) += ('A' - 'a');
		}
		fputc(*(buf + i), op);
	}
	fclose(f);
	fclose(op);
	return 0;
}





