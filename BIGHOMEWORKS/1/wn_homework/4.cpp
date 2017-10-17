//已知Q是一个（不带头结点的）非空队列，S是一个（不带头结点的）空栈
//编写算法实现：将队列Q中的所有元素逆置。要求：调用头文件操作函数实现。
//答：元素依次出队列，依次入栈，逆序出栈，依次人队列

#include "SqQueue.h"
#include "SqStack.h"

void Inverse(SqQueue &Q, SqQueue &S){
    while(!QueueEmpty_Sq(Q)){
        ElemType e;
        DeQueue_Sq(Q,e);
        Push_Sq(S,e);
    }
    while(!StackEmpty_Sq(S)){
        ElemType e;
        Pop_Sq(mystack,e);
        EnQueue_Sq(Q,e);
    }
}
