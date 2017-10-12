#### 【例3.1】 数制转换问题
 十进制数N和其它d进制数的转换是计算机实现计算的基本问题，其解决方法很多，其中一个简单算法是基于下列原理：<br>
N = (N div d)×d + N mod d(其中:div为整除运算)<br>

分析：余数存放在堆栈里，运用循环解决。
```c++
[例3.1.cpp]
typedef int ElemType;     // 链栈元素类型为int
# include "stdlib.h"      // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"     // 该文件包含标准输入输出流cout、cin及控制符setw()
# include "LinkStack.h"   // 该文件包含链栈数据对象的描述及相关操作

void TransFrom(long N,int d )
{
LinkStack S;             // 用顺序栈和链栈都可以，此处是链栈
int x;
  InitStack_L(S);
while(N)
   { Push_L(S,N % d);
     N=N/d;
    }
while(!StackEmpty_L(S))
{ Pop_L(S,x);
     cout<<x;
}
   cout<<endl;
}// TransFrom

void main()
{ int num,dec;              // num存放十进制数，dec存放进制
  cout<<"输入一个十进制数：";
  cin>>num;
  cout<<"输入要转换的进制：";
cin>>dec;  
cout<<"转换后的"<<dec<<"进制数为："; 
  TransFrom(num,dec);                 // 调用数制转换函数
}	
```

----------------

#### 【例3.2】表达式求值

分析：中缀表达式是人能读懂的， 后缀表达式是计算机读懂的
1. **中缀规则**：先乘除后加减、先括号内再括号外、同级别时先左后右
2. **后缀规则**：没有括号，不必考虑优先关系，从左到右依次扫描、读到一个运算符即计算前面两个操作数
3. **中缀转后缀**：首先编写一个优先级函数char Process(char x1, char x2)，用于比较x1和x2的优先级
<img width="400"  src="/Chapter_03_Stack/img/3.2.jpg"/>

```c++
[例3.2.cpp]
char Proceed(char x1,char x2)
{           
   char Result;               // 保存比较结果
   char MidString[2];         
   Result='<';                
   MidString[0]=x2;           // 将x2与'\0'构成一个字符串
   MidString[1]=0;
   if(((x1=='+'||x1=='-')&&strstr("+-)#", MidString)!=NULL)||((x1=='*'||x1=='/')&&strstr("+-*/)#", MidString)!=NULL)||(x1==')'&&strstr("+_*/)#", MidString)!=NULL))
        Result='>';  
     else if((x1=='('&&x2==')')||(x1=='#'&&x2=='#'))
     Result='=';  
          else if((x1=='('&&x2=='#')||(x1==')'&&x2=='(')||(x1=='#'&&x2==')'))
                 Result=' '; 
   return Result;
}// Proceed
```

4. 然后编写一个算法，包括创建两个数组Post_Expression和Pre_Expression,分别存放后缀表达式和前缀表达式，再设置一个堆栈装填运算符，算法如下：<br>
   - 依次从左到右扫描中缀表达式
   - 若输入为操作数，则直接输入到后缀表达式，并接着读下一个单词；
   - 若输入为运算符，则比较扫描运算符**x2**和栈顶运算符**x1**的优先级。
        - 若x2>x1，则将x2入栈，继续读取下一个单词
        - 若x2<x1，则弹x1至后缀表达式，然后继续比较x2和新x1的优先级
        - 若x2=x1
            - x1=(,x2=)，则弹出x1，然后继续下一个单词
            - x1 =x2 = #，则算法结束

<img width="500"  src="/Chapter_03_Stack/img/3.3.3.jpg"/>

```c++
[例3.3.cpp]
bool Postfix(char *Mid_Expression,char *Post_Expression)
{   // 将中缀表达式mid_Expression转换为后缀表达式Post_Expression
   SqStack S;
   char x1,x2,x,y; // x1为栈顶运算符，x2为当前输入的运算符，比较x1和x2的优先级
   int i=0,j=0;
   InitStack_Sq(S);                     // 运算符栈初始化
   Push_Sq(S,'#');                      // 栈顶置结束符"#"
   x2=Mid_Expression[j];                // 输入当前字符到x2
   if(!GetTop_Sq(S,x1)) exit(0);        // 取栈顶运算符
   while(1)
   { if(x2!='+'&&x2!='-'&&x2!='*'&&x2!='/'&&x2!='('&&x2!=')'&&x2!='#')
	  { Post_Expression[i++]=x2;      // 输入的字符为操作数，直接输出到后缀表达式
        x2=Mid_Expression[++j];               // 输入下一个字符
      }
      else if(Proceed(x1,x2)=='<')   // 输入的运算符的优先级大于栈顶运算符的优先级
	      { if(!Push_Sq(S,x2)) exit(0);           // 输入的运算符入栈
            if(!GetTop_Sq(S,x1)) exit(0);         // 取栈顶运算符
            x2=Mid_Expression[++j];               // 输入下一个字符
	       }
          else if(Proceed(x1,x2)=='>')   // 输入的运算符的优先级小于栈顶运算符的优先级 
	            {
                  if(!Pop_Sq(S,x)) exit(0);        // 栈顶运算任出栈
                  Post_Expression[i++]=x;          // 输出到后缀表达式
                  if(!GetTop_Sq(S,x1))  exit(0);    // 取栈顶运算符
	}
                  else if(Proceed(x1,x2)=='='&&x1=='('&&x2==')')  // 输入的运算符的优先级等于栈顶运算任的优先级,且栈顶运算符为"("，输入的运算符为")"
	                    { if(!Pop_Sq(S,y))  exit(0);  // 弹出栈顶运算符，不输出到后缀表达式
                         if(!GetTop_Sq(S,x1))  exit(0);  // 取栈顶运算符
                         x2=Mid_Expression[++j];         // 输入下一个字符
	                  }
                  else if(Proceed(x1,x2)=='='&&x1=='#'&&x2=='#')  // 输入的运算符的优先级等于栈顶运算任的优先级,且栈顶运算符和输入的运算符为都为"#"
                        { Post_Expression[i]='\0'; // 后缀表达式置结束标志
		                   return true;               // 成功返回
	                     }
                  else if(Proceed(x1,x2)==' ') break; //表达式语法错，退出
           } 
       cout<<"错误"<<endl;
       return false;	
}// Postfix
```
<img width="850"  src="/Chapter_03_Stack/img/3.2.5.jpg"/>


5. 后缀表达式的求值
- 算法思想：设置一个堆栈，从左到右依次扫描后缀表达式，每读到一个操作数，就将其压入堆栈；每读到一个运算符，就从栈顶去除两个操作数施以该运算符所代表的操作，并把计算结果作为一个新的操作数压如堆栈。
<img width="600"  src="/Chapter_03_Stack/img/表达式求值6.png"/>


#### 【例3.3】背包问题
<img width="850"  src="/Chapter_03_Stack/img/背包问题1.jpg"/>
<img width="850"  src="/Chapter_03_Stack/img/背包问题2.jpg"/>

```c++
[例3.3.cpp]
typedef int ElemType;     // 链栈元素类型为int
# include "stdlib.h"      // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"     // 该文件包含标准输入输出流cout、cin及控制符setw()
# include "SqStack.h"     // 该文件包含顺序栈数据对象的描述及相关操作

void Print(SqStack S,int w[],int n)
{        
	int k=S.top;
	while(k>=0)
	 cout<<w[S.stack[k--]]<<' ';
   cout<<endl;
}// Print

void knapsack( int w[], int T, int n ) 
{      // 已知n件物品的体积分别为 w[0], w[1], …, w[n]，背包的总体积为 T,
        // 本算法输出所有恰好能装满背包的物品组合解
    SqStack S;
	int k;
	InitStack_Sq(S);   k=0;               // 从第0 件物品考察起
    do {
      while (T>0 && k<n ) 
       { if (T-w[k]>=0 )                  // 第k件物品可选，则k入栈
         { Push_Sq(S,k);  T-=w[k];        // 背包剩余体积减少w[k]
          }
          k++;                            // 继续考察下一件物品
        }
     if(T==0)  Print(S,w,6);        // 输出一组解，之后回溯寻找下一组解
     Pop_Sq(S,k );  T+= w[k];       // 退出栈顶物品，背包剩余体积增添w[k]
     k++;                                   // 继续考察下一件物品
  } while (!StackEmpty_Sq(S)||k!=n );
}// knapsack

void main()
{int w[]={1,8,4,3,5,2},T=10;  // 背包总体积为10
  knapsack(w,T,6);
}
```

#### 【例3.4】划分子集问题
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

#### 【例3.5】轮渡问题
```c++
[in 例3.5.cpp]

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
```