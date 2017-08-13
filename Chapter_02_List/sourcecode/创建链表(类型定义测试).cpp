 # include "stdio.h"
# include "stdlib.h"
# include "malloc.h"
# define LEN sizeof(SLNode)
typedef  int DataType;
 typedef struct SLNode
    {
     DataType data;
     struct SLNode *next;
     }SLNode,*NK;
/* 通过参数 */

void creat(NK *head)
{ SLNode *p,*q;
  *head=(SLNode *)malloc(LEN);
  q=p=*head;
  scanf("%d",&p->data);
  while(p->data!=0)
  {
   p=(SLNode *)malloc(LEN);
   scanf("%d",&p->data);
   q->next=p;
   q=p;
   }
   q->next=NULL;
 }

 void print(SLNode *head)
  {
    while(head!=NULL)
    {
      printf("%4d",head->data);
      head=head->next;
    }
  }
void main()
 { SLNode *h;
  creat(&h);
  print(h);
  getchar();
  getchar();
  }

