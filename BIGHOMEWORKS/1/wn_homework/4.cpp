#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
typedef int ElemType;
#include "SqQueue.h"
#include "SqStack.h"

void Inverse(SqQueue &Q){
    SqStack mystack;
    InitStack_Sq(mystack);
    while(!QueueEmpty_Sq(Q)){
        ElemType e;
        DeQueue_Sq(Q,e);
        Push_Sq(mystack,e);
    }
    while(!StackEmpty_Sq(mystack)){
        ElemType e;
        Pop_Sq(mystack,e);
        EnQueue_Sq(Q,e);
    }
}


int main()
{
    SqQueue myqueue;
    InitQueue_Sq(myqueue);
    ElemType e[10]={1,2,3,4,5,6,7};
    int i=0;
    while(i<7){
        EnQueue_Sq(myqueue,e[i++]);
    }
    while(!QueueEmpty_Sq(myqueue)){
        ElemType e;
        DeQueue_Sq(myqueue,e);
        cout<<setw(4)<<e;
    }
    i=0;
    while(i<7){
        EnQueue_Sq(myqueue,e[i++]);
    }
    Inverse(myqueue);
    while(!QueueEmpty_Sq(myqueue)){
        ElemType e;
        DeQueue_Sq(myqueue,e);
        cout<<setw(4)<<e;
    }

    return 0;
}
