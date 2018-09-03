#define MAX_ARRAY_DIM 8 // 假设数组维数的最大值为8
typedef struct {
   ElemType *base; // 数组元素基址，由InitArray分配
   int dim; // 数组维数
   int *b; // 数组维界基址，由InitArray分配
   int *c; // 数组映象函数常量基址，由InitArray分配
 }Array;

bool InitArray(Array &A,int dim,...)
 { // 若维数dim和各维长度合法，则构造相应的数组A，并返回true
   int elemtotal=1,i; // elemtotal是数组元素总数，初值为1(累乘器)
   va_list ap; // 变长参数表类型，在stdarg.h中，是存放变长参数表信息的数组
   if(dim<1||dim>MAX_ARRAY_DIM) // 数组维数超出范围
     return false;
   A.dim=dim; // 数组维数
   A.b=(int*)malloc(dim*sizeof(int)); // 动态分配数组维界基址
   if(!A.b)     exit(1);                // 存储分配失败
   va_start(ap,dim); // 变长参数“...”从形参dim之后开始
   for(i=0;i<dim;++i)
   { A.b[i]=va_arg(ap,int); // 逐一将变长参数赋给A.b[i]
     if(A.b[i]<0)
       return false; // 长度不合法
	 // 若各维长度合法，则存入数组A.b中，并求出A的元素总数
     elemtotal*=A.b[i]; 
   }	
   va_end(ap); // 结束提取变长参数
   A.base=(ElemType*)malloc(elemtotal*sizeof(ElemType)); // 动态分配数组存储空间
   if(!A.base)     exit(1);     // 存储分配失败
   // 求映象函数的常数Ci,并存入数组A.c[i-1],i=1,…,dim
   A.c=(int*)malloc(dim*sizeof(int)); // 动态分配数组偏移量基址
   if(!A.c)     exit(1);  // 存储分配失败
   A.c[dim-1]=1; // 最后一维的偏移量为1(L=1,指针的增减以元素的大小为单位）
   for(i=dim-2;i>=0;--i)
     A.c[i]=A.b[i+1]*A.c[i+1];   // 每一维的偏移量
    return true;
 }

 void DestroyArray(Array &A)
 { // 销毁数组A。
   if(A.base) // A.base指向存储单元
     free(A.base); // 释放A.base所指向的存储单元
   if(A.b)
     free(A.b);
   if(A.c)
     free(A.c);
     A.base=NULL;    // 使它们不再指向任何存储单元
	 A.b=A.c=NULL; 
   A.dim=0;
 }

 bool Locate(Array A,va_list ap,int &off) 
 { // 若ap指示的各下标值合法，则求出该元素在A中的相对地址off
   int i,ind;
   off=0;
   for(i=0;i<A.dim;i++)
   { ind=va_arg(ap,int); // 逐一读取各维的下标值
     if(ind<0||ind>=A.b[i]) // 各维的下标值不合法
       return false;
     off+=A.c[i]*ind; // 相对地址=各维的下标值*本维的偏移量之和
   }
   return true;
 }

 bool Value(ElemType &e,Array A,...) // 在VC++中，“...”之前的形参不能是引用类型
 { // “...”依次为各维的下标值，若各下标合法，则e被赋值为A的相应的元素值
   va_list ap; // 变长参数表类型，在stdarg.h中
   int off;
   va_start(ap,A); // 变长参数“...”从形参A之后开始
   if(!Locate(A,ap,off)) // 调用Locate()，求得变长参数所指单元的相对地址off
     return false;
   e=*(A.base+off); // 将变长参数所指单元的值赋给e
   return true;
 }

 bool Assign(Array A,ElemType e,...) 
 { // “...”依次为各维的下标值，若各下标合法，则将e的值赋给A的指定的元素。
   va_list ap; // 变长参数表类型，在stdarg.h中
   int off;
   va_start(ap,e); // 变长参数“...”从形参e之后开始
   if(!Locate(A,ap,off)) // 调用Locate()，求得变长参数所指单元的相对地址off
     return false;
   *(A.base+off)=e; // 将e的值赋给变长参数所指单元
   return true;
 }