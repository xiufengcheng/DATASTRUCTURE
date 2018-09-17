typedef int ElemType;    // 顺序表中元素类型为int

# include "stdlib.h"     // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"    // 该文件包含标准输入输出流cout和cin及控制符setw()等函数,visual studio中可能不需要写.h
//# include "iostream"   //visual studio中可能要用到
# include "SqList.h"     // 该文件中包含链表数据对象的描述及相关操作

void Union(SqList &La, SqList Lb, ElemType &e)
{
    int La_len = ListLength_Sq(La);   //求线性表La的长度
    while(!ListEmpty_Sq(Lb))     //Lb表的元素尚未处未处理完
    {
        ListDelete_Sq(Lb,0,e);    //从Lb中删除第一个数据元素赋值给e
        if(LocateElem_Sq(La,e)==-1)     //若La中不存在值和e相等的数据元素
           {ListInsert_Sq(La,La.length,e);  //则将它插入在La中最后一个数据元素之后
           }
    }
    DestroyList_Sq(Lb); //撤销线性表
}
	
int main()
{	
	
	SqList La;
	SqList Lb;
	int i,j, temp;
	InitList_Sq(La, 30, 5);
	for(i=0,j=1;i<10;i++,j++)
	ListInsert_Sq(La,i, 6+2*j);
	ListTraverse_Sq(La);
	
	InitList_Sq(Lb, 30, 5);
	for(i=0,j=1;i<10;i++,j++)
	ListInsert_Sq(Lb,i, 2*j);
	ListTraverse_Sq(Lb);
	
	Union(La,Lb,temp);
	//ListInsert_Sq(La, La.length, Lb.elem[0]);
	cout<<La.length<<endl;
	ListTraverse_Sq(La);
  return 0; 
 }	