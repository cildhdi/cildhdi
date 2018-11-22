#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
void print_space(unsigned int n)
{
	while (n != 0)
	{
		printf(" ");
		n--;
	}
}
int main()
{
	unsigned int n, i, j;
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
	{
		print_space((n - i) * 2);
		for (j = 1; j <= i; j++)
		{
			printf("%d ", j);
		}
		for (j = i - 1; j > 0; j--)
		{
			printf("%d ", j);
		}
		printf("\n");
	}
	for (i = n - 1; i > 0; i--)
	{
		print_space((n - i) * 2);
		for (j = 1; j <= i; j++)
		{
			printf("%d ", j);
		}
		for (j = i - 1; j > 0; j--)
		{
			printf("%d ", j);
		}
		printf("\n");
	}
	//system("pause");
	return 0;
}

