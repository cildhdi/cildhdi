#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int pred_better(const void * ln, const void * rn)
{
	return (*(int*)ln - *(int*)rn) > 0 ? 1 : 0;
}
void merge_sort(int* ns1, unsigned int size1, int* ns2, unsigned int size2, int* dst)
{
	assert((ns1 != 0) && (ns2 != 0) && (dst != 0));
	memcpy(dst, ns1, size1 * sizeof(int));
	memcpy(dst + size1, ns2, size2 * sizeof(int));
	qsort(dst, size1 + size2, sizeof(int), pred_better);
}
int main()
{
	unsigned int n = 0, m = 0, i = 0;
	printf("Enter n: ");
	scanf("%d", &n);
	int* ns1 = malloc(sizeof(int)*n);
	printf("Enter %d integers: ", n);
	for (i = 0; i < n; i++)
		scanf("%d", ns1 + i);
	printf("Enter m: ");
	scanf("%d", &m);
	int* ns2 = malloc(sizeof(int)*m);
	printf("Enter %d integers: ", m);
	for (i = 0; i < m; i++)
		scanf("%d", ns2 + i);
	int* result = malloc((m + n) * sizeof(int));
	merge_sort(ns1, n, ns2, m, result);
	for (i = 0; i < m + n; i++)
		printf("%4d", *(result + i));
	free(ns1);
	free(ns2);
	free(result);
	return 0;
}

