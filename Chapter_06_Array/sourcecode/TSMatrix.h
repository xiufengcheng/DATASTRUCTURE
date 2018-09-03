# define MAX_SIZE 100          // 非零元素个数的最大值
typedef struct  {
 int  i;             // 行下标
 int  j;             // 列下标
 ElemType  e;        // 非零元素值
}Triple;             // 三元组定义
typedef struct {
   int m,n,t;                  // 矩阵的行数、列数、非零元素个数
Triple data[MAX_SIZE];      // 非零元三元组表
 }TSMatrix;                    // 三元组顺序表定义
int comp(int c1,int c2)
{
	if(c1<c2) return -1;
	   else if(c1==c2)  return 0;
	        else  return 1;
}
bool CreateSMatrix(TSMatrix &M)
 { // 创建稀疏矩阵M
   int i;
   Triple T;
   bool k;
   cout<<"请输入矩阵的行数,列数,非零元素个数：";
   cin>>M.m>>M.n>>M.t;
   if(M.t>MAX_SIZE)                          // 非零元个数太多
     return false;
   M.data[0].i=0;     // 为比较输入的行列的顺序做准备
   M.data[0].j=0;
   for(i=0;i<M.t;i++) // 依次输入M.t个非零元素
   { do
     { cout<<"请按行序顺序输入第"<<i+1<<"个非零元素所在的行(0～"<<M.m-1<<"),列(0～"<<M.n-1<<"),元素值：";
       cin>>T.i>>T.j>>T.e;
       k=0; // 输入值的范围正确的标志
       if(T.i<0||T.i>=M.m||T.j<0||T.j>=M.n) // 行或列超出范围
         k=1;
	    if(i>0)
        if(T.i<M.data[i-1].i||T.i==M.data[i-1].i&&T.j<=M.data[i-1].j)
         k=1; // 行或列的顺序有错 
	  }while(k); // 输入值的范围不正确则重新输入
     M.data[i]=T; // 将输入正确的值赋给三元组结构体M的相应单元
   }
   return true;
 }

void CopySMatrix(TSMatrix M,TSMatrix &T)
 { // 由稀疏矩阵M复制得到T
   T=M;
 }

 bool AddSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q)
 { // 求稀疏矩阵的和Q=M+N
   int m=0,n=0,q=0,i=0;
   if(M.m!=N.m||M.n!=N.n) // M、N两稀疏矩阵行或列数不同
     return false;
   Q.m=M.m; // 设置稀疏矩阵Q的行数和列数
   Q.n=M.n;
   while(m<M.t&&n<N.t) // 矩阵M和N的元素都未处理完
    switch(comp(M.data[m].i,N.data[n].i)) // 比较两当前元素的行值关系
     { case -1:Q.data[q++]=M.data[m++]; // 矩阵M的行值小，将M的当前元素值赋给矩阵Q
	           break;
       case  0:switch(comp(M.data[m].j,N.data[n].j))
               { // M、N矩阵当前元素的行值相等，继续比较两当前元素的列值关系
                 case -1:Q.data[q++]=M.data[m++]; // 矩阵M的列值小，将M的值赋给矩阵Q 
					     break;
                 case  0:// M、N矩阵当前非零元素的行列均相等，将两元素值求和并赋给矩阵Q
                         Q.data[q]=M.data[m++];
						 Q.data[q].e+=N.data[n++].e;
						 q++;
				         if(Q.data[q].e==0) // 两元素值之和为0，不存入稀疏矩阵
                           q--;
						 break;
                 case  1:Q.data[q++]=N.data[n++]; // 矩阵N的列值小，将N的值赋给矩阵Q
               }
		   	   break;
       case  1:Q.data[q++]=N.data[n++]; // 矩阵N的行值小，将N的当前元素值赋给矩阵Q
     } // 以下2个循环最多执行1个
   while(m<M.t) // 矩阵N的元素已全部处理完毕，处理矩阵M的元素
     Q.data[q++]=M.data[m++];
   while(n<N.t) // 矩阵M的元素已全部处理完毕，处理矩阵N的元素
	  Q.data[q++]=N.data[n++];
   if(q>MAX_SIZE) // 非零元素个数太多
     return false;
   Q.t=q; // 矩阵Q的非零元素个数
   return true;
 }

 bool SubtSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q)
 { // 求稀疏矩阵的差Q=M-N
   int i;
   if(M.m!=N.m||M.n!=N.n) // M、N两稀疏矩阵行或列数不同
     return false;
   for(i=0;i<N.t;++i) // 对于N的每一元素，其值乘以-1
     N.data[i].e*=-1;
     AddSMatrix(M,N,Q); // Q=M+(-N)
    return true;
 }

void TransposeSMatrix(TSMatrix M,TSMatrix &T)
 { // 求稀疏矩阵M的转置矩阵T
   int p,col,q=0; // q指示转置矩阵T的当前元素，初值为1
   T.m=M.n; // 矩阵T的行数=矩阵M的列数
   T.n=M.m; // 矩阵T的列数=矩阵M的行数
   T.t=M.t; // 矩阵T的非零元素个数=矩阵M的非零元素个数
   if(T.t) // 矩阵非空
     for(col=0;col<M.n;++col) // 从矩阵T的下标为0的行到最后一行
       for(p=0;p<M.t;++p) // 对于矩阵M的所有元素
         if(M.data[p].j==col) // 该元素的列数=当前矩阵T的行数
         { T.data[q].i=M.data[p].j; // 将矩阵M的值行列对调赋给T的当前元素
           T.data[q].j=M.data[p].i;
           T.data[q++].e=M.data[p].e; // 转置矩阵T的当前元素指针+1
         }
 }

 bool MultSMatrix(TSMatrix M,TSMatrix N,TSMatrix &Q)
 { // 求稀疏矩阵的乘积Q=M×N
   int i,j,q,p;
   ElemType Qs; // 矩阵单元Q[i][j]的临时存放处
   TSMatrix T; // N的转置矩阵
   if(M.n!=N.m) // 矩阵M和N无法相乘
     return false;
   Q.m=M.m; // Q的行数=M的行数
   Q.n=N.n; // Q的列数=N的列数
   Q.t=0; // Q的非零元素个数的初值为0
   TransposeSMatrix(N,T); // T是N的转置矩阵
   for(i=0;i<Q.m;i++) // 对于M的每一行，求Q[i][]
   { q=0; // q指向T的第1个非零元素
     for(j=0;j<T.m;j++) // 对于T的每一行(即N的每一列)，求Q[i][j]
     { Qs=0; // 设置Q[i][j]的初值为0
       p=0; // p指向M的第1个非零元素
       while(M.data[p].i<i) // 使p指向矩阵M的第i行的第1个非零元素
         p++;
       while(T.data[q].i<j) // 使q指向矩阵T的第j行(即矩阵N的第j列)的第1个非零元素
         q++;
       while(p<M.t&&q<T.t&&M.data[p].i==i&&T.data[q].i==j)
       // [p]仍是M的第i行的非零元素且[q]仍是T的第j行(即N的第j列)的非零元素
         switch(comp(M.data[p].j,T.data[q].j))
         { // 比较M矩阵当前元素的列值和T矩阵当前元素的列值(即N矩阵当前元素的行值)
           case -1:p++; // M矩阵当前元素的列值<T(N)矩阵当前元素的列(行)值，p向后移
                   break;
           // M当前元素的列值=T(N)当前元素的列(行)值，则两值相乘并累加到Qs，p、q均向后移
           case  0:Qs+=M.data[p++].e*T.data[q++].e;
                   break;
           case  1:q++; // M矩阵当前元素的列值>T(N)矩阵当前元素的列(行)值，q向后移
         }
       if(Qs) // Q[i][j]不为0
       { if(++Q.t>MAX_SIZE) // Q的非零元素个数+1，如果非零元素个数太多
           return false;
         Q.data[Q.t-1].i=i; // 将Q[i][j]按顺序存入稀疏矩阵Q
         Q.data[Q.t-1].j=j;
         Q.data[Q.t-1].e=Qs;
       }
     }
   }
   return true;
 }

 void TraverseSMatrix(TSMatrix M)
 { // 按矩阵形式输出M
   int i,j,k=1; // 非零元计数器，初值为1
   Triple *p=M.data; // p指向M的第1个非零元素
   for(i=0;i<M.m;i++) // 从第1行到最后一行
   { for(j=0;j<M.n;j++) // 从第1列到最后一列
       if(k<=M.t&&p->i==i&&p->j==j) // p指向非零元，且p所指元素为当前循环在处理元素
       { cout<<setw(3)<<(p++)->e;   // 输出p所指元素的值，p指向下一个元素
         k++; // 计数器+1
       }
       else // p所指元素不是当前循环在处理元素
         cout<<setw(3)<<0; // 输出0
     cout<<endl;
   }
 } 

  void DestroySMatrix(TSMatrix &M)
 { // 销毁稀疏矩阵M
   M.m=M.n=M.t=0;
 }
