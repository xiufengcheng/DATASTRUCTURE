typedef int ElemType;     
#include  "stdlib.h"      
#include  "iomanip.h"     
#include  "LinkList.h"    




//已知非空单链表第一个结点由head指出，请写一算法，交换p所指结点与其下一个结点在链表中的位置
void Reverse(LinkList &L, LinkList p)
{
 LinkList q,r;
 q = L;
 r = p->next;
 while(q->next!=NULL&&q->next->data!=p->data)
 q = q->next;    //这样q指向了p之前的一个节点
  
 if(r)
	{
	  q->next = p->next;
	  p->next = r->next;
	  r->next = p;
	     
	} 
 
}


//设有头结点的单链表，编程对表中的一值（5）只保留一个结点，删除其余值相同的结点。
void  Choice_L(LinkList &L)
{
 ElemType e;
 LinkList p,q;
 p=L;
 int i=0;
 while(p->next)
 { 
   p = p->next;i++;
   if(p->data = 5)
   		{
         q=p->next;                               
		 p->next=q->next;                              
	     e=q->data;    free(q);
   
 }
}



int main()
{
 LinkList linklist,p;
 InitList_L(linklist);
 ElemType a[]={1,2,3,4,5,5,6};
 CreateList_L_Rear(linklist,a,7);
 
 cout<<"之前："<<endl;
 ListTraverse_L(linklist);
 p=linklist->next->next;
 
 //Reverse_L(linklist,p);
 Choice_L(linklist);
 
 cout<<"之后："<<endl;
 ListTraverse_L(linklist);
 
 
 
}

