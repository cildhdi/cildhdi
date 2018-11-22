#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int num[4] = { 0 };
	printf("Enter a number: ");
	int i = 0;
	for (i = 0; i < 4; i++)
	{
		int k;
		scanf("%1d", &k);
		num[i] = (k + 9) % 10;
	}
	printf("The encrypted number is %d%d%d%d", num[2], num[3], num[0], num[1]);
	system("pause");
	return 0;
}

// int main()
// {
// 	char str[256] = { 0 };
// 	scanf("%s", str);
// 	size_t length = strlen(str);
// 	int pos1 = -1, pos2 = -1;
// 	for (unsigned int i = 0; i < length; i++)
// 	{
// 		if (str[i] >= 'A'&&str[i] <= 'Z')
// 		{
// 			if (pos1 == -1)
// 			{
// 				pos1 = i;
// 				continue;
// 			}
// 			if (pos2 == -1)
// 			{
// 				pos2 = i;
// 				break;
// 			}
// 		}
// 	}
// 
// 	char str1[256] = { 0 }, str2[256] = { 0 };
// 	for (unsigned int i = pos1; i < pos2; i++)
// 		str1[i] = str[i];
// 	for (unsigned int i = pos2; i < length; i++)
// 		str2[i - pos2] = str[i];
// 	printf(str); printf("\n");
// 	printf(str1); printf("\n");
// 	printf(str2); printf("\n");
// 	str1[1] = '\0';
// 	str2[1] = '\0';
// 	printf(str1); printf(".");
// 	printf(str2); printf(".");
// 	system("pause");
// 	return 0;
// }

