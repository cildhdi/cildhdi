#include <stdio.h>
#include <stdlib.h>

int cmp(const void* ln,const void* rn)
{
	return *(int*)ln-*(int*)rn<0?1:0;
}
int main()
{
	int nums[3];
	unsigned int i=0;
	int num=0;
	for(i=0;i<3;i++)
	{
		scanf("%d",&num);
		nums[i]=num;
	}
	qsort(nums,3,sizeof(int),cmp);
	for(i=0;i<3;i++)
	{
		printf("%d ",nums[i]);
	}
	return 0;
}

