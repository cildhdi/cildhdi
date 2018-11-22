#include <stdio.h>
#include <stdlib.h>

struct node
{
	int num;           /*ѧ����ѧ��*/
	struct node *next; /*ָ����һ���*/
};
struct node *find(struct node *head,int num)
{
	/*�����headΪ�������򷵻ؿ�ָ�롣�������һ������ѧ�Ų�С��num��Ҳ���ؿ�ָ�롣��������һ������ѧ����С��num���򷵻����һ�����ָ�롣�������ǰ����ѧ��С��num����һ���ѧ�Ų�С��num���򷵻ص�ǰ����ָ��*/
	struct node *p, *q;
	if(head==NULL || head->num>=num)
		return NULL;/*headΪ������ʱ���һ������ѧ�Ų�С��numʱ���ؿ�ָ��*/
	for ( p=head; p!=NULL; p=p->next )
	{
		q = p->next;
		if ((p->next==NULL&&p->num<num)||(p->num<num&&q->num>=num) ) /*����*/
			return p;
	}
	return NULL;
}

struct node *insert(struct node *head,int num)
{
	/*��ѧ��˳������½�㣬�½���ѧ��Ϊnum*/
	struct node *p, *q;
	p = (struct node *)malloc(sizeof(struct node)) ;/*�����ڴ�ռ�*/
	p->num = num;
	q = find(head,num);/*�ҵ�����λ����p�ĺ���*/
	if (q==NULL)
	{
		/*���뵽����ͷ*/
		p->next = head;
		return p;
	}
	p->next=q->next       ;/*���뵽q�ĺ���*/
	q->next = p;
	return head;
}

int main()
{
	struct node *head=NULL, *p;
	int  i, num;
	for ( i=0; i<5; i++ )
	{
		scanf( "%d", &num );
		head=insert(head,num);
	}
	for ( p=head; p!=NULL; p=p->next )
		printf( "%d ", p->num );
	printf("\n");
	return 0;
}

