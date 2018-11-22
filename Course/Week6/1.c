#include <stdio.h>
#include <stdlib.h>

int int_cmp(const void* ln,const void* rn)
{
	return *(int*)ln-*(int*)rn>0?1:0;
}

void sort(int a[],int n)
{
	qsort(a,n,sizeof(int),int_cmp);
}

int main()
{
	printf("Input n:");
	int n,i;
	scanf("%d",&n);
	int* nums=calloc(n,sizeof(int));
	printf("Input array of 10 integers:");
	for(i=0;i<n;i++)
		scanf("%d",nums+i);
	sort(nums,n);
	printf("After sorted the array is:");
	for(i=0;i<n;i++)
		printf("%d ",*(nums+i));
	return 0;
}


