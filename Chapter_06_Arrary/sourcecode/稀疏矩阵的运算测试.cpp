typedef int ElemType;         // 定义矩阵元素类型ElemType为整型
# include "stdlib.h"           // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"          // 该文件包含标准输入输出流cout和cin及控制符setw()


# include "TSMatrix.h"        // 该文件包含三元组顺序表数据对象的描述及相关操作

 void main()
 {
   TSMatrix A,B,C;
   cout<<"创建矩阵A：";
   CreateSMatrix(A);                    // 创建矩阵A
   TraverseSMatrix(A);                   // 输出矩阵A
   CopySMatrix(A,B);                     // 由矩阵A复制矩阵B   
   cout<<"由矩阵A复制矩阵B1："<<endl;
   TraverseSMatrix(B);                    // 输出矩阵B
   DestroySMatrix(B);                     // 撤销矩阵B
   cout<<"创建矩阵B2：(与矩阵A的行、列数相同，行、列分别为";
cout<<A.m<<","<<A.n<<")"<<endl;
   CreateSMatrix(B);                      // 创建矩阵B
   TraverseSMatrix(B);                    // 输出矩阵B
   AddSMatrix(A,B,C);                      // 矩阵相加，C=A+B
   cout<<"矩阵C1(A+B)："<<endl;
   TraverseSMatrix(C);                     // 输出矩阵C
   SubtSMatrix(A,B,C);                     // 矩阵相减，C=A-B
   cout<<"矩阵C2(A-B)："<<endl;
   TraverseSMatrix(C);                    // 输出矩阵C
   TransposeSMatrix(A,C);                 // 矩阵C是矩阵A的转置矩阵
   cout<<"矩阵C3(A的转置)："<<endl;
   TraverseSMatrix(C);                    // 输出矩阵C
   cout<<"创建矩阵A2：";
   CreateSMatrix(A);                      // 创建矩阵A
   TraverseSMatrix(A);                    // 输出矩阵A
   cout<<"创建矩阵B3：(行数应与矩阵A2的列数相同="<<A.n<<")"<<endl;
   CreateSMatrix(B);                      // 创建矩阵B
   TraverseSMatrix(B);                     // 输出矩阵B
   MultSMatrix(A,B,C);                     // 矩阵相乘，C=A×B
   cout<<"矩阵C4(A×B)："<<endl;
   TraverseSMatrix(C);                     // 输出矩阵C
 }
