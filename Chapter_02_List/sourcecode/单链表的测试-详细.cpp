# include "stdlib.h"
# include "iostream.h"
# include "iomanip.h"
typedef  int ElemType;
# include "LinkList.h"
  void  main()
     {
      LinkList head;
      int i,x,k,a[]={10,20,30,40,50,60,70,80,90,100};
      InitList_L(head);   //初始化
       
        CreateList_L_Front(head,a,10 );          //创建链表
		k=ListLength_L(head);
		cout<<"表长="<<k<<endl;
		if(GetElem_L(head,12,x)) 
	     cout<<"x="<<x<<endl;
		else cout<<"元素不存在"<<endl;
      if(!ListDelete_L(head,4,x))
     {
       cout<<"错误!"<<endl;
       return;
     }
	  	k=ListLength_L(head);
		cout<<"k="<<k<<endl;
	cout<<"被删除元素是:"<<x<<endl;
	cout<<"删除后的单链表为："<<endl;
    ListTraverse_L(head);
    DestroyList_L(head);
  }
