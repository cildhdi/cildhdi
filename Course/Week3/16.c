#include <stdio.h>

int main()
{
	int i, j, x;
	for (j = 4; j >= 1; j--)
	{
		for (i = 1; i <= 4; i++)
		{
			x = (j - 1) * 4 + i;
			printf("%d",x);
			if (i==4)
				printf("\n");
			else
				printf(" ");
		}
	}
	return 0;

}




