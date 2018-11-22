#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i,j,num,Matrix[3][3]=
	{
		{68,55,28},
		{36,45,17},
		{77,16,24}
	};
	scanf("%d",&num);
	for(i=0; i<3; i++)
		for(j=0; j<3; j++)
		{
			if(Matrix[i][j]==num)
			{
				printf("[%d,%d]",i+1,j+1);
				return 0;
			}
		}
	printf("[N]");
	return 0;
}


