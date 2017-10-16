#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
typedef int ElemType;
#include "LinkList.h"
void iListTraverse_L(LinkList L)
{
    LinkList p=L;
    cout<< setw(6)<<p->data;
    p=L->next;
    while(p!=L)
    {
        cout<< setw(6)<<p->data;
        p=p->next;
    }
    cout<<endl;
}// ListTraverse_L
void iCreateList_L_Front(LinkList &L,ElemType a[],int n )
{    // 已知一维数组A[n]中存有线性表的数据元素，利用头插法创建单链表L
    LinkList p;   int i;
    L=(LinkList)malloc(sizeof(LNode));              //创建立头结点
    L->next=L;
    for(i=n-1;i>=1;i--)
    {   p=(LinkList)malloc(sizeof(LNode));           //创建新结点
        p->data=a[i];                                // 赋元素值
        p->next=L->next;                          // 插入在头结点和第一个结点之间
        L->next=p;
    }
    L->data=a[0];
}// CreateList_L_Front



bool Union_CL(LinkList &La,LinkList &Lb){
    LinkList p=La->next,q=Lb;
    La->next=Lb;
    while(q->next!=Lb){
        q=q->next;
    }
    q->next=p;
}

int main()
{
    LinkList La,Lb;
    ElemType a[10]={1,2,3,4,5};
    ElemType b[10]={6,7,8,9,10};
    iCreateList_L_Front(La,a,5);
    iCreateList_L_Front(Lb,b,5);
    iListTraverse_L(La);
    iListTraverse_L(Lb);
    Union_CL(La,Lb);
    ListTraverse_L(La);
    return 0;
}
