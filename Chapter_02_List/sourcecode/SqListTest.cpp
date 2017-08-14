typedef int ElemType;    // 顺序表中元素类型为int
# include "stdio.h"  
# include "stdlib.h"     // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"    // 该文件包含标准输入输出流cout和cin及控制符setw()等函数 
# include "SqList.h"     // 该文件中包含链表数据对象的描述及相关操作


int main()
{
  SqList mylist;
  int i,j,temp,forLocate,forGet,forInsert,forDelete;
  
  InitList_Sq(mylist, 50, 10);  
  for(i=0,j=1;i<10;i++,j++)
  if(!ListInsert_Sq(mylist,i, 2*j))
  {cout<<"错误!"<<endl; return 0;}
  cout<<"我创建了一个顺序表，表长为："<<ListLength_Sq(mylist)<<endl;
  cout<<endl<<"表中的元素依次为："<<endl;
  ListTraverse_Sq(mylist);
  
  
  cout<<endl<<"***现在执行元素定位操作,请输入需要查找的元素：***"<<endl;
  cin>>forLocate;
  j=LocateElem_Sq(mylist, forLocate);
  if(j!=-1) cout<<"找到了，它是第"<<j+1<<"个元素。"<<endl;
  else cout<<"定位失败！"<<endl;
  
  
  cout<<endl<<"***现在执行取元素操作,您要找第几个元素？请输入：***"<<endl;
  cin>>forGet;
  if(GetElem_Sq(mylist,forGet-1,temp))  
  cout<<"第"<<forGet<<"个元素的值是:"<<temp<<endl;
  else cout<<"取元素失败！"<<endl;
 
 
  cout<<endl<<"***现在执行插入操作,您要将什么元素插入顺序表？请输入：***"<<endl;
  cin>>forInsert;
  cout<<"***插入到第几个位置？***"<<endl;
  cin>>temp;
  if(!ListInsert_Sq(mylist, temp-1, forInsert))
  {cout<<"插入!"<<endl; return 0;} 
  else cout<<"插入成功，插入后的顺序表为："<<endl;
  ListTraverse_Sq(mylist);
  
 
  cout<<endl<<"***现在执行删除操作,您要删除第几个元素？请输入：***"<<endl;
  cin>>forDelete;
  if(!ListDelete_Sq(mylist,forDelete-1,temp))
  {cout<<"删除失败!"<<endl; return 0;} 
  else cout<<"删除成功，删除后的顺序表为："<<endl;
  ListTraverse_Sq(mylist);
 
  //  visualization(mylist,"showsqlist.dot");
 
  cout<<endl<<"***现在执行撤销操作***"<<endl;
  DestroyList_Sq(mylist);
  
 
  cout<<"***顺序表已经销毁！***"<<endl;
  return 0; 
 }