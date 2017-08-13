typedef int ElemType;   
# include "stdlib.h"
# include "iostream.h"
# include "iomanip.h"
# include "SqList.h"

void main()
 {
 SqList mylist;
  int i,x,k,j;
  InitList_Sq(mylist, 50,10);
  for(i=0;i<10;i++)
  if(!ListInsert_Sq(mylist, i, i+1))
     {
       cout<<"错误!"<<endl;
       return;
     }
     k=ListLength_Sq(mylist);
     cout<<"表长为："<<k<<endl;
	 j=LocateElem_Sq(mylist, 6);
	 if(j!=-1) cout<<"查找的元素为："<<mylist.elem[j]<<endl;
	 cout<<"元素不存在."<<endl;
	 if(GetElem_Sq(mylist,15,x))  cout<<"第5个元素是:"<<x<<endl;
	  else cout<<"错误"<<endl;
	if(!ListDelete_Sq(mylist,4, x))
    {
      cout<<"错误!"<<endl;
       return;
     }
	cout<<"被删除元素是:"<<x<<endl;
	cout<<"删除后的顺序表为："<<endl;
   ListTraverse_Sq(mylist);
   DestroyList_Sq(mylist);
  }