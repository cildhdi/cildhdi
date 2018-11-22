#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num = 0;
	int odd_count = 0, even_count = 0;
	double odd_sum = 0, even_sum = 0;
	while (1)
	{
		scanf("%d", &num);
		if (num == 0)break;
		if (num % 2 == 0)
		{
			even_sum += num;
			even_count++;
		}
		else
		{
			odd_sum += num;
			odd_count++;
		}
	}
	printf("%d %.2lf\n", odd_count, odd_count ? odd_sum / odd_count : 0);
	printf("%d %.2lf", even_count, even_count ? even_sum / even_count : 0);
	//system("pause");
	return 0;
}
