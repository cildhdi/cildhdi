#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int char_cmp(const void* lc,const void* rc)
{
	return (int)(*(char*)lc)-(int)(*(char*)rc)> 0 ? 1: -1;
}

int main()
{
	char a[21]= {0};
	scanf("%s", a);
	int len = strlen(a), count = 0, i;
	for(i = 0; i < len; i++)
	{
		if(a[i]=='c')
			count++;
	}
	if(0 == count)
	{
		printf("No c\n");
	}
	else
	{
		printf("count:%d\n",count);
	}
	char b[21]= {0};
	unsigned int index = 0;
	for(i = 0; i < len; i++)
	{
		if(a[i] != 'c')
		{
			b[index]=a[i];
			index ++;
		}
	}
	printf("b:%s\n",b);
	qsort(b,strlen(b),sizeof(char),char_cmp);
	printf("b sorted:%s",b);
	return 0;
}
