#include <stdio.h>
#include <stdlib.h>

struct node
{
	int num;           /*学生的学号*/
	struct node *next; /*指向下一结点*/
};
struct node *find(struct node *head,int num)
{
	/*①如果head为空链表，则返回空指针。②如果第一个结点的学号不小于num，也返回空指针。③如果最后一个结点的学号仍小于num，则返回最后一个结点指针。④如果当前结点的学号小于num且下一结点学号不小于num，则返回当前结点的指针*/
	struct node *p, *q;
	if(head==NULL || head->num>=num)
		return NULL;/*head为空链表时或第一个结点的学号不小于num时返回空指针*/
	for ( p=head; p!=NULL; p=p->next )
	{
		q = p->next;
		if ((p->next==NULL&&p->num<num)||(p->num<num&&q->num>=num) ) /*条件*/
			return p;
	}
	return NULL;
}

struct node *insert(struct node *head,int num)
{
	/*按学号顺序插入新结点，新结点的学号为num*/
	struct node *p, *q;
	p = (struct node *)malloc(sizeof(struct node)) ;/*分配内存空间*/
	p->num = num;
	q = find(head,num);/*找到插入位置在p的后面*/
	if (q==NULL)
	{
		/*插入到链表头*/
		p->next = head;
		return p;
	}
	p->next=q->next       ;/*插入到q的后面*/
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

