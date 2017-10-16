#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
typedef int ElemType;
#include "SqQueue.h"

int main()
{
    SqQueue myqueue;
    InitQueue_Sq(myqueue,5,5);
    ElemType a[10]={1,2,3,4,5,6,7};
    for(int i=0;i<6;i++){
        EnQueue_Sq(myqueue,a[i]);
    }
    while(!QueueEmpty_Sq(myqueue)){
        ElemType e;
        DeQueue_Sq(myqueue,e);
        cout<<setw(4)<<e;
    }
    return 0;
}
