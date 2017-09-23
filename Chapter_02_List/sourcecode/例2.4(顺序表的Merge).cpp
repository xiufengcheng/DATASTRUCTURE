typedef int ElemType;      // 顺序表中元素类型为int
# include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"      // 该文件包含标准输入输出流cout和cin及控制符setw()
# include "SqList.h"       // 该文件中包含顺序表数据对象的描述及相关操作

void MergeList_Sq(SqList La, SqList Lb,SqList &Lc) 
{    // 归并两个非递减有序的顺序表La和lb成为一个非递减有序的顺序表Lc
  int i=0,j=0,k=0;                    // i,j,k分别指向各自的表头
  InitList_Sq(Lc, La.length+Lb.length,10);  // 创建一个空的顺序表Lc
  while(i<La.length&&j<Lb.length)             // 归并
	    if(La.elem[i]<=Lb.elem[j]) 
 Lc.elem[k++]=La.elem[i++]; 
    else Lc.elem[k++]=Lb.elem[j++]; 
  while(i<La.length)  Lc.elem[k++]=La.elem[i++];
  while(j<Lb.length)  Lc.elem[k++]=Lb.elem[j++];
  Lc.length=La.length+Lb.length;
}// MergeList_Sq

int main()
 { 
  SqList La,Lb,Lc;
  ElemType a[]={2,6,9,13,45};
  ElemType b[]={1,6,19,25,45,60};
  InitList_Sq(La, 50,10);                  // 初始化顺序表La
  for(int i=0;i<5;i++)                     // 创建顺序表La
  if(!ListInsert_Sq(La,i,a[i]))           
     { cout<<"插入失败！"<<endl;
       return 0;
     }
    cout<<"顺序表La：";
   ListTraverse_Sq(La);                  // 显示顺序表La
  InitList_Sq(Lb, 50,10);                // 初始化顺序表Lb
  for(int i=0;i<6;i++)                       // 创建顺序表Lb
  if(!ListInsert_Sq(Lb,i,b[i]))
     { cout<<"插入失败！"<<endl;
       return 0;
     }
   cout<<"顺序表Lb：";
   ListTraverse_Sq(Lb);                   // 显示顺序表Lb
   MergeList_Sq(La,Lb,Lc) ;               // 归并La和Lb为Lc
   cout<<"归并后的顺序表Lc：";
   ListTraverse_Sq(Lc);                   // 显示顺序表Lc
   
   return 0;
 }	
