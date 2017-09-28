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
