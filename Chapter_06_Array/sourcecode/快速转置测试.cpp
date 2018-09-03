 typedef int ElemType;   // 定义矩阵元素类型ElemType为整型
 # include "iostream.h"   // 该文件包含标准输入输出流cout和cin
 # include "iomanip.h"             // 该文件包含控制符setw()
 # include "stdlib.h"  // 该文件包含malloc()
 # include"TSMatrix.h" // 三元组顺序表存储结构、稀疏矩阵的相关运算函数

 void FastTransposeSMatrix(TSMatrix M,TSMatrix &T)
 { // 快速求稀疏矩阵M的转置矩阵T
   int p,q,col,*num,*cpot;
   num=(int*)malloc((M.n)*sizeof(int)); // 存M每列(T每行)非零元素个数
   cpot=(int*)malloc((M.n)*sizeof(int)); // 存T每行下一个非零元素的位置
   T.m=M.n; // T的行数=M的列数
   T.n=M.m; // T的列数=M的行数
   T.t=M.t; // T的非零元素个数=M的非零元素个数
   if(T.t) // T是非零矩阵
   { for(col=0;col<M.n;++col) // 从M的第1列到最后一列
       num[col]=0; // 计数器初值设为0
     for(p=0;p<M.t;++p) // 对于M的每一个非零元素
       ++num[M.data[p].j]; // 根据它所在的列进行统计
     cpot[0]=0; // T的第1行的第1个非零元在T.data中的序号为1
     for(col=1;col<M.n;++col) // 从M(T)的第2列(行)到最后一列(行)
       cpot[col]=cpot[col-1]+num[col-1]; // 求T的第col行第1个非零元在T.data中的序号
     for(p=0;p<M.t;++p) // 对于M的每一个非零元素
     { col=M.data[p].j; // 将其在M中的列数赋给col
       q=cpot[col]; // q指示M当前的元素在T中的序号
       T.data[q].i=M.data[p].j; // 将M当前的元素转置赋给T
       T.data[q].j=M.data[p].i;
       T.data[q].e=M.data[p].e;
       ++cpot[col]; // T第col行的下一个非零元在T.data中的序号比当前元素的序号大1
     }
   }
   free(num); // 释放num和cpot所指向的动态存储空间
   free(cpot);
 }

 void main()
 {
   TSMatrix A,B;
   cout<<"创建矩阵A：";
   CreateSMatrix(A); // 创建矩阵A
   TraverseSMatrix(A); // 输出矩阵A
   FastTransposeSMatrix(A,B); // B是A的转秩矩阵
   cout<<"矩阵B(A的快速转置)："<<endl;
   TraverseSMatrix(B); // 输出矩阵B
 }