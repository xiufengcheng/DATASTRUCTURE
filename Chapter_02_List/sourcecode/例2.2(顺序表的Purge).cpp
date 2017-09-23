typedef int ElemType;    // 顺序表中元素类型为int
# include "stdio.h"  
# include "stdlib.h"     // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"    // 该文件包含标准输入输出流cout和cin及控制符setw()等函数 
# include "SqList.h"     // 该文件中包含链表数据对象的描述及相关操作
	
void CreateList_Sq(SqList &L, int a[])
{ int i=0;
  if(L.length==0)
  for(int i=0;i<=sizeof(a);i++)
      ListInsert_Sq(L,i,a[i]);
}

	
void Purge(SqList &La,SqList Lb, ElemType &e)
{
    InitList_Sq(La);          //初始化La,即创建一个新的，空的线性表La,这个放到外面写
    while(!ListEmpty_Sq(Lb))     //Lb表的元素尚未处未处理完
    {
        ListDelete_Sq(Lb,0,e);    //从Lb中删除第一个数据元素赋值给e
        if(LocateElem_Sq(La,e)==-1)     //若La中不存在值和e相等的数据元素
           ListInsert_Sq(La,La.length,e);   //则将它插入在La中最后一个数据元素之后
    }
    DestroyList_Sq(Lb); //撤销线性表
}



int main()
{	
	int temp;
	SqList Lb;
	InitList_Sq(Lb, 30, 5);
	int a[5] = {3,2,2,1,4};
	CreateList_Sq(Lb,a);
    ListTraverse_Sq(Lb);
    
    SqList La;
    InitList_Sq(La, 30, 5);
    Purge(La, Lb, temp);
    ListTraverse_Sq(La);
    
    return 0; 
 }	