#include "stdio.h"

#include "stdlib.h"

typedef struct node
{
	int n;
	struct node* next;
} NODE;
int IsPrime(int n) /*判断整数n是不是素数*/
{
	int i;
	if(n<2)  return 0;
	for(i=2;i<n;i++)
		if(n%i==0) return 0;
	return 1;
}
NODE* create() /*创建由10个整数构成的链表*/
{
	int i;
	NODE *head=NULL,*p;
	for(i=0;i<10;i++)
	{
		p= (NODE*)malloc(sizeof(NODE));   ;
		scanf("%d",&p->n);
		p->next=head;
		head=p;
	}
	return head;
}
NODE* del(NODE* head) /*删除所有素数点*/
{
	NODE *p,*q;
	if(head==NULL) return NULL;
	for(p=head,q=p->next;q!=NULL;q=p->next)
	{   /* 删除从第2个结点开始的整数部分是素数的结点*/
		if(IsPrime(q->n))
		{
			p->next=q->next;
			free(q);
		}
		else
			p=   p->next  ;
	}
	if(IsPrime(head->n)) /*处理头结点整数部分是素数的情况*/
	{
		p=     head->next  ;
		free(head);
		head=p;
	}
	return head;
}
void print(NODE* head)
{
	NODE* p=head;
	if(p==NULL) printf(" nothing");
	while(p!=NULL)
	{
		printf("%d ",p->n);
		p=p->next;
	}
}
int main()
{
	NODE* head;
	head=create();
	printf("Source list: ");
	print(head);
	printf("\n");
	head=del(head);
	printf("After deleted: ");
	print(head);
	printf("\n");
	return 0;
}

