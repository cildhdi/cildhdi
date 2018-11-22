#include<stdio.h>

int main()
{
	char szNum[3];
	scanf("%s",szNum);
	unsigned int i =3;
	for(; i!=0; i--)
		printf("%c ",szNum[i-1]);
	return 0;
}


