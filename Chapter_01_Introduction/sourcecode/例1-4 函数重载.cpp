# include "iostream.h"                 // 该文件包含标准输入输出流cout和cin
int max(int a,int b)                    // 函数1
{
  return(a>b?a:b);
}
float max(float a,float b,float c)       // 函数2
 { float t=a;
      if(t<b) t=b;
   if(t<c) t=c;
   return t;
 }

void main( )
{
 cout<<"max(2,3)="<<max(2,3)<<endl;
 cout<<"max(2.3,5.6,3.1)="<<max(2.3,5.6,3.1)<<endl;
}
