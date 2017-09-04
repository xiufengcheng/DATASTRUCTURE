typedef int ElemType;
#include <iomanip.h>
#include <iostream.h>
#include "SqQueue.h"

int main(){
	SqQueue myQueue;
	int i,x,a[]={6,8,16,2,34,56,7,10,22,45,62,88};
	InitQueue_Sq(myQueue,10,10);   //初始画循环队列
	for(i=0;i<12;i++){
		if(!EnQueue_Sq(myQueue,a[i])){
			cout<<"进队失败！"<<endl;
			return 1;
		}
	} 
	if(!GetHead_Sq(myQueue,x)){
		cout<<"取队首元素失败！"<<endl;
		return 1;
	}
	cout<<"当前队首元素数据是："<<x<<endl;
	cout<<"当前顺序队列的长度是："<<QueueLength_Sq(myQueue)<<endl;
	visualization(myQueue,"showsqlist.dot");
	cout<<"依次出对的数据元素序列为：";
	while(!QueueEmpty_Sq(myQueue)){
		if(!DeQueue_Sq(myQueue,x)){
			cout<<"出对失败"<<endl;
			return 1; 
		}
		cout<<x<<' ';
	} 
	cout <<endl;
	cout<<"当前顺序队列的长度是："<<QueueLength_Sq(myQueue)<<endl;
	cout<<endl;
	DestroyQueue_Sq(myQueue); 
	return 0;
}