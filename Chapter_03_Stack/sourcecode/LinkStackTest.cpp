typedef int ElemType;      // 链栈元素类型为int
# include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"      // 该文件包含标准输入输出流cout、cin及控制符setw()
# include "LinkStack.h"    // 该文件包含链栈数据对象的描述及相关操作
	
void main()
 {
 LinkStack mystack;
  int i,x,a[]={6,8,16,2,34,56,7,10,22,45,62,88};
  InitStack_L(mystack);                 // 初始化链栈
  for(i=0;i<12;i++)
    if(!Push_L(mystack,a[i]))            // a[i]依次进链栈
     { cout<<"进栈失败！"<<endl;
       return;
     }
	if(!GetTop_L(mystack,x))             // 取栈顶元素并赋值给x
    {  cout<<"取栈顶元素失败！"<<endl;
       return;
     }
	cout<<"当前栈顶数据元素是："<<x<<endl;
	cout<<"当前链栈的长度是："<<StackLength_L(mystack)<<endl;
// 求链栈的长度并输出
	cout<<"依次出栈的数据元素序列为：";
    while(!StackEmpty_L(mystack))       // 判栈是否非空
	{  if(!Pop_L(mystack,x))              // 栈顶元素出栈并赋值给x
       {  cout<<"出栈失败！"<<endl;
          return;
       }
	   cout<<x<<' ';
	}
	cout<<endl;
	cout<<"当前链栈的长度是："<<StackLength_L(mystack)<<endl;
	cout<<endl;
	DestroyStack_L(mystack);             // 撤销链栈
  }
