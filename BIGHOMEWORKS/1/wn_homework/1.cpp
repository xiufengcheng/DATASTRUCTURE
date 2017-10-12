#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
typedef int ElemType;
#include "LinKList.h"

bool Intersect_L(LinkList &La,LinkList Lb){
    ElemType temp;
    LinkList p,q;
    p=La->next;
    q=La;
    while(p){
        //cout<<p->data;
        if(LocateElem_L_2(Lb,p->data)==-1){
            //cout<<p->data<<endl;
            //cout<<LocateElem_L_2(Lb,p->data)<<endl;
            //cout<<LocateElem_L_2(La,p->data)<<endl;
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
