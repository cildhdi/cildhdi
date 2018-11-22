#include <stdlib.h>
#include <stdio.h>

int main()
{
	int n, i, index = 0, sum;
	printf("Input n:");
	scanf("%d", &n);
	int* ps = calloc(n, sizeof(int));
	sum = n;
	for (i = 0; i < n; i++)
	{
		*(ps + i) = i + 1;
	}
	while (n != 1)
	{
		for (i = 0; i < sum; i++)
		{
			if (*(ps + i) != 0)
			{
				index++;
				if (index == 3)
				{
					printf("%d ", *(ps + i));
					*(ps + i) = 0;
					n--;
					index = 0;
				}
			}
		}
	}
	for (i = 0; i < sum; i++)
	{
		if (*(ps + i) != 0)
		{
			printf("\nLast No. is:%d", *(ps + i));
		}
	}
	return 0;
}
