typedef int ElemType;     // 定义数组元素类型ElemType为整型
# include "stdarg.h"     // 该文件包含VA_start()、va_arg()、va_end()等函数
# include "stdlib.h"     // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"    // 该文件包含标准输入输出流cout和cin及控制符setw()
# include "Array.h"      // 该文件包含数组数据对象的描述及相关操作

 void main()
 {
   Array A;
   int i,j,k,dim=3,b1=3,b2=4,b3=2;            // A[3][4][2]数组
   ElemType e;
   InitArray(A,dim,b1,b2,b3);                 // 构造3×4×2的三维数组A
   cout<<"A.b=";
   for(i=0;i<dim;i++)                         // 顺序输出A.b
     cout<<setw(4)<< A.b[i];
   cout<<endl;
   cout<<"A.c=";
   for(i=0;i<dim;i++)                         // 顺序输出A.c
     cout<<setw(4)<<A.c[i];
   cout<<endl;
   cout<<b1<<"页"<<b2<<"行"<<b3<<"列矩阵元素如下："<<endl;
   for(i=0;i<b1;i++)
   { for(j=0;j<b2;j++)
     { for(k=0;k<b3;k++)
       { Assign(A,i*100+j*10+k,i,j,k);      // 将i×100+j×10+k赋值给A[i][j][k]
        Value(e,A,i,j,k);                   // 将A[i][j][k]的值赋给e
        cout<<"  "<<"A["<<i<<"]["<<j<<"]["<<k<<"]="<<setw(2)<<e;// 输出A[i][j][k]
       }
       cout<<endl;
     }
    cout<<endl;
   }
   cout<<"A.base="<<endl;

   for(i=0;i<b1*b2*b3;i++)                               // 顺序输出A.base
   { cout<<setw(5)<<A.base[i];
     if(i%(b2*b3)==b2*b3-1)
      cout<<endl;
   }
  cout<<"A.dim="<<A.dim<<endl;
   DestroyArray(A);
}
