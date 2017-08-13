# include "stdlib.h"         // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"        // 该文件包含标准输入输出流cout和cin以及setw()等
typedef struct                          // 多项式的项作为LinkList的数据对象
{ float coef;                           // 系数
  int exp;                              // 指数
}ElemType;   
bool operator==(const ElemType &e1,const ElemType &e2) // 重载运算符"=="
{
	 return e1.exp==e2.exp;
}

bool operator!=(const ElemType &e1,const ElemType &e2)  // 重载等于运算符
{
	 return e1.exp!=e2.exp;
} 

bool operator>(const ElemType &e1,const ElemType &e2)  // 重载小于运算符
{
	 return e1.exp>e2.exp;
}

ostream& operator<<(ostream& ostr,const ElemType &x)   
    // 重载插入运算符，ostream是C++的通用输出流类
{
	 ostr<<x.coef<<' '<<x.exp<<' ';
     return ostr;
}

# include "LinkList.h"

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
{       // 以ab和bh为头指针的单链表分别表示多项式A(x)和B(x)
// 以ch为头指针的单链表表示A(x)和B(x)和的多项式C(x) 
LinkList pa, pb, pc;
      float x;
      pa=ah->next; pb=bh->next;              // pa和pb分别指向链表开始结点
      ch=(LNode *)malloc(sizeof(LNode));      // 创建头结点
      pc=ch;
      while(pa&&pb)                            // pa和pb非空
      { 
if(pa->data>pb->data)              // 结点pa的指数大于结点pb的指数
{  attach(pa->data.coef, pa->data.exp,pc);  // 结点pa复制到ch中
             pa=pa->next; 
}
else if(pa->data==pb->data)     // 结点pa的指数等于结点pb的指数
 { x=pa->data.coef+pb->data.coef;
                if(x!=0)                   // 指数和不为0
  attach(x,pa->data.exp,pc);  // 以指数和产生新结点，插入到ch中
                pa=pa->next;
                pb=pb->next;
               }
            else  
			{ attach(pb->data.coef, pb->data.exp,pc); // 结点pa的指数小于结点pb的指数
              pb=pb->next;                             // 结点pb复制到ch中
            }
        }
       while(pb)                                    // pb非空
       { attach(pb->data.coef, pb->data.exp,pc);   // 把bh中剩余结点复制到ch中去
         pb=pb->next;
        }
       while(pa)                                    // pa非空
        { attach(pa->data.coef,pa->data.exp,pc);     // 把ah中剩余结点复制到ch中去
          pa=pa->next;
}
pc->next=NULL;      // 是ch链表最后一个结点的指针域为空 
}// polyadd


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