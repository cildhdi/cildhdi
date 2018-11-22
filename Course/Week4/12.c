#include <stdio.h>
#include <stdlib.h>

int main()
{
	double nums[12],sum=0;
	int i,per;
	for(i=0; i<12; i++)
	{
		scanf("%lf",nums+i);
		sum+=nums[i];
	}
	for(i=0; i<12; i++)
	{
		per=100*nums[i]/sum+0.5;
		printf("%2d(%d%%)",i+1,per);
		while(per!=0)
		{
			printf("#");
			per--;
		}
		printf("\n");
	}
	return 0;
}

