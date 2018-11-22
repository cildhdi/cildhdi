#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int n, i, score, sum = 0, scores[20] = { 0 };
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		scanf("%d", &score);
		sum += score;
		scores[i] = score;
	}
	double kill = sum / (double)n;
	printf("%.2lf\n", kill);
	for (i = 0; i < n; i++)
	{
		if (scores[i] < kill)
		{
			printf("%d ", scores[i]);
		}
	}
	system("pause");
	return 0;
}

































// 	if ((a + b > c) && (b + c > a) && (a + c > b))
// 	{
// 		printf();
// 	}
// 	else
// 	{
// 		printf();
// 	}

