#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmp(const void* ln, const void* rn)
{
	return *(int*)ln - *(int*)rn < 0 ? 1 : 0;
}

int main()
{
	int n, i, num, nums[10] = { 0 };
	printf("Input n: ");
	scanf("%d", &n);
	printf("Input %d integers: ", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &num);
		nums[i] = num;
	}
	qsort(nums, n, sizeof(int), cmp);
	printf("After sorted: ");
	for (i = 0; i < n; i++)
	{
		printf("%d ", nums[i]);
	}
	system("pause");
	return 0;
}

































// 	if ((a + b > c) && (b + c > a) && (a + c > b))
// 	{
// 		printf();
// 	}
// 	else
// 	{
// 		printf();
// 	}

