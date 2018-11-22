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
	unsigned int n, i;
	printf("Enter n: ");
	scanf("%d", &n);
	printf("Enter %d integers: ", n);
	int  num, nums[10];
	for (i = 0; i < n; i++)
	{
		scanf("%d", nums + i);
	}
	printf("Enter insert integer: ");
	scanf("%d", &num);
	for (i = 0; i < n; i++)
	{
		if (num < nums[i])
		{
			printf("%d ", num);
			num = 10000;
		}
		printf("%d ", nums[i]);
	}
	//system("pause");
	return 0;
}

