#include <stdio.h>
#include <stdlib.h>


int main()
{
	int n,i,j,num;
	scanf("%d",&n);
	if(1==n)
	{
		printf("NO");
		return 0;
	}
	for(i=0; i<n; i++)
		for(j=0; j<n; j++)
		{
			scanf("%d",&num);
			if(i+j>2*j&&num!=0)
			{
				printf("NO");
				return 0;
			}
		}
	printf("YES");
	return 0;
}

