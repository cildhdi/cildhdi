#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int* binary_search(int* nums, unsigned int noe, int value)
{
	if (noe == 1)
	{
		if (*nums == value)
			return nums;
		else
			return 0;
	}
	unsigned int mid = 0;
	if (noe % 2 == 0)
		mid = noe / 2;
	else
		mid = (noe + 1) / 2;
	if (value < *(nums + mid))
		return binary_search(nums, mid, value);
	else
		return binary_search(nums + mid, noe - mid, value);
}
int main()
{
	int nums[9] = { 1,12,23,34,45,56,67,68,89 }, value;
	scanf("%d", &value);
	int* result = binary_search(nums, sizeof(nums) / sizeof(int), value);
	printf("%ld", result == 0 ? -1 : result - nums);
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

