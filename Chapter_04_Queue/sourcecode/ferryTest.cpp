typedef int ElemType;
#include <stdlib.h>
#include <iomanip.h>
#include <time.h>
#include "LinkQueue.h"
#include "ferry.h"

int main(){
	LinkQueue q1,q2;
	InitQueue_L(q1);
	InitQueue_L(q2);
	int flag,mark=0;
	int a[10],n=0;
	long t1;
	do{
		cout<<"功能菜单："<<endl;
		cout<<"1-- -车到渡口进行登记"<<endl;
		cout<<"2-- -渡轮到渡口进行登记"<<endl;
		cout<<"3-- -汽车上渡轮"<<endl;
		cout<<"4-- -命令渡轮启航"<<endl;
		cout<<"5-- -输出当前汽车排队情况"<<endl;
		cout<<"6-- -结束程序运行"<<endl<<endl;
		cout<<"输入你的选择（1-6）:";
		do{
			cin>>flag;
			if(flag<1||flag>6)  cout<<"输入菜单号错，重输:";
		}while(flag<1||flag>6);
		//根据输入进行处理
		switch(flag){
			case 1:auto_register(q1,q2);break;
			case 2:ferry_register(t1,mark,n);break;
			case 3:auto_up_ferry(q1,q2,a,t1,mark,n);break;
			case 4:ferry_set_sail(a,mark,n);break;
			case 5:OutputQueue(q1,q2);break;
			case 6:end_run(q1,q2,n);break;
			
		} 
	}while(2); 
	DestroyQueue_L(q1);
	DestroyQueue_L(q2);
	return 0;
}