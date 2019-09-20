typedef  int ElemType;
# include "stdlib.h"     
# include "iostream.h"   
# include "iomanip.h"     
# include "LinkList.h"

bool reverseLinkList(LinkList &head)
{
   LinkList p,q;
   p= head->next;
   head->next= NULL;
   
   while(p)
   {
     q=p;
     p=p->next;
     q->next = head->next;
     head->next = q;
   }
}

void reverseLinkList2(LinkList &head)
{
 LinkList p,q;
 p = q = head->next;
 ElemType e;
 
 while(p->next)
 {
   p=p->next;
   e=p->data;
   ListInsert_L(head,1,e);
 }
 q->next= NULL;
}

int  main()
{
      LinkList mylist;
      int i,j,temp,forLocate,forGet,forInsert,forDelete,a[]={6,8,16,2,34,56,7,10,22,45};
      InitList_L(mylist);   
      cout<<"我初始化了一个头结点。"<<endl;
      CreateList_L_Front(mylist,a,10);          
      cout<<"我创建了一个带头结点的单链表，表长为："<<ListLength_L(mylist)<<endl;
      cout<<endl<<"表中的元素依次为："<<endl;
      ListTraverse_L(mylist);
      
	  cout<<endl<<"逆序后的链表元素依次为"<<endl;
      if(reverseLinkList(mylist))
      ListTraverse_L(mylist);
      
      reverseLinkList2(mylist);
      ListTraverse_L(mylist);
}

