#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int match(int num)
{
	if(num % 5 != 0)
		return 0;
	char sz[5] = {0};
	sprintf(sz, "%d", num);
	unsigned int len = strlen(sz), i, sum = 0;
	for(i = 0; i < len; i++)
	{
		sum += (sz[i] - '0');
	}
	if(sum == 5)
		return 1;
	return 0;
}

int main()
{
	int a, b, i, sum = 0;
	scanf("%d %d",&a, &b);
	for(i = a + 1; i < b; i++)
	{
		if(match(i))
		{
			sum += i;
		}
	}
	printf("%d", sum);
	return 0;
}



