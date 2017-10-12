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
