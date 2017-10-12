typedef int ElemType;    // 顺序表中元素类型为int
# include "stdlib.h"     // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"    // 该文件包含标准输入输出流cout和cin及控制符setw()等函数 
# include "SqList.h"     // 该文件中包含链表数据对象的描述及相关操作
	
void CreateList_Sq(SqList &L, int a[])
{ int i=0;
  if(L.length==0)
  for(int i=0;i<=sizeof(a);i++)
      ListInsert_Sq(L,i,a[i]);
}


bool Isequal(SqList La, SqList Lb, ElemType &e)
{  bool found; 
   int i,k;
   SqList Lc;
   int La_len = ListLength_Sq(La);    //求表长 
   int Lb_len = ListLength_Sq(Lb);    //求表长
   if(La_len != Lb_len)  return false;
   else
   {    
        InitList_Sq(Lc);           //初始化Lc
        for(k=0;k<=La_len;k++)     //生成La的复制品Lc
        {
            GetElem_Sq(La,k,e);
            ListInsert_Sq(Lc,k,e);
        }
    found = true;
    for(k=0;k<=Lb_len, found; k++)
    {
        GetElem_Sq(Lb,k,e);        //取Lb中第k个数据元素
        i = LocateElem_Sq(Lc,e);   //在Lc中进行查询
        if(i==0) found = false;    //La中不存在和该数据元素相同的元素
        else ListDelete_Sq(Lc,i,e); //从Lc中删除该数据元素
    }
    if(found && ListEmpty_Sq(Lc))   return true;
    else return false;
    DestroyList_Sq(Lc);
   }
}



int main()
{    SqList La,Lb;
     int i,j,temp;
     ElemType a[]={1,2,3,4,5};
     ElemType b[]={3,1,2,4,5};
     
     InitList_Sq(La);
     InitList_Sq(Lb);
     CreateList_Sq(La,a);
     CreateList_Sq(Lb,b);
     ListTraverse_Sq(La);
     ListTraverse_Sq(Lb);
     
    if(Isequal(La, Lb, temp)==true)
     cout<<"相等"<<endl;
    else
     cout<<"不相等"<<endl;
     
     
}