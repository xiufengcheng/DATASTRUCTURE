
typedef int ElemType;       // 链队元素类型为int
# include "stdlib.h"        // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"       // 该文件包含标准输入输出流cout、cin以及setw()等
# include "time.h"          // 此头文件中包含有time函数ctime函数的声明
# include "LinkQueue.h"     // 该文件包含链队数据对象的描述及相关操作

void Print(int a[],int n)
{        // 输出每次渡轮所载汽车的编号
long t=time(0);        // 当前机器系统时间被保存在t中，单位为秒
cout<<endl;
cout<<"轮渡开始起航->"<<endl;
cout<<"本次过江时间："<<ctime(&t)<<endl;
	     // ctime(&t)函数的值为根据参数t转换得到的日期和时间的字符串
cout<<"本次轮渡所载汽车：";
for(int i=0;i<n;i++) cout<<a[i]<<' ';
cout<<endl;
}// Print

void auto_register(LinkQueue &q1,LinkQueue &q2)
 {    // 车到渡口进行登记
	   int x;
   cout<<"输入车辆号，假定小于100为客车，否则为货车，"<<endl;
cout<<"可以输入多辆车，用空格分开，直至输入-1为止。"<<endl;
	   while(1)
	   { cin>>x;
		 if(x==-1) break;
		 if(x<100) EnQueue_L(q1,x);     // 客车进q1队
		 else EnQueue_L(q2,x);          // 货车进q2队
	    }
  }// auto_register

void ferry_register(long &t1,int &mark,int &n)
 {   // 渡轮到渡口进行登记
	   if(mark==1)
	   { cout<<"渡轮已在渡口等待，不要重复登记！"<<endl;
	     return;
	    }
	    mark=1;                     // 渡轮到口岸登记
	    cout<<"渡轮已到渡口，可以上船！"<<endl;
	    n=0;                      // 装载车辆数初始为0
	    t1=time(0);               // 登记渡轮到渡口时间
  }// ferry_register

void auto_up_ferry(LinkQueue &q1,LinkQueue &q2,int a[10],int t1,int &mark,int &n) 
 {      // 汽车上轮渡
	  int i;
	  long t2;
	  if(QueueEmpty_L(q1)&&QueueEmpty_L(q2))
	  { cout<<"暂无汽车过江！"<<endl;
		if(mark==1&&n!=0)
		 { t2=time(0)-t1;        // 计算到目前为止渡轮等待的时间
		   cout<<"渡轮未满，有车"<<n<<"辆，已等待"<<t2/60<<"分";
		   cout<<t2%60<<"秒，等待其他汽车上渡轮！"<<endl;
		  }
		  return;
	    }
		if(mark!=1)
		 { cout<<"渡轮未到，请汽车稍后上渡轮！"<<endl;
		   return;
		  }
		 do
		  { i=n%5;
			 while(!QueueEmpty_L(q1)&&n<10 && i<4)    // 首先上4辆客车
			 {	 DeQueue_L(q1,a[n++]);
				 i++;
		      }
			    // 满10辆开船,打印车辆号，重新对mark和n清0，转功能菜单
			  if(n==10) {Print(a,n);mark=0;n=0;return; }
			            // 进4辆客车则接着进一辆货车，不满4辆则由货车补
			     if(i==4) { if(!QueueEmpty_L(q2)) DeQueue_L(q2,a[n++]); }
			 else
	  			 { while(!QueueEmpty_L(q2) && n<10 && i<5)
				   { DeQueue_L(q2,a[n++]);
				     i++;
				    }
			     }
	           if(n==10) {Print(a,n);mark=0;n=0;return; }  // 满10辆开船
		      }while(!QueueEmpty_L(q1)||!QueueEmpty_L(q2));//do-while
		 t2=time(0)-t1;        // 登记渡轮等待的时间
	    	 cout<<"渡轮上有车"<<n<<"辆，已等待"<<t2/60<<"分";
			 cout<<t2%60<<"秒，等待其他汽车上渡轮！"<<endl;
		 	 return;
	      }// auto_up_ferry

	 void ferry_set_sail(int a[10],int &mark,int &n)
	 {
                  // 命令轮渡起航
	    if(n==0||mark==0)
		   cout<<"渡轮上无车过江或根本无渡轮！不需要起航！"<<endl;
		 else {  Print(a,n);mark=0;n=0;  }
	 }// ferry_set_sail

void OutputQueue(LinkQueue &q1,LinkQueue &q2)
{    // 输出汽车排队等待情况
cout<<"客车排队的情况：";
QueuePtr p=q1.front;
if(!p) cout<<"暂时无客车等候。"<<endl;
	  while(p)
	  {	cout<<p->data<<' ';
	    p=p->next;
	  }
cout<<endl;
cout<<"货车排队的情况：";
	  p=q2.front;
	  if(!p) cout<<"暂时无货车等候。"<<endl;
	  while(p)
	  {	cout<<p->data<<' ';
	    p=p->next;
	   }
cout<<endl;
}// OutputQueue

void end_run(LinkQueue &q1,LinkQueue &q2,int n)
{      // 结束程序运行
if(!QueueEmpty_L(q1)||!QueueEmpty_L(q1))
	  {	cout<<"还有汽车未渡江，暂不能结束。"<<endl;
		return;
	   }
	 if(n!=0)
	  {	cout<<"渡轮上有车，不能结束，需命令开渡轮！"<<endl;
		return;
	  }
	  cout<<"程序运行结束！"<<endl;
	  exit(0);
}// end_run

void main()
{
LinkQueue q1,q2;   // q1和q2队列分别存储待渡江的客车和货车
InitQueue_L(q1);   // 初始化q1
InitQueue_L(q2);   // 初始化q2
int flag,mark=0;   // flag保存用户选择,mark登记渡轮到渡口
int a[10],n=0;     // 数组a记录渡轮上的每个汽车号,n记录汽车的个数
long t1;           // t1登记时间
do{                // 显示功能菜单并接受用户选择
    cout<<"功能菜单："<<endl;
   cout<<"1---车到渡口进行登记"<<endl;
   cout<<"2---渡轮到渡口进行登记"<<endl;
   cout<<"3---汽车上轮渡"<<endl;
   cout<<"4---命令轮渡起航"<<endl;
   cout<<"5---输出当前汽车排队情况"<<endl;
   cout<<"6---结束程序运行"<<endl<<endl;
   cout<<"请输入你的选择(1-6)：";
   do{
	      cin>>flag;
	      if(flag<1||flag>6) cout<<"输入菜单号错，重输：";
     }while(flag<1||flag>6);  //内层do-while
   // 根据不同问题进行相应处理
   switch(flag)
   {case 1:auto_register(q1,q2); break;
	    case 2:ferry_register(t1,mark,n);break;
	    case 3:auto_up_ferry(q1,q2,a,t1,mark,n);  break;
	    case 4:ferry_set_sail(a,mark,n); break;
	    case 5:OutputQueue(q1,q2); break;
	    case 6:end_run(q1,q2,n); break;
   }
}while(1);                  // 外层do_while 
DestroyQueue_L(q1);
DestroyQueue_L(q2);
}
