#include <stdio.h>

void print_stars(unsigned int n)
{
	unsigned int i=0;
	for(; i<n; i++)
		printf("*");
	printf("\n");
}

int main()
{
	unsigned int i=4;
	for(; i!=0; i--)
		print_stars(i);
	return 0;
}


