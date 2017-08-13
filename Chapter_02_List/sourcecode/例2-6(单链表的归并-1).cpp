
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
void MergeList_L(NK La, NK Lb, NK &Lc) 
{
 // 归并两个带头结点非递减有序的单链表La和lb成为一个带头结点非递减有序的单链表Lc
   NK pa,pb,pc;   
   Lc=(SLNode *)malloc(LEN);           // 创建一个空的单链表Lc
   pa=La->next; pb=Lb->next;               // pa和pb分别指向La和Lb的开始结点
   pc=Lc;                                  // pc指向Lc的头结点
 while(pa&&pb)                           // La和Lb均非空
 if(pa->data<=pb->data)                  // 两表中当前元素比较
{ pc->next=pa;pa=pa->next;pc=pc->next; }  // pa所指结点插入到Lc中
else 
{ pc->next=pb;pb=pb->next;pc=pc->next; }  // pb所指结点插入到Lc中
if(pa) pc->next=pa;                         // 链接La中的剩余结点
if(pb) pc->next=pb;                         // 链接Lb中的剩余结点
free(La);   free(Lb);                       // 释放La和lb的头结点
}
 

void creat(NK &head)
{ SLNode *p,*q;
  DataType a;
  head=(SLNode *)malloc(LEN);
  q=p=head;
  scanf("%d",&a);
  while(a!=0)
  {
   p=(SLNode *)malloc(LEN);
   p->data=a;
   q->next=p;
   q=p;
    scanf("%d",&a);
   }
   q->next=NULL;
 }

 void print(SLNode *head)
  {
	 head=head->next;
    while(head!=NULL)
    {
      printf("%4d",head->data);
      head=head->next;
    }
  }
void main()
 { SLNode *ha,*hb,*hc;
  creat(ha);
  print(ha); printf("\n");
  creat(hb);
  print(hb); printf("\n");
 MergeList_L(ha,hb,hc) ;
   print(hc); printf("\n");
  getchar();
  getchar();
  }