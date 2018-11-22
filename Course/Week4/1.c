#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i, num, max, index = 0;
	int nums[10] = { 0 };
	printf("Input n: ");
	scanf("%d", &n);
	printf("Input %d integers: ", n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &num);
		nums[i] = num;
	}
	max = nums[0];
	index = 1;
	for (i = 1; i < n; i++)
	{
		if (nums[i] > max)
		{
			max = nums[i];
			index = i;
		}
	}
	printf("max=%d,index=%d", max, index);
	return 0;
}

