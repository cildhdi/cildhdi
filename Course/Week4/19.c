#include <stdio.h>
#include <stdlib.h>


int main()
{
	int i,j,num,sum=0;
	for(i=0; i<4; i++)
		for(j=0; j<4; j++)
		{
			scanf("%d",&num);
			if(i==j)
			{
				sum+=num;
			}
		}
	printf("%d",sum);
	return 0;
}


