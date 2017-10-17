//假设称正读和反读都相同的字符序列为“回文”，例如“abba”和“abcba”是回文，而“abcde”和“ababab”则不是回文。①比较线性表、堆栈和队列等方式，
//1.解释哪种方式实现回文的判断合适？
//2.试写出算法判别读入的一个以“@”为结束符的字符序列是否是回文。
//答：显然是用堆栈和队列结合的方式实现合适
#include "SqQueue.h"
#include "SqStack.h"
bool IsHuiWen(char *str)
{
  SqQueue Q;
  SqStack S;
  char x,y;
  int i,length=strlen(str);
  InitQueue_Sq(Q);
  InitStack_Sq(S);
  for(i=0;i<length;i++)
  {
    EnQueue_Sq(Q,str[i]);
    Push_Sq(S,str[i]);
  }
  while(!QueueEmpty_Sq(Q)&&!StackEmpty_Sq(S))
  {
    if(DeQueue_Sq(Q,x)&&Pop_Sq(S,y)&&x!=y)
	{
      cout<<str<<"不是回文！"<<endl;
      return false;
    }
  }
  if(!QueueEmpty_Sq(Q)||!StackEmpty_Sq(S))
    {
      cout<<str<<"不是回文！"<<endl;
      return false;
    }
  else
    {
      cout<<str<<"是回文！"<<endl;
      return true;
    }
}

int main()
{
    char a[10],e;
    int i=0;
    cout<<"请输入回文字符串"<<endl;
    while((e=getchar())!='@'){
        a[i++]=e;
    }
    a[i]='@';
    cout<<isHuiwen(a)<<endl;
    return 0;
}
