typedef int ElemType;       // 单链表中元素类型为int
# include "stdlib.h"        // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"        // 该文件包含标准输入输出流cout和cin及控制符setw()
# include "LinkList.h"      // 该文件中包含单链表数据对象的描述及相关操作

int  main()
     {
      LinkList head;
      int i,x,k,a[]={6,8,16,2,34,56,7,10,22,45};



///////算法2.12
      InitList_L(head);                       // 初始化单链表
      for(i=1;i<=9;i++)
        if(!ListInsert_L(head,i,a[i-1]))     // 将a[i]插入到单链表中第i个元素之前
        { cout<<"插入失败！"<<endl;
          return 0;
        }
      

///////算法2.13
	cout<<endl<<endl<<"链表长度为：" <<ListLength_L(head)<<endl;
	cout<<"链表显示："<<endl;
	ListTraverse_L(head); 



///////算法2.14
    cout<<endl<<endl<<"元素10所在位置为：";
    LNode *p2 = LocateElem_L(head,10);
	cout<<p2->next<<endl;
	



///////算法2.15
    cout<<endl<<endl<<"现在在第三个元素16之前插入元素15"<<endl;
    ListInsert_L(head,3,15);
    cout<<"插入后的单链表为："<<endl; 
	ListTraverse_L(head); 
    cout<<"插入后的单链表长度为"<<ListLength_L(head)<<endl; 


///////算法2.16
	cout<<endl<<endl<<"现在删除第八个元素"<<endl;
      if(!ListDelete_L(head,8,x))                
       { cout<<"删除失败！"<<endl;
       }
    cout<<"被删除元素是："<<x<<endl;
    cout<<"删除后的单链表显示："<<endl;
      ListTraverse_L(head);
      

///////算法2.17
    cout<<endl<<endl<<"此时第五个元素是：";
 	if(GetElem_L(head,5,x)) 
	     cout<<x<<endl;
 	else cout<<"元素不存在"<<endl;
  DestroyList_L(head);


///////算法2.18  
      LinkList head2;
      int b[]={10,20,30,40,50};
      InitList_L(head2);      
	  CreateList_L_Front(head2,b,5);
      cout<<"现在建立第二个链表（头插）";
      ListTraverse_L(head2);
      DestroyList_L(head2);


///////算法2.19
      LinkList head3;
      int c[]={10,20,30,40,50};
      InitList_L(head3);      
	  CreateList_L_Rear(head3,c,5);
      cout<<"现在建立第三个链表（尾插）";
      
///////算法2.20
      ListTraverse_L(head3);
      
///////算法2.21
      DestroyList_L(head3);    
    

 
}
