//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int num1 = 0, num2 = 0;
	printf("Enter num1:");
	scanf("%d", &num1);
	printf("Enter num2:");
	scanf("%d", &num2);
	printf("%d+%d=%d\n", num1, num2, num1 + num2);
	printf("%d-%d=%d\n", num1, num2, num1 - num2);
	printf("%d*%d=%d\n", num1, num2, num1 * num2);
	printf("%d/%d=%d\n", num1, num2, num1 / num2);
	printf("%d%%%d=%d\n", num1, num2, num1 % num2);
	//system("pause");
	return 0;
}

