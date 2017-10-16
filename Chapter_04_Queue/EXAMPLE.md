#### 【例3.4】 运动会比赛日程安排（划分无冲突子集问题）
 队列的应用很广。例如，操作系统中的各种资源请求排队和各种数据缓冲的先进先出管理，各种应用系统的**事件规划**、**事件模拟**、**树类**和**图类**问题中的一些非递归搜索等等<br>
某运动会设立N个比赛项目，每个运动员可以参加1~3个项目。试问如何安排比赛日程，既可以使同一运动员参加的项目不安排在同一单位时间进行，又使总的竞赛日程最短? <br>

分析：若将此问题抽象成数学模型，则归属于“划分子集”问题。<br>
N个比赛项目构成一个大小为n的集合，有同一运动员参加的项目则抽象为“冲突”关系。 <br>
例如：设运动会有A={0,1,2,3,4,5,6,7,8,9}个项目<br>
有7名运动员参与比赛。<br>
<img width="400"  src="/Chapter_04_Queue/img/3.4.jpg"/>
算法思想：<br>
利用顺序循环队列可以实现这个思想。<br>
令集合中的元素依次插入队列，之后重复下列操作：将队列中的队头元素出队，成为某个子集中的第一个元素，之后依次让队头元素出队列并检查它与当前子集中的各元素是否冲突，若不冲突，则将它加入该子集；否则重新“进队”，以等待“下一次”开辟新子集的机会。<br>
由于重新进队的元素序号必定小于队尾元素，则一旦发现当前出队的元素序号小于前一个出队的元素时，说明已构成一个子集。(从而保证每次重新归类时，队列内的元素总是从小到大排列)<br>
如此循环直至队列删空为止。 <br>


```c++
[例3.4.cpp]
# define N 9	
typedef int ElemType;      // 循环队列元素类型为int
# include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"      // 该文件包含标准输入输出流cout、cin及控制符setw()
# include "SqQueue.h"      // 该文件包含循环队列数据对象的描述及相关操作

void division(int R[N][N],int n, int result[ ],int &group) 
{    // 已知 R[N][N]是编号为0 至n-1的 n个元素的关系矩阵,子集划分的结果
    // 记入result数组,result[k]的值是编号为 k 的元素所属组号
int i,j,pre=n;  
int clash[N];
   SqQueue Q;
   InitQueue_Sq(Q,n+1);                       // 设置最大容量为 n+1的空队列
   for(int e=0; e<n; e++)  EnQueue_Sq (Q,e);  // 全体项目进队
     while (!QueueEmpty_Sq(Q)) 
{ DeQueue_Sq(Q,i); 
       if(i<=pre ) 
{ group ++;                              // 增加一个新的组
         for(j=0; j<n; j++)  
clash[j]=0;
	  }
     if (clash[i]==0) 
{ result[i] = group;                // 编号为i 的元素入group 组
       for(j=0; j<n; j++ ) clash[j]+= R[i][j];   // 添加和 i冲突的信息
     }
     else EnQueue_Sq(Q,i);             // 编号为i的元素不能入当前组,重新进队
	  pre=i; 
  } 
}// division

void main()
{ int i,j,result[N],group=0; 
int R[N][N]={{0,1,0,0,0,1,0,0,0},{1,0,0,0,1,1,0,1,1},{0,0,0,0,0,1,1,0,0},
{0,0,0,0,1,0,0,0,1},{0,1,0,1,0,0,1,0,1},{1,1,1,0,0,0,1,0,0},
{0,0,1,0,1,1,0,0,0},{0,1,0,0,0,0,0,0,0},{0,1,0,1,1,0,0,0,0}};
  division (R,N,result,group);
  cout<<"总共分"<<group<<"个小组。"<<endl;
  cout<<"分组情况如下："<<endl;
  for( i=0;i<N;i++)
	   cout<<result[i]<<' ';
  cout<<endl;
 for( i=1;i<=group;i++)
  { cout<<"第"<<i<<"小组的项目为：";
	   for( j=0;j<N;j++)
		  if(result[j]==i) cout<<j<<' ';
	  cout<<endl;
  }
}

```

----------------

#### 【例3.5】轮渡问题。（事件规划）  
有一个渡口，每条渡轮一次能装载 10辆汽车过江，过江车辆分为客车和货车两类，上渡轮有如下规定： <br>
⑴同类汽车先到先上船。 <br>
⑵客车先于货车上船。 <br>
⑶每上4辆客车才允许上一辆货车，但若等待的客车不足4辆则用货车填补，反过来若没有货车等待则用客车填补。 <br>
⑷装满10辆后则自动开船，当等待时间较长时车辆不足10辆也应人为控制发船。  <br>

问题分析:此题应建立和使用两个队列，一个为客车队列，另一个为货车队列，到渡口需过江的汽车分别进入到相应队列中。当渡口有渡轮时先让客车队列中的4个车辆出队并开进渡轮，再让货车队列中的一个车辆出队并开进渡轮，若某一类车辆队列为空则从另一个队列中补充。当渡轮上的车辆己装满则自动开船，此时应打印出已装车辆的每个车号。若装载不足10辆，但两个车辆队列全为空，应继续等待一段时间，若等待时间较长，仍不满载则应人为控制开船。 <br>

在这个应用中，主要有4类“事件”，即：车到渡口进行登记、渡轮到渡口进行登记、汽车上轮渡和渡轮起航。其中，车到渡口进行登记就是让客车和货车分别进各自所属的队列；渡轮到渡口进行登记首先要用一个标志来表明渡轮是否到达渡口，如用变量mrak=1表示渡轮已到达渡口，mrak=0表示渡轮已离开渡口，其次还要登记渡轮到达渡口的时间；汽车上轮渡则按问题要求处理客车队列和货车队列需要何时出队，并适时命令渡轮起航；渡轮起航则主要是打印出已装车辆的车号，并让渡轮离开渡口。下面用不同的的函数来实现上述功能，同时增加两个函数分别实现打印渡轮起航时所载汽车的编号和汽车排队等待情况。因此该问题的算法由以下列主要模块构成：车到渡口进行登记、渡轮到渡口进行登记、汽车上轮渡、命令轮渡起航、输出当前汽车排队情况 。<br>



<img width="400"  src="/Chapter_03_Stack/img/3.2.jpg"/>

```c++
[轮渡问题.cpp]

typedef int ElemType;       // 链队元素类型为int
# include "stdlib.h"        // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"       // 该文件包含标准输入输出流cout、cin以及setw()等
# include "time.h"          // 此头文件中包含有time函数ctime函数的声明
# include "LinkQueue.h"     // 该文件包含链队数据对象的描述及相关操作

void Print(int a[],int n)// 输出每次渡轮所载汽车的编号
{                        
        long t=time(0);        // 当前机器系统时间被保存在t中，单位为秒
        cout<<endl;
        cout<<"轮渡开始起航->"<<endl;
        cout<<"本次过江时间："<<ctime(&t)<<endl;// ctime(&t)函数的值为根据参数t转换得到的日期和时间的字符串
	    cout<<"本次轮渡所载汽车：";
        for(int i=0;i<n;i++) cout<<a[i]<<' ';
        cout<<endl;
}// Print

void auto_register(LinkQueue &q1,LinkQueue &q2)     // 车到渡口进行登记
 {    
	   int x;
       cout<<"输入车辆号，假定小于100为客车，否则为货车，"<<endl;
       cout<<"可以输入多辆车，用空格分开，直至输入-1为止。"<<endl;
	   while(1)
	   { 
	        cin>>x;
		    if(x==-1) break;
		    if(x<100) EnQueue_L(q1,x);     // 客车进q1队
		    else EnQueue_L(q2,x);          // 货车进q2队
	   }
  }// auto_register

void ferry_register(long &t1,int &mark,int &n)     // 渡轮到渡口进行登记
 {  
	   if(mark==1)
	   { 
	        cout<<"渡轮已在渡口等待，不要重复登记！"<<endl;
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
	  { 
	       cout<<"暂无汽车过江！"<<endl;
		   if(mark==1&&n!=0)
		       { 
			        t2=time(0)-t1;        // 计算到目前为止渡轮等待的时间
		            cout<<"渡轮未满，有车"<<n<<"辆，已等待"<<t2/60<<"分";
		            cout<<t2%60<<"秒，等待其他汽车上渡轮！"<<endl;
		       }
		   return 0;
	  }
      if(mark!=1)
	  { 
		     cout<<"渡轮未到，请汽车稍后上渡轮！"<<endl;
		     return;
	  }
	  do
	  { 
		     i=n%5;
			 while(!QueueEmpty_L(q1)&&n<10 && i<4)    // 首先上4辆客车
			 {	 
			     DeQueue_L(q1,a[n++]);
				 i++;
		      }
		
		    if(n==10) {Print(a,n);mark=0;n=0;return; }   // 满10辆开船,打印车辆号，重新对mark和n清0，转功能菜单
			            // 进4辆客车则接着进一辆货车，不满4辆则由货车补
			if(i==4) { if(!QueueEmpty_L(q2)) DeQueue_L(q2,a[n++]); }
			else{ 
			       while(!QueueEmpty_L(q2) && n<10 && i<5)
				   { 
				       DeQueue_L(q2,a[n++]);
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

void OutputQueue(LinkQueue &q1,LinkQueue &q2)   // 输出汽车排队等待情况
{    
     cout<<"客车排队的情况：";
     QueuePtr p=q1.front;
     if(!p) cout<<"暂时无客车等候。"<<endl;
	 while(p)
	 {	
	     cout<<p->data<<' ';
	     p=p->next;
	 }
     cout<<endl;
     cout<<"货车排队的情况：";
	 p=q2.front;
	 if(!p) cout<<"暂时无货车等候。"<<endl;
	 while(p)
	 {	
	    cout<<p->data<<' ';
	    p=p->next;
	 }
     cout<<endl;
}// OutputQueue

void end_run(LinkQueue &q1,LinkQueue &q2,int n)
{      // 结束程序运行
      if(!QueueEmpty_L(q1)||!QueueEmpty_L(q1))
	  {	
		     cout<<"还有汽车未渡江，暂不能结束。"<<endl;
		     return;
	  }
	 if(n!=0)
	  {
	         cout<<"渡轮上有车，不能结束，需命令开渡轮！"<<endl;
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

```
