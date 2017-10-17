#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
typedef int ElemType;
#include "LinKList.h"

bool Intersect_Arr(SqList &La,SqList Lb) //用顺序表实现
{
   ElemType temp;
    while(!ListEmpty_Sq(La))     //La表的元素尚未处未处理完
    {
        GetElem_Sq(La,0,temp);    //从La中删除第一个数据元素赋值给temp
        if(LocateElem_Sq(Lb,temp)==-1)     //若Lb中不存在值和temp相等的数据元素
              ListDelete_Sq(La,0,e);     //则将它插入在La中最后一个数据元素之后
    }
    DestroyList_Sq(Lb);               //撤销线性表 
}

bool Intersect_L(LinkList &La,LinkList Lb){   //用链表实现
    ElemType temp;
    LinkList p,q;
    p=La->next;
    q=La;
    while(p){
        if(LocateElem_L_2(Lb,p->data)==-1){
            ListDelete_L(La,LocateElem_L_2(La,p->data)+1,temp);
            //ListTraverse_L(La);
            p=La->next;
        }else{
            p=p->next;
        }
    }
    return true;
}

int main()
{
    int i,j,k;
    LinkList La,Lb;
    InitList_L(La);
    InitList_L(Lb);
    ElemType a[]={1,2,3,4,5,6,7,8,9};
    ElemType b[]={2,4,6,8,10};
    CreateList_L_Front(La,a,9);
    CreateList_L_Front(Lb,b,5);
    ListTraverse_L(La);
    ListTraverse_L(Lb);
    Intersect_L(La,Lb);
    ListTraverse_L(La);
    return 0;
}
