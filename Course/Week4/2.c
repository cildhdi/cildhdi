#include <stdio.h>
#include <stdlib.h>

void swap(int* p1, int* p2)
{
	int temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

int main()
{
	int n, i, num, max, min, maxindex = 0, minindex = 0;
	int nums[10] = { 0 };
	printf("Input n: ");
	scanf("%d", &n);
	printf("Input %d integers: ", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &num);
		nums[i] = num;
	}
	max = -10000;
	maxindex = -1;
	min = 10000;
	minindex = -1;
	for (i = 0; i < n; i++)
	{
		if (nums[i] > max)
		{
			max = nums[i];
			maxindex = i;
		}
	}
	swap(nums + maxindex, nums + n - 1);
	for (i = 0; i < n; i++)
	{
		if (nums[i] < min)
		{
			min = nums[i];
			minindex = i;
		}
	}
	swap(nums + minindex, nums);

	printf("After swapped: ");
	for (i = 0; i < n; i++)
	{
		printf("%d ", nums[i]);
	}
	return 0;
}



