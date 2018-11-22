#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int num = 0;
	scanf("%d", &num);
	if (num == 0)
	{
		printf("not within the scope of judgment");
		return 0;
	}
	if (num > 0)
		printf("positive ");
	else
		printf("negative ");

	if (num % 2 == 0)
		printf("even ");
	else
		printf("odd ");

	printf("number");

	//system("pause");
	return 0;
}
