#include <stdlib.h>
#include <stdio.h>

unsigned int gcd(unsigned int a, unsigned int b)
{
	return b > 0 ? gcd(b, a%b) : a;
}

struct fraction
{
	int numerator;
	int denominator;
};

struct fraction add(struct fraction a, struct fraction b)
{
	struct fraction result = { 0,0 };
	a.numerator *= b.denominator;
	b.numerator *= a.denominator;
	result.denominator = a.denominator*b.denominator;
	result.numerator = a.numerator + b.numerator;
	unsigned int div = gcd(result.numerator, result.denominator);
	result.numerator /= div;
	result.denominator /= div;
	return result;
}

int main()
{
	struct fraction a, b, ret;
	printf("please enter the fenzi,fenmu of two complex:\n");
	scanf("%d %d %d %d", &a.numerator, &a.denominator, &b.numerator, &b.denominator);
	ret = add(a, b);
	printf("the result is %d/%d", ret.numerator, ret.denominator);
	return 0;
}


