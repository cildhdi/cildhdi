#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void lmove(int ptr[], unsigned int size, unsigned int offset)
{
	int* temp = malloc(sizeof(int)*offset);
	memcpy(temp, ptr, sizeof(int)*offset);
	memcpy(ptr, ptr + offset, sizeof(int)*(size - offset));
	memcpy(ptr + size - offset, temp, sizeof(int)*offset);
	free(temp);
}

int main()
{
	printf("Enter 10 integers: ");
	unsigned int i = 0, x = 0;
	int nums[10] = { 0 };
	for (i = 0; i < 10; i++)
	{
		scanf("%d", nums + i);
	}
	printf("Enter x: ");
	scanf("%d", &x);
	lmove(nums, 10, x);
	printf("After Circle left shift %d bit: ", x);
	for (i = 0; i < 10; i++)
	{
		printf("%4d", nums[i]);
	}
	return 0;
}

