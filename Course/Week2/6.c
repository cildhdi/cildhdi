#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true (1)
#define false (0)
bool is_not_triangle(double x, double y, double z)
{
	return !((x + y > z) && (x + z > y) && (y + z > x));
}
bool is_equilateral_triangle(double x, double y, double z)
{
	return (x == y) && (y == z);
}
bool is_isosceles_triangle(double x, double y, double z)
{
	return ((x == y) /*&& (z != x)*/) || ((x == z) /*&& (y != x)*/) || ((y == z) /*&& (x != y)*/);
}
bool is_right_triangle(double x, double y, double z)
{
	return ((x * x + y * y) == z * z) || ((x * x + z * z) == y * y) || ((z * z + y * y) == x * x);
}
int main()
{
	double a, b, c;
	scanf("%lf%lf%lf", &a, &b, &c);
	if (is_not_triangle(a, b, c))
		printf("not triangle");
	else if (is_equilateral_triangle(a, b, c))
		printf("equilateral triangle");
	else if (is_isosceles_triangle(a, b, c))
		printf("isosceles triangle");
	else if (is_right_triangle(a, b, c))
		printf("right triangle");
	else
		printf("arbitrary triangle");
	system("pause");
	return 0;
}





