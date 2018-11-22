#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	int a,b,c;
	printf("Enter 3 sides of the triangle: ");
	scanf("%d%d%d",&a,&b,&c);
	if (a+b>c&&a+c>b&&b+c>a)
	{
		double s=(a+b+c)/2.0;
		printf("area=%-8.2lf;perimeter=%-8.2lf",sqrt(s*(s-a)*(s-b)*(s-c)),s*2);
	}
	else
	{
		printf("These sides do not correspond to a valid triangle");
	}
	return 0;
}

