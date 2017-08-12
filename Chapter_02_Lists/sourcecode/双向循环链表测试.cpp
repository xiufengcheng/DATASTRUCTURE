# include "stdio.h"
# include "stdlib.h"
typedef int ElemType;
typedef struct DuNode  {
 ElemType data;
struct  DuNode *prior;
struct  DuNode *next;
}DuLNode,*DuLinkList;

void InitList_DuL(DuLinkList &L)
    {  
L=(DuLNode *)malloc(sizeof(DuLNode));    // 申请存放一个结点数据所需要的内在空间
if(!L)   exit(1);                        // 存储分配失败
L->next=L;                               // 表头结点作为表头结点的后继
L->prior=L;                              // 表头结点作为表头结点的前驱
    }

bool ListInsert_DuL(DuLinkList &L,int i,ElemType e) 
    {
       // 在带头结点的双向链表L中第i个结点之前插入元素e
  DuLinkList p,s;
   int j;
   p=L->next;  j=1;
   while(p!=L&&j<i)  { p=p->next; j++; }   // 寻找第i个结点,并让p指向此结点
   if(j!=i)   return false;                   // i的位置不合理
   s=(DuLNode *)malloc(sizeof(DuLNode));
if(!s)   exit(1);                          // 存储分配失败
   s->data=e;  
s->prior=p->prior;                                  // 修改指针
p->prior->next=s;      
s->next=p;
p->prior=s;
return true;
}

bool ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{
           // 删除带有头结点的双向链表L中的第i个结点，并让e返回其值
DuLinkList p;
  int j;
  p=L;  j=0;
 while(p->next!=L&&j<i){ p=p->next; j++; }      // 寻找第i个结点,并让p指向此结点
   if(j!=i)   return false;                    // i的位置不合理
  e=p->data;                                  // 被取元素的值赋给e
    p->prior->next=p->next;                     // 修改指针
    p->next->prior=p->prior;
free(p);                                    // 释放结点p的空间
  return true;
 }

    void main()
     {int a,e;
      DuLinkList head,p,q;
      p=q=head=(DuLNode*)malloc(sizeof(DuLNode));
      scanf("%d",&a);
      while(a!=0)
       {p=(DuLNode*)malloc(sizeof(DuLNode));
        p->data=a;
        p->prior=q;
        q->next=p;
        q=p;
        scanf("%d",&a);}
        q->next=head;
		head->prior=q;
        printf("插入之前的双向链表是:");
        p=head->next;
        while(p!=head)
        {printf("%3d,",p->data);
         p=p->next;}
         printf("\n");
        if(ListInsert_DuL(head,1,7))
		{
			printf("插入成功\n");
			printf("插入之后的双向链表是:");
            p=head->next;
            while(p!=head)
			{printf("%3d,",p->data);
            p=p->next;}
            printf("\n");
		}  
		else printf("插入失败\n");
        
        if(ListDelete_DuL(head,1,e))
		{	
			printf("删除成功\n");
            printf("被删除的元素是：%d\n",e);
           printf("删除之后的双向链表是:");
           p=head->next;
          while(p!=head)
		  {printf("%3d,",p->data);
           p=p->next;}
           printf("\n");
		}
        else printf("删除失败\n");
       }