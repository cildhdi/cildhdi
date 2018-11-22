#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	int nums[10], i, num;
	for (i = 0; i < 10; i++)
	{
		scanf("%d", nums + i);
	}
	scanf("%d", &num);
	int b = 0;
	for (i = 0; i < 10; i++)
	{
		if (nums[i] == num)
		{
			b = 1;
		}
	}
	if (b == 0)
	{
		printf("fail!");
		return 0;
	}
	for (i = 0; i < 10; i++)
	{
		if (nums[i] != num)
		{
			printf("%d ", nums[i]);
		}
	}
	return 0;
}

