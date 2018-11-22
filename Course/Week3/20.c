#include <stdio.h>
double rec(int n)
{
	if(n==1)return 1;
	return n*rec(n-1);
}
int main()
{
	int i=1;
	double e=1,an=0;
	while(1)
	{
		an=1/rec(i);
		if(an<1E-6)break;
		e+=an;
		i++;
	}
	printf("%lf",e);
	return 0;
}





