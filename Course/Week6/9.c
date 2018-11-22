#include <stdio.h>

#include <stdlib.h>

struct node
{
	int n;
	struct node *next;
};

int main( )
{
	struct node  *head=NULL, *tail=NULL, *p;
	int  i, min, s=0, index=1, ct;
	scanf ( "%d", &ct ); /*从键盘输入ct的值,设ct大于1*/
	for ( i=0; i<ct; i++ )
	{
		p =       (struct node*) malloc(sizeof(struct node))     ;/*申请新结点空间*/
		scanf( "%d", &p->n );
		p->next=NULL;
		if ( head==NULL ) head = p;
		else   tail->next=p      ;
		tail = p;
	}
	min = head->n + head->next->n;
	i = 1;
	for ( p=head->next; p!=NULL && p->next!=NULL; p=p->next )
	{
		s =     p->n+p->next->n   ;
		i++;
		if(       s<min    )
		{
			min=s;
			index=i;
		}
	}
	printf( "%d %d", index, index+1 );
	return 0;
}


