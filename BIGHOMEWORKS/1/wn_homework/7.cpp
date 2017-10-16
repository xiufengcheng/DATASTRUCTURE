#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <iostream>
using namespace std;
typedef int ElemType;
#include "SqQueue.h"

void wait_in_line(SqQueue &Q){
    cout<<"请输入病历号：";
    ElemType i;
    cin>>i;
    EnQueue_Sq(Q,i);
}

void see_a_doctor(SqQueue &Q){
    ElemType e;
    DeQueue_Sq(Q,e);
    cout<<e<<"号病人就诊！"<<endl;;
}

void see_queue(SqQueue &Q){
    for(int i=Q.front;i!=Q.rear;i=(i+Q.queuesize+1)%Q.queuesize){
        cout<<setw(5)<<Q.queue[i];
    }
    cout<<endl;
}

void exit_line(SqQueue &Q){
    while(!QueueEmpty_Sq(Q)){
        ElemType e;
        DeQueue_Sq(Q,e);
        cout<<setw(5)<<e;
    }
    cout<<endl;
    exit(0);
}

void get_off_work(){
    exit(0);
}

int main()
{
    SqQueue myqueue;
    InitQueue_Sq(myqueue);
    bool working=true;
    while(working){
        cout<<"\n**********************************************************"<<endl;
        cout<<"*    欢迎来到黑诊所，请选择操作：\n";
        cout<<"*    1、排队"<<endl;
        cout<<"*    2、就诊"<<endl;
        cout<<"*    3、查看排队"<<endl;
        cout<<"*    4、不再排队"<<endl;
        cout<<"*    5、下班"<<endl;
        cout<<"*    请选择您的操作："<<endl;
        int iOperator;
        cin>>iOperator;
        switch(iOperator){
            case 1:wait_in_line(myqueue);break;
            case 2:see_a_doctor(myqueue);break;
            case 3:see_queue(myqueue);break;
            case 4:exit_line(myqueue);break;
            case 5:get_off_work();break;
            default:cout<<"错误";break;
        }
    }
    return 0;
}
