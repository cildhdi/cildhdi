
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	unsigned int num = 0;
	scanf("%d", &num);
	switch (num)
	{
	case 0:
	case 1:
	case 4:
		printf("NO");
		break;
	case 2:
		printf("YES");
		break;
	default:
	{
		int i = 0;
		for (i = 3; i < sqrt(num); i++)
		{
			if (num%i == 0)
			{
				printf("NO");
				return 0;
			}
		}
		printf("YES");
	}
	break;
	}
	return 0;
}

