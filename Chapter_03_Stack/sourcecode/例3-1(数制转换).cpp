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
