## 第四章（队列）目录
>* <font size = 8 color = blue>[数组](#数组)</font>
>>* <font size = 8 color = blue>[一维数组](#一维数组)</font>
>>* <font size = 8 color = blue>[多维数组](#多维数组)</font>
>* <font size = 8 color = blue>[广义表](#广义表)</font>
-----------------------------

## 数组(Array)

### 定义
- **数组**：是由类型相同的数据元素构成的有限集合，每个数据元素称为一个数组元素（简称元素），每个元素受n（n≥1）个线性关系的约束，每个元素在n个线性关系中的序号j<sub>1</sub>，j<sub>2</sub>，…，j<sub>n</sub>，称为该元素的下标，并称该数组为n维数组。
  - j的下标<sub>n</sub>与线性表重元素的序号不同，该n表示每个元素受n个线性关系的约束。而j表示数组中元素的下标。
  - 例如，对于一个m行n列的二维数组A<sub>m×n</sub>可以看成是长度为m的线性表（每一行为线性表中的一个元素），它本身又是一个长度为n的线性表（每一列为线性表中的一个元素，它本身又是一个长度为m的线性表）。
  <img width="700"  src="/Chapter_06_Arrary/img/1.png"/>
  - 对于上述数组中的某元素A<sub>ij</sub>（0≤i≤m-1, 0≤j≤n-1）则受m和n两个线性关系的约束。
  - 数组是线性表的推广，线性表中的元素是原子元素（非结构的原子类型），而数组（非结构的扩展类型）中的元素本身可以是一个种数据结构。

- **数组的操作**
  - 数组的操作只能是存取和修改，而线性表除此之外还可以做插入与删除等操作。
  - **存取**（读写）：给定一组下标，存入或去除相应的数组元素。
  - **修改**（写）：给定一组下标，修改相应的数组元素。
  - 存取和修改在本质上都是一种操作：**寻址**，即根据一组下标定位相应的元素。

- 注意事项：
  - **元素推广性**：元素本身可以具有某种结构，而不限定是单个的数据元素。
  - **元素同一性**：元素具有相同的数据类型。
  - **关系确定性**：每个元素均受n（n≥1）个线性关系的约束，元素个数和元素之间的关系一般不发生变动。
-------------
#### 数组与线性表的区别（简答题）
- 数组是线性表的推广
   - 线性表：元素的线性排列（有序），其元素为原子类型。
   - 数组：将线性表中数据元素的类型扩充为线性表。
   - 对于一个m行n列的二维数组Am×n可以看成(1)长度为m的线性表 (2)长度为n的线性表，如上图。
   - 即此时的线性表中的元素本身也是一个线性表。
- 数组的操作只能是存取和修改，而线性表除此之外还可以做插入与删除等操作。

### 数组的ADT
```C++
ADT Array{
    Data： 
        数据元素具有相同类型。
        每个元素均受n(n≥1)个线性关系的约束并由一组下标唯一标识。
    Operation：
        InitArray（&A，dim，bound1，…，boundn）
           操作结果：若维数dim和各维长度合法，则构造相应的数组A。
        DestroyArray（&A）
           初始条件：A是n维数组。
           操作结果：撤销数组A。
        Value（A，&e，index1，…，indexn）
            初始条件：A是n维数组，e为元素变量，随后是n个下标值。
            操作结果：若各下标不超界，则e赋值为所指定的A的元素值。
         Assign（A，e，index1，…，indexn）
            初始条件：A是n维数组，e为元素变量，随后是n个下标值。
            操作结果：若下标不超界，则将e的值赋给所指定的A的元素。
         Locate（A,va_list ap,int &off)
            初始条件：A是n维数组，ap指示一组下标。                       
            操作结果：若ap指示的各下标值合法，则求出该元素在A中的相对地址off
}ADT Array
```
-------------

### 数组的存储结构
- 数组通常没有插入和删除操作（一经建立，关系固定）
- 元素在数组中的位置通常称为数组下标
- 通过下标，可以找到

#### 一维数组的存储
- 一维数组就顺序地存放在一段连续的存储单元中
  <img width="100"  src="/Chapter_06_Arrary/img/2.png"/>
- 如上图，设数组a[n]的每个元素占有L个存储单元，其第一个元素的存储首址表示为Loc(a<sub>0</sub>)，则数组a中第i个元素（0≤i≤n-1）的存储首址为：
Loc(a<sub>i</sub>)=loc(a<sub>0</sub>)+i×L

#### 二维数组的存储
- 二维数A(<sub>m×n</sub>)组可以看成是以m个单位元素构成一维数组(每个单位有n个元素)，也可以看成是以n个元素为单位构成的一维数组(每个单位有m个元素)
- 用一组连续的存储单元存放二维数组的数据元素，一般有两种存储方式：
	- 以行序为主序的存储方式（先存储第0行，然后存储第1行...）
		- a<sub>00</sub>, a<sub>01</sub> , ... , a<sub>0,n-1</sub> , a<sub>10</sub> , a<sub>11</sub> , ... , a<sub>1,n-1</sub> , ..., a<sub>m-1,0</sub> , a<sub>m-1,1</sub> , ... , a<sub>m-1,n-1</sub>
		- 公式：**Loc(a<sub>ij</sub>)=Loc(a<sub>00</sub>)+(i×n+j)×L**
		- **行乘以列加列**
	- 以列序为主序的存储方式（先存储第0列，然后存储第1列...）
		- a<sub>00</sub>, a<sub>10</sub> , ... , a<sub>m-1,0</sub> , a<sub>0,1</sub> , a<sub>11</sub> , ... , a<sub>m-1,1</sub> , ..., a<sub>0,n-1</sub> , a<sub>1,n-1</sub> , ... , a<sub>m-1,n-1</sub>
    	- 公式：**Loc(a<sub>ij</sub>)=Loc(a<sub>00</sub>)+(j×m+i)×L**
		- **列乘以行加行**

#### n维数组的存储(见课本)
- 静态存储
	- 相关操作的实现较为简单
- 动态存储
	- 较灵活，但相关操作的实现较复杂。
```c++
#define MAX_ARRAY_DIM 8 // 假设数组维数的最大值为8
typedef struct {
   ElemType *base; // 数组元素基址，由InitArray分配
   int dim; // 数组维数
   int *b; // 数组维界基址，由InitArray分配
   int *c; // 数组映象函数常量基址，由InitArray分配
 }Array;
```
#### 初始化操作
若维数dim和各维长度合法，则构造相应的数组A，并返回true
```c++
bool InitArray(Array &A,int dim,...)
 { 
   int elemtotal=1,i;      // elemtotal是数组元素总数，初值为1(累乘器)
   va_list ap;          // 变长参数表类型，在stdarg.h中，是存放变长参数表信息的数组
   if(dim<1||dim>MAX_ARRAY_DIM)      // 数组维数超出范围
     return false;
   A.dim=dim;                  // 数组维数
   A.b=(int*)malloc(dim*sizeof(int)); // 动态分配数组维界基址
   if(!A.b)     exit(1);                // 存储分配失败
   va_start(ap,dim);            // 变长参数“...”从形参dim之后开始
   for(i=0;i<dim;++i)
   { A.b[i]=va_arg(ap,int);       // 逐一将变长参数赋给A.b[i]
     if(A.b[i]<0)
       return false;            // 长度不合法
	 // 若各维长度合法，则存入数组A.b中，并求出A的元素总数
     elemtotal*=A.b[i]; 
   }	
   va_end(ap);            // 结束提取变长参数
   A.base=(ElemType*)malloc(elemtotal*sizeof(ElemType));          // 动态分配数组存储空间
   if(!A.base)     exit(1);     // 存储分配失败
   // 求映象函数的常数Ci,并存入数组A.c[i-1],i=1,…,dim
   A.c=(int*)malloc(dim*sizeof(int)); // 动态分配数组偏移量基址
   if(!A.c)     exit(1);  // 存储分配失败
   A.c[dim-1]=1; // 最后一维的偏移量为1(L=1,指针的增减以元素的大小为单位）
   for(i=dim-2;i>=0;--i)
     A.c[i]=A.b[i+1]*A.c[i+1];   // 每一维的偏移量
    return true;
 }
 ```
#### 元素定位操作
若ap指示的各下标值合法，则求出该元素在A中的相对地址off
```c++
 bool Locate(Array A,va_list ap,int &off) 
 { 
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
```

#### 取元素操作
“...”依次为各维的下标值，若各下标合法，则e被赋值为A的相应的元素值
```c++
 bool Value(ElemType &e,Array A,...) // 在VC++中，“...”之前的形参不能是引用类型
 { 
   va_list ap; // 变长参数表类型，在stdarg.h中
   int off;
   va_start(ap,A); // 变长参数“...”从形参A之后开始
   if(!Locate(A,ap,off)) // 调用Locate()，求得变长参数所指单元的相对地址off
     return false;
   e=*(A.base+off); // 将变长参数所指单元的值赋给e
   return true;
 }
```
#### 存元素操作
“...”依次为各维的下标值，若各下标合法，则将e的值赋给A的指定的元素。
```c++
 bool Assign(Array A,ElemType e,...) 
 {  
   va_list ap; // 变长参数表类型，在stdarg.h中
   int off;
   va_start(ap,e); // 变长参数“...”从形参e之后开始
   if(!Locate(A,ap,off)) // 调用Locate()，求得变长参数所指单元的相对地址off
     return false;
   *(A.base+off)=e; // 将e的值赋给变长参数所指单元
   return true;
 }
```

#### 撤销操作
销毁数组A。
```c++
 void DestroyArray(Array &A)
 { 
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
```
## [源代码下载](/Chapter_06_Arrary/sourcecode)
