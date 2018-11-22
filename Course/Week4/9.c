#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	unsigned int m, n, i;
	double sum = 0;
	scanf("%d%d", &m, &n);
	double* nums = malloc(m*n * sizeof(double));
	for (i = 0; i < m*n; i++)
	{
		scanf("%lf", nums + i);
	}
	for (i = 0; i < n; i++)
	{
		sum += *(nums + i);
	}
	for (i = 1; i < m - 1; i++)
	{
		sum += (*(nums + i * n) + *(nums + i * n + n - 1));
	}
	for (i = 0; i < n; i++)
	{
		sum += *(nums + n * (m - 1) + i);
	}
	printf("%.1lf", sum);
	return 0;
}

