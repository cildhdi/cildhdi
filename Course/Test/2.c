#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main()
{
	int n, i, j;
	scanf("%d", &n);
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(j < i)
				printf("%4d", i + 1);
			else
				printf("%4d", j + 1);
		}
		printf("\n");
	}
	return 0;
}
