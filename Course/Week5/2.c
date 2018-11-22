#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

static unsigned int array[10000] = { 0 };

void array_init()
{
	unsigned int i;
	array[0] = 1;
	array[1] = 1;
	for (i = 2; i < 10000; i++)
	{
		array[i] = array[i - 1] + array[i - 2];
	}
}

unsigned int fib(unsigned int n)
{
	return array[n - 1];
}

int main()
{
	array_init();
	unsigned int m = 0, n = 0, i = 1;
	printf("Input m: ");
	scanf("%d", &m);
	printf("Input n: ");
	scanf("%d", &n);
	while (1)
	{
		if (fib(i) >= m)
		{
			if (fib(i) <= n)
			{
				printf("%d ", fib(i));
			}
			else
			{
				break;
			}
		}
		i++;
	}
	return 0;
}

