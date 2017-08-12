# include "stdlib.h"
# include "iostream.h"
# include "iomanip.h"
typedef struct                          // 多项式的项作为LinkList的数据对象
{ float coef;                           // 系数
  int exp;                              // 指数
}ElemType;   
# include "LinkList(多项式相加).h"

void attach (float c, int e, LinkList &pc)
{
// 建立系数为c，指数为e的新结点，并把它插在pc所指结点的后面
// 链接后pc指向新链入的结点 
 LinkList p;
  p=(LNode *)malloc(sizeof(LNode));
  p->data.coef=c;
  p->data.exp=e;
  pc->next=p;
  pc=p;
}
void polyadd( LinkList ah, LinkList bh, LinkList &ch)
{
// 以ab和bh为头指针的单链表分别表示多项式A(x)和B(x),以ch为头指针的单链表
//表示A(x)和B(x)和的多项式C(x)。为便于计算，本算法不破坏A(x)与B(x)，C(x)另辟空间 
 LinkList pa, pb, pc;
  float x;
  pa=ah->next; pb=bh->next;
  ch=(LNode *)malloc(sizeof(LNode));
  pc=ch;
  while (pa&&pb)
  { 
if (pa->data.exp>pb->data.exp) {attach (pa->data.coef, pa->data.exp,pc);
                               pa=pa->next; }
else if(pa->data.exp==pb->data.exp) { x=pa->data.coef+pb->data.coef;
                            if(x!=0) attach(x,pa->data.exp,pc); 
                            pa=pa->next;
                            pb=pb->next;
                          }
       else  { attach (pb->data.coef, pb->data.exp,pc);
               pb=pb->next;
             }
  }
   while(pb)
   { attach(pb->data.coef, pb->data.exp,pc);
     pb=pb->next;
   }
 while(pa)
    { attach(pa->data.coef,pa->data.exp,pc);
      pa=pa->next;
}
pc->next=NULL;      // 是ch链表最后一个结点的指针域为空 
}

void main()
{
  LinkList A,B,C;
  ElemType a[]={{3,14},{2,8},{1,0}};
  ElemType b[]={{8,14},{-3,10},{10,6}};
  CreateList_L_Rear(A,a,3);
  cout<<"多项式A：";
  ListTraverse_L(A);
  CreateList_L_Rear(B,b,3);
  cout<<"多项式B：";
  ListTraverse_L(B);
  polyadd(A,B,C);
  cout<<"多项式相加的结果C：";
  ListTraverse_L(C);
}
