typedef  int ElemType;
# include "stdlib.h"     
# include "iostream.h"   
# include "iomanip.h"     
# include "LinkList.h"

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
      
      cout<<endl<<"<====现在执行定位元素操作,您要找的元素值？"<<endl;
      cout<<"请输入：";
      cin>>forLocate;
      j = LocateElem_L_2(mylist,forLocate);
      if(j!=-1&&GetElem_L(mylist,1,temp)) 
	  cout<<"找到了，它是第"<<j+2<<"个元素（其中，"<<temp<<"是第一个元素）====>"<<endl;
      else cout<<"没找到这个元素！"<<endl;
	  //如果你想使用另外一个函数：
      //LinkList q = LocateElem_L(mylist,forLocate);
	  //cout<<q->data<<endl;
      
      cout<<endl<<"<====现在执行取元素操作,您要找第几个元素？"<<endl;
      cout<<"请输入：";
      cin>>forGet;
      if(GetElem_L(mylist,forGet,temp)) 
      cout<<"第"<<forGet<<"个元素的值是:"<<temp<<"====>"<<endl;
      else cout<<"元素不存在！"<<endl;
      
      
	  cout<<endl<<"<====现在执行插入操作,您要将什么元素插入顺序表？"<<endl;
	  cout<<"请输入：";
	  cin>>forInsert;
	  cout<<"插入到第几个位置？"<<endl;
	  cout<<"请输入：";
	  cin>>temp;
	  if(!ListInsert_L(mylist, temp, forInsert))
	  {cout<<"插入失败!"<<endl; return 0;} 
	  else cout<<"==>插入成功，插入后的链表为：====>"<<endl;
	  ListTraverse_L(mylist);
	  
	  
	  cout<<endl<<"<====现在执行删除操作,您要删除第几个元素？"<<endl;
	  cout<<"请输入：";
	  cin>>forDelete;
	  if(!ListDelete_L(mylist,forDelete,temp)) 
      {cout<<"删除失败!"<<endl; return 0;} 
	  else cout<<"删除成功，删除后的链表为：====>"<<endl;
	  ListTraverse_L(mylist);
	  
      //ListVisualization_L(mylist,"showlinklist.dot");
      
      cout<<endl<<"<====现在执行销毁操作***"<<endl;
      DestroyList_L(mylist);
      cout<<"销毁成功====>"<<endl;
  }
