typedef int ElemType;       // 单链表中元素类型为int
# include "stdlib.h"        // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"        // 该文件包含标准输入输出流cout和cin及控制符setw()
# include "LinkList.h"      // 该文件中包含单链表数据对象的描述及相关操作

int  main()
     {
      LinkList head;
      int i,x,a[]={6,8,16,2,34,56,7,10,22,45};
      InitList_L(head);                       // 初始化单链表
      for(i=1;i<=10;i++)
        if(!ListInsert_L(head,i,a[i-1]))  // 将a[i]插入到单链表中第i个元素之前
        { cout<<"插入失败！"<<endl;
          return 0;
        }
cout<<"删除前的单链表为：";
    ListTraverse_L(head);                      // 显示单链表中的数据元素
      if(!ListDelete_L(head,4,x))                // 删除第4个元素
       { cout<<"删除失败！"<<endl;
         return 0;
       }
cout<<"被删除元素是："<<x<<endl;
	  cout<<"删除后的单链表为：";
      ListTraverse_L(head);                      // 显示单链表中的数据元素
      DestroyList_L(head);                       // 撤销单链表
      return 0;
   }
