#include <stdio.h>
#include <math.h>

void ps(unsigned int i,char ch)
{
	while(i!=0)
	{
		putchar(ch);
		i--;
	}
	if(ch!=' ')printf("\n");
}

int main()
{
	int n;
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			for(n=1; n<=5; n+=2)ps(n,'*');
			break;
		case 2:
			for(n=5; n>0; n-=2)ps(n,'*');
			break;
		case 3:
			for(n=1; n<=5; n+=2)ps(n,'*');
			ps(3,'*');
			ps(1,'*');
			break;
		case 4:
			//傻得我自己都害怕
			ps(2,' ');
			ps(1,'*');
			ps(1,' ');
			ps(3,'*');
			ps(5,'*');
			ps(1,' ');
			ps(3,'*');
			ps(2,' ');
			ps(1,'*');
			break;
	}
	return 0;
}




