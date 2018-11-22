#include "stdio.h"

#include "stdlib.h"

typedef struct node
{
	int n;
	struct node* next;
} NODE;
int IsPrime(int n) /*�ж�����n�ǲ�������*/
{
	int i;
	if(n<2)  return 0;
	for(i=2;i<n;i++)
		if(n%i==0) return 0;
	return 1;
}
NODE* create() /*������10���������ɵ�����*/
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
NODE* del(NODE* head) /*ɾ������������*/
{
	NODE *p,*q;
	if(head==NULL) return NULL;
	for(p=head,q=p->next;q!=NULL;q=p->next)
	{   /* ɾ���ӵ�2����㿪ʼ�����������������Ľ��*/
		if(IsPrime(q->n))
		{
			p->next=q->next;
			free(q);
		}
		else
			p=   p->next  ;
	}
	if(IsPrime(head->n)) /*����ͷ����������������������*/
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

