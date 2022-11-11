#include<stdio.h>
#include<stdlib.h>

/*下面程序的功能是把一个 int 型数组的各元素作为一个结点插入到一个链表中去。
如果待插入到链表中的数组元素为奇数，按该数组元素生成的的结点总是被插入到链表的表头；
如果待插入到链表中的数组元素为偶数，按该数组元素生成的结点总是被插入到链表的表尾。
程序填空，请在(1),(2),(3),(4),(5)处填入正确答案，以获得正确结果。
*/

#include<stdio.h>
#include<stdlib.h>
typedef struct node{
 int data;
 struct node *next;
}NODE;
void insert(NODE **head , int n)
{		
	 int i;
	 NODE *p,*p1=*head;
	 p=(NODE*)malloc(sizeof(NODE)) ;
	 if(!p)exit(1);
	 p->data=n;
	 p->next=0;

	if(!p1)
	   *head=p;//填空1
	else{
	   if(p->data%2!=0){
	      p->next=*head;
	      *head=p;//填空2
	   }else{
          while(p1->next)
            p1=p1->next;
          p1->next=p;//填空3
       }
    }
}
int main( )
{
	NODE *head=NULL,*p;
	int i,num[10]={3,7,10,12,8,45,12,31,99,20};

	 for(i=0;i<10;i++)
	    insert((NODE **)&head, num[i] );//填空4
	p=head;
	while(p){
	 printf("%5d",p->data);
		 p= p->next;//填空5
	}
}

