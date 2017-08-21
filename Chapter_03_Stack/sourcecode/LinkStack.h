# include "LinkList.h"
typedef LinkList LinkStack;             // 链栈的结点结构和单链表相同
void InitStack_L(LinkStack &S)
 {  
   S=NULL;  
  }// InitStack_L

int StackLength_L(LinkStack S)
{
  int k=0;
  LinkStack p=S;
	while(p)
    { k++;
      p=p->next;                            // 访问下一个结点。
    }
   return k;
}// StackLength_L

bool Push_L( LinkStack &S, ElemType e) 
{      //在链栈的栈顶插入元素e
      LinkStack p;
      if((p=(LNode *)malloc(sizeof(LNode)))==NULL) return false;  // 存储分配失败
      p->data=e;  
      p->next=S;                      // 插入新的栈顶元素
      S=p;                            // 修改栈顶指针
      return true;
     }// Push_L

bool Pop_L( LinkStack &S, ElemType &e) 
{     // 删除链栈栈顶元素，并让e返回其值
LinkStack p;
   if(S)                          // 栈非空
	  { p=S;S=S->next;            // 修改栈顶指针
	    e=p->data;                // 元素e返回其值
	    free(p);                  // 释放结点空间
	    return true; 
   }
   else return false;            // 栈空，出栈失败
 }// Pop_L

bool GetTop_L(LinkStack S,ElemType &e)
{    
  if(S)                    // 栈非空
	  { e=S->data;           // 元素e返回其值
	    return true;  
 }
   else return false;      // 栈空，取栈顶元素失败
 }// GetTop_L
 
bool StackEmpty_L(LinkStack S)
{
 if(!S) return true;
 else return false;
}// StackEmpty_L

void DestroyStack_L(LinkStack &S )
{
  LinkStack p,p1;
  p=S;
  while(p) 
  { p1=p;
    p=p->next;
    free(p1);                                // 释放p1所指的空间
   }
   S=NULL;                                    // S置空
 }// DestroyStack_L
