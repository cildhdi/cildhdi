#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	int matrix[5][5] = {{ 0 }};
	unsigned int i, j;
	for (i = 0; i < 5; i++)
	{
		matrix[i][i] = 1;
		matrix[i][4 - i] = 1;
	}
	for (i = 0; i < 5; i++)
	{
		for (j = 0; j < 5; j++)
		{
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}

