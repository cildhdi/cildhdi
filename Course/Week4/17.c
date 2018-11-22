#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main()
{
	char c,num[80];
	int i=0;
	while((c=getchar())!='\n')
	{
		if((c>='0'&&c<='9')||(c>='a'&&c<='f')||(c>='A'&&c<='F'))
		{
			num[i]=c;
			i++;
		}
	}
	unsigned int len=strlen(num),digit=0,sum=0;
	for(i=len-1; i>=0; i--)
	{
		c=num[i];
		if(c>='0'&&c<='9')
		{
			digit=c-'0';
		}
		else if(c>='a'&&c<='f')
		{
			digit=c-'a'+10;
		}
		else if(c>='A'&&c<='F')
		{
			digit=c-'A'+10;
		}
		sum+=(pow(16,len-i-1)*digit);
	}
	printf("%s\n%d",num,sum);
	return 0;
}

