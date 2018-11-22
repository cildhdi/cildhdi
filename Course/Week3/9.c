#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
int gcd(int a, int b)
{
	return b > 0 ? gcd(b, a%b) : a;
}
int main()
{
	int num1 = 0, num2 = 0;
	scanf("%d%d", &num1, &num2);
	printf("The greatest common divisor:%d\n", gcd(num1, num2));
	unsigned int i = 1;
	while (1)
	{
		if (((i*(num1 > num2 ? num1 : num2)) % (num1 < num2 ? num1 : num2) == 0))
		{
			printf("The lowest common multiple:%d", i*(num1 > num2 ? num1 : num2));
			break;
		}
		i++;
	}
	return 0;
}
