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
