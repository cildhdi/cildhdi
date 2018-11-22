#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num,i,j,scores[10][7]= {{0}};
	for(i=0; i<10; i++)scanf("%d",&num);
	for(i=0; i<10; i++)
	{
		for(j=0; j<6; j++)
		{
			scanf("%d",&scores[i][j]);
			scores[i][6]+=scores[i][j];
		}
	}
	for(i=0; i<10; i++)
	{
		if(scores[i][6]>=530)
		{
			printf("[%d,%d]\n",i+1,scores[i][6]);
		}
	}
	return 0;
}

