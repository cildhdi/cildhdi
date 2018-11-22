#include<stdio.h>
int get_score(char* szSubject)
{
	printf(szSubject);
	printf("=");
	int score=0;
	scanf("%d",&score);
	return score;
}

int main()
{
	double aver=(double)(get_score("math")+get_score("eng")+get_score("comp"))/3;
	printf("average=%.2f",aver);
	return 0;
}


