typedef int ElemType;      // 单链表中元素类型为int
# include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"      // 该文件包含标准输入输出流cout和cin及控制符setw()
# include "LinkList.h"     // 该文件中包含单链表数据对象的描述及相关操作

void MergeList_L(LinkList La, LinkList Lb, LinkList &Lc) 
{     // 归并两个带头结点非递减有序的单链表La和lb
// 成为一个带头结点非递减有序的单链表Lc
       LinkList pa,pb,pc;   
       Lc=(LNode *)malloc(sizeof(LNode));      // 创建一个空的单链表Lc
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
}// MergeList_L

void main()
 { 
      LNode *ha,*hb,*hc;
      ElemType a[]={2,6,9,13,45};
      ElemType b[]={1,6,19,25,45,60};
      CreateList_L_Rear(ha,a,5);               // 创建单链表ha
      cout<<"单链表ha：";
      ListTraverse_L(ha);                      // 显示单链表ha
      CreateList_L_Rear(hb,b,6);               // 创建单链表hb
      cout<<"单链表hb：";
      ListTraverse_L(hb);                       // 显示单链表hb
      MergeList_L(ha,hb,hc);                    // 归并ha和hb为hc
      cout<<"归并后的单链表hc：";
      ListTraverse_L(hc);                       // 显示单链表hc
 }
