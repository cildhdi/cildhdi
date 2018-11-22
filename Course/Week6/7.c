#include <stdio.h>
#include <stdlib.h>
struct info
{
	char name[10];
	int age;
	char tele[16];
};
int info_cmp(const void* l, const void* r)
{
	return (*(struct info*)l).age > (*(struct info*)r).age ? 1 : 0;
}
int main()
{
	unsigned int n = 0, i;
	printf("Input n:");
	scanf("%d", &n);
	struct info* infos = calloc(n, sizeof(struct info));
	for (i = 0; i < n; i++)
	{
		printf("Input the name,age,telephone of the %d friend:", i + 1);
		scanf("%s%d%s", (char*)&(*(infos + i)).name, &(*(infos + i)).age, (char*)&(*(infos + i)).tele);
	}
	qsort(infos, n, sizeof(struct info), info_cmp);
	printf("after sorted:\n");
	for (i = 0; i < n; i++)
		printf("%s %d %s\n", (*(infos + i)).name, (*(infos + i)).age, (*(infos + i)).tele);
	return 0;
}


