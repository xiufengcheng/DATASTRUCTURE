typedef char ElemType;     // 顺序栈元素类型为char
# include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"      // 该文件包含标准输入输出流cout、cin及控制符setw()
# include "SqStack.h"      // 该文件包含顺序栈数据对象的描述及相关操作
# include "string.h"       // 该文件包含C++串的的定义及相关操作

char Proceed(char x1,char x2)
{           
   char Result;               // 保存比较结果
   char MidString[2];         
   Result='<';                
   MidString[0]=x2;           // 将x2与'\0'构成一个字符串
   MidString[1]=0;
   if(((x1=='+'||x1=='-')&&strstr("+-)#", MidString)!=NULL)||
((x1=='*'||x1=='/')&&strstr("+-*/)#", MidString)!=NULL)||
(x1==')'&&strstr("+_*/)#", MidString)!=NULL))
        Result='>';  
     else if((x1=='('&&x2==')')||(x1=='#'&&x2=='#'))
     Result='=';  
          else if((x1=='('&&x2=='#')||(x1==')'&&x2=='(')||(x1=='#'&&x2==')'))
                 Result=' '; 
   return Result;
}// Proceed

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
          else if(Proceed(x1,x2)=='>')   
// 输入的运算符的优先级小于栈顶运算符的优先级 
	            {
                  if(!Pop_Sq(S,x)) exit(0);        // 栈顶运算任出栈
                  Post_Expression[i++]=x;          // 输出到后缀表达式
                  if(!GetTop_Sq(S,x1))  exit(0);    // 取栈顶运算符
	}
                  else if(Proceed(x1,x2)=='='&&x1=='('&&x2==')')  
  // 输入的运算符的优先级等于栈顶运算任的优先级 
		                             // 且栈顶运算符为"("，输入的运算符为")"
	                    { if(!Pop_Sq(S,y)) 
 exit(0);  // 弹出栈顶运算符，不输出到后缀表达式
                         if(!GetTop_Sq(S,x1))  exit(0);  // 取栈顶运算符
                         x2=Mid_Expression[++j];         // 输入下一个字符
	                  }
                    else if(Proceed(x1,x2)=='='&&x1=='#'&&x2=='#')  
   // 输入的运算符的优先级等于栈顶运算任的优先级 
		                        // 且栈顶运算符和输入的运算符为都为"#"
                        { Post_Expression[i]='\0'; // 后缀表达式置结束标志
		                   return true;               // 成功返回
	                     }
                        else if(Proceed(x1,x2)==' ') break; //表达式语法错，退出
           } 
       cout<<"错误"<<endl;
       return false;	
}// Postfix

void main( )
{
char Mid_Expression[80]={"A+(B-C/D)*E"},Post_Expression[80];
cout<<"中缀表达式为："<< Mid_Expression<<endl;
// 中缀表达式转换为后缀表达式
Postfix(strcat(Mid_Expression,"#"),Post_Expression); 
cout<<"后缀表达式为："<<Post_Expression<<endl;
}
