#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int get_minutes()
{
	char szTime[4]={0};
	int hours=0,minutes=0;
	scanf("%s",szTime);
	if(strlen(szTime)==3)
	{
		minutes=atoi(szTime+1);
		szTime[1]='\0';
		hours=atoi(szTime);
	}
	else
	{
		minutes=atoi(szTime+2);
		szTime[2]='\0';
		hours=atoi(szTime);
	}
	return hours*60+minutes;
}
int main()
{
	int time1=0,time2=0;
	printf("Enter time1:");
	time1=get_minutes();
	printf("Enter time2:");
	time2=get_minutes();
	int time=time2-time1;
	printf("The train journey time is %d hours %d minutes",(time-time%60)/60,time%60);
	system("PAUSE");	
	return 0;
}

