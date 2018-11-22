#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int sort_cmp(void *ln, void *rn)
{
	return (*(int *)ln - *(int *)rn) < 0 ? 1 : 0;
}

int main()
{
	int nums[4] = {0};
	int num = 0;
	unsigned int i = 0;
	for (i = 0; i < 4; i++)
	{
		scanf("%d", &num);
		nums[i] = num;
	}
	qsort(nums, 4, sizeof(int), (int (*)(const void *, const void *))sort_cmp);
	for (i = 0; i < 4; i++)
	{
		printf("%d ", nums[i]);
	}
	//system("pause");
	return 0;
}
