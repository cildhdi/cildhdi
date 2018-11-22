#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define bool int
#define false 0
#define true 1

bool in_array(int* p,unsigned int size,int num)
{
	unsigned int i;
	for(i=0; i<size; i++)
	{
		if(*(p+i)==num) return true;
	}
	return false;
}

int main()
{
	int i, A[5],B[5];
	printf("Please Enter Array A,5 digits: ");
	for (i = 0; i < 5; i++)
		scanf("%d", A + i);
	printf("Please Enter Array B,5 digits: ");
	for (i = 0; i < 5; i++)
		scanf("%d", B + i);
	printf("A B intersection is:");
	for(i=0; i<5; i++)
	{
		if(in_array(B,5,*(A+i)))
			printf("%d ",*(A+i));
	}
	return 0;
}



