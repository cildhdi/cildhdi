#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	unsigned int i,j,mr;
	for(i=1; i<1001; i++)
	{
		mr=0;
		for(j=1; j<i; j++)
		{
			if(i%j==0)
				mr+=j;
		}
		if(i==mr)printf("%d ",i);
	}
	return 0;
}




