# 线性表(linear list，简称list)

### 定义
- 是**n(n≥0)**个**相同类型**的**数据元素**构成的**有限**序列。

### 数学表示
- (a1，a2，…，an)
- 其中，n为线性表的长度，当n=0时，表示线性表是一个空表，即表中不包含任何元素。
- 对任意一对相邻元素<ai,ai+1>（1≤i<n），ai称为ai+1的**前驱**，ai+1称为ai的**后继**
-------------
### 图示
![](/Chapter_02_List/img/0.jpg)

### 注意事项
- 线性表除第一个和最后一个元素之外，每一格数据元素只有一个前驱和一个后继
- 分有序线性表（顺序表）和无序线性表（链表），有序线性表的元素按照值的递增顺序排列；无序线性表在元素的值与位置之间没有特殊的联系
- 元素含义无所谓，可以指任何东西，但元素类型必须相同

------------------
### 抽象数据类型ADT
```C
ADT List
{
    Data:
    Operation:
        InitList(&L)
        Create List(&L)
        ListEmpty(L)
        ListLength(L)
        LocateElem(L,e)
        PriorElem(L,cur_e,&pre_e)
        NextElem(L,cur_e,&pre_e) 
        ListInsert(&L,i,e)
        ListDelete(&L,i,&e)
        GetElem(L,i,&e)
        ListTraverse(L)
        DestroyList(&L)
    }//ADT List
```
------------------
# 顺序表

### 定义
- 顺序存储结构：用一组地址连续的存储单元依次存储**数据结构**(在这里是线性表)里各个元素，这种存储结构称为线性表的顺序存储结构。
- 顺序表：按照顺序存储结构存储的线性表。

### 逻辑图示
![](/Chapter_02_List/img/1.jpg)

### 数学表示
- 同线性表
- 求址
    - 每个元素占用k个存储单元，则<br>
    LOC(ai)= LOC(a1)+(i-1)*k   (1≤i ≤n)<br>
    LOC(ai+1)= LOC(ai)+k       (1≤i ≤n)<br>
------------------
### 注意事项
- 访问顺序表中任意元素的时间都相等，具有这一特点的存储结构称为**随机存取结构**。


### 顺序表静态存储数据结构
```C
[in SqList.h]
# define LIST_INIT_SIZE 100    //(默认)最大存储容量
typedef struct {
    ElemType  elem [LIST_INIT_SIZE];   //存储数据元素的一维数组 
    int length;                        //线性表的当前长度
} SqList;
```
------------------
### 顺序表动态存储数据结构
```C
[in SqList.h]
# define LISTINCREMENT  10          //(默认)增补空间量
typedef struct {
    ElemType  *elem;           // 存储数据元素的一维数组
    int length;                // 线性表的当前长度
    int listsize;              // 当前分配的数组容量（以ElemType为单位）
    int incrementsize;        // 增补空间量（以ElemType为单位）
} SqList;
```

------------------
### 顺序表初始化操作
```C
[in SqList.h]
void InitList_Sq( SqList &L, int maxsize=LIST_INIT_SIZE, int incresize=LISTINCREMENT ) // 构造一个最大容量为maxsize的顺序表 L
{      
     L.elem=(ElemType *)malloc(maxsize*sizeof(ElemType)); // 分配一个最大容量为maxsize的数组空间
     if(!L.elem)  exit(1);           // 存储分配失败
      L.length=0;                    // 顺序表中当前所含元素个数为 0
      L.listsize=maxsize;            // 该顺序表可以容纳maxsize个数据元素
      L.incrementsize=incresize;     // 需要时可扩容incresize个元素空间
}// InitList_Sq
```
------------------
### 顺序表求表长操作
```C
[in SqList.h]
int ListLength_Sq(SqList L)
{ 
    return L.length;
}// ListLength_Sq
```
------------------
### 判断顺序表是否为空
```C
[in SqList.h]
bool ListEmpty_Sq(SqList L)
{
    if(L.length==0)
    return true;
    else return false;
}
```
------------------
### 顺序表定位元素(返回与e值相等的元素下标)
```C
[in SqList.h]
int LocateElem_Sq( SqList L, ElemType e) 
{  
    for(int i=0;i<L. length;i++)
    if(L.elem[i]==e)  return i;   // 找到满足判定的数据元素为第 i 个元素
    return -1;                     // 该线性表中不存在满足判定的数据元素
 }//LocateElem_Sq
```

------------------
### 顺序表前插
在顺序表L的第i个元素之**前**插入新的元素e，若表中当前容量不足，则按预定义的增量扩容
```C
[in SqList.h]
bool ListInsert_Sq(SqList &L, int i, ElemType e)
{   
    int j;
        if(i<0||i>L.length)  return false;  // i值不合法
        if(L.length>=L.listsize)           // 当前存储空间已满，增补空间
        {                   
            L.elem=(ElemType *)realloc(L.elem,(L.listsize+L.incrementsize)*sizeof(ElemType));
            if(!L.elem) exit(1);                   // 存储分配失败
            L.listsize+=L.incrementsize;           // 当前存储容量增加
        }
    for(j=L.length;j>i;j--)                // 被插入元素之后的元素左移
        L.elem[j]=L.elem[j-1];             
        
    L.elem[i]=e;                           // 插入元素e
    L.length++;                            // 表长增1
    return true;   
}// ListInsert_Sq
```
------------------
### 顺序表后插
在顺序表L的第i个元素之**后**插入新的元素e，若表中当前容量不足，则按预定义的增量扩容


------------------
### 顺序表尾插
在顺序表L的最后一个元素之**后**插入新的元素e，若表中当前容量不足，则按预定义的增量扩容



------------------
### 顺序表查插
在递增有序顺序表L中查找插入新的元素e，首先需要找到在哪插
```C
[in SqList.h]
bool ListInsert_Sq_1(SqList &L, ElemType e)
{   
// 若表中当前容量不足，则按预定义的增量扩容
      int i,j;
      if(L.length>=L.listsize)  {          // 当前存储空间已满，增补空间
          L.elem=(ElemType *)realloc(L.elem,(L.listsize+L.incrementsize)*sizeof(ElemType));
          if(!L.elem) exit(1);                   // 存储分配失败
          L.listsize+=L.incrementsize;           // 当前存储容量增加
        }
      for(i=0;i<L.length&&e>L.elem[i];i++); //让下标移动到应该插入的位置之前
	  for(j=L.length;j>i;j--)                // 被插入元素之后的元素左移
        L.elem[j]=L.elem[j-1];
      L.elem[i]=e;                           // 插入元素e
      L.length++;                            // 表长增1
      return true;   
}// ListInsert_Sq
```

------------------
### 顺序表删除元素操作
在顺序表L中删除第i个元素，并用e返回其值
```C++
[in SqList.h]
bool ListDelete_Sq(SqList &L,int i, ElemType &e)
{      
      int  j;
if(i<0||i>L.length) return false;            // i值不合法
if(L.length<=0)  return false;                // 表空无数据元素可删
     e=L.elem[i];                                  // 被删除元素的值赋给e
      for(j=i+1;j<=L.length-1;j++)                 // 被删除元素之后的元素前移
        L.elem [j-1]=L.elem [j];
      L.length--;                                  // 表长减1
      return true;    
}// ListDelete_Sq
```

------------------
### 顺序表取元素操作
取出顺序表L中第i个元素，并用e返回其值。
```C++
[in SqList.h]
bool GetElem_Sq(SqList L,int i, ElemType &e)
{     // 取出顺序表L中第i个元素，并用e返回其值。
     if(i<0||i>L.length) return false;            // i值不合法
if(L.length<=0)  return false;               // 表空无数据元素可取
e=L.elem[i];                                 // 被取元素的值赋给e
      return true;    
}// GetElem_Sq  
```
------------------
### 顺序表遍历输出各元素
```C++
[in SqList.h]
void ListTraverse_Sq(SqList L)
{
int i;
for(i=0;i<L.length;i++)
      cout<<setw(6)<<L.elem[i];
cout<<endl;
}// ListTraverse_Sq
```
------------------
### 删除顺序表
```C++
[in SqList.h]
void DestroyList_Sq(SqList &L)
{       // 释放顺序表L所占存储空间
      free(L.elem);
	  L.elem=NULL;
      L.listsize=0;
      L.length=0;
}// DestroyList_Sq
```
------------------
### 顺序表测试
```C++
[in SqListTest.cpp]
typedef int ElemType;    // 顺序表中元素类型为int
# include "stdlib.h"     // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"    // 该文件包含标准输入输出流cout和cin及控制符setw()等函数 
# include "SqList.h"     // 该文件中包含链表数据对象的描述及相关操作

int main()
{
  SqList mylist;
  int i,j,temp,forLocate,forGet,forInsert,forDelete;
  
  InitList_Sq(mylist, 50, 10);  
  for(i=0,j=1;i<10;i++,j++)
  if(!ListInsert_Sq(mylist,i, 2*j))
  {cout<<"错误!"<<endl; return 0;}
  cout<<"我创建了一个顺序表，表长为："<<ListLength_Sq(mylist)<<endl;
  cout<<endl<<"表中的元素依次为："<<endl;
  ListTraverse_Sq(mylist);
  
  
  cout<<endl<<"***现在执行元素定位操作,请输入需要查找的元素：***"<<endl;
  cin>>forLocate;
  j=LocateElem_Sq(mylist, forLocate);
  if(j!=-1) cout<<"找到了，它是第"<<j+1<<"个元素。"<<endl;
  else cout<<"定位失败！"<<endl;
  
  
  cout<<endl<<"***现在执行取元素操作,您要找第几个元素？请输入：***"<<endl;
  cin>>forGet;
  if(GetElem_Sq(mylist,forGet-1,temp))  
  cout<<"第"<<forGet<<"个元素的值是:"<<temp<<endl;
  else cout<<"取元素失败！"<<endl;
 
 
  cout<<endl<<"***现在执行插入操作,您要将什么元素插入顺序表？请输入：***"<<endl;
  cin>>forInsert;
  cout<<"***插入到第几个位置？***"<<endl;
  cin>>temp;
  if(!ListInsert_Sq(mylist, temp-1, forInsert))
  {cout<<"插入!"<<endl; return 0;} 
  else cout<<"插入成功，插入后的顺序表为："<<endl;
  ListTraverse_Sq(mylist);
  
 
  cout<<endl<<"***现在执行删除操作,您要删除第几个元素？请输入：***"<<endl;
  cin>>forDelete;
  if(!ListDelete_Sq(mylist,forDelete-1,temp))
  {cout<<"删除失败!"<<endl; return 0;} 
  else cout<<"删除成功，删除后的顺序表为："<<endl;
  ListTraverse_Sq(mylist);
   
  cout<<endl<<"***现在执行撤销操作***"<<endl;
  DestroyList_Sq(mylist);
  cout<<"***顺序表已经销毁！***"<<endl;
  return 0; 
 }
```
------------------

# 链表

## 单链表

### 定义
- 链式存储结构：用一组任意的存储单元存储**数据结构**（这里是线性表)里的各元素(这组存储单元可以是地址连续的，也可以是不连续的)，并且每个存储元素有一个数据域，一个（或多个）指针域，数据域用来存储元素内容，指针域用来反映元素的逻辑关系(前后位置关系)，这种存储方式成为链式存储（也叫非随机存取的存储结构）。
- 链表：按照链式存储结构存储的线性表。
- 单链表：各元素只有一个指针域的链表（只含有一个指针域）
------------------
### 逻辑图示
![](/Chapter_02_List/img/2.jpg)

- 头结点：单链表中第一个结点（上图中的a1之前的结点a0）
- 表头指针：存放单链表中第一个结点的地址。（a0的指针）
- 表尾结点：单链表中最后一个结点，表尾结点的指针域指针为空。（an）
- 开始结点：存放线性表的第一个元素的结点。(a1)

### 数学表示
- 同线性表
- 寻址
  一般用p,q等字母表示操作性指针，假设 p = &ai; ai = p->data = (*p).data, ai的下一个元素的地址 = p -> next = (*p).next
------------------
### 注意事项
- 链表的元素一般称为“结点”。
- 头结点在链表中并不是必须的，仅仅是为了操作上的方便。 
- 结点ai指其数据域为ai的结点，而p结点则指指针p所指向的结点(即其存储位置存在放在p中的结点)
- 单链表的操作
![](/Chapter_02_List/img/3.jpg)

------------------
### 单链表的数据结构
```C++
[in LinkList.h]
typedef struct Node {
    ElemType data;    //数据域
    struct  Node *next;   //指针域
}LNode,*LinkList;                 // LinkList为结构体指针类型
```
------------------

### 单链表的初始化
```C++
[in LinkList.h]
void InitList_L(LinkList &L)
    {  
		L=(LNode *)malloc(sizeof(LNode));  // 申请存放一个结点数据所需要的内在空间
		if(!L)   exit(1);                        // 存储分配失败
        L->next=NULL;                            // 表头结点的指针域置空
	}// InitList_L
```
------------------
### 求单链表的长度
// L为带头结点的链表的头指针，函数返回L所指链表的长度
```C++
[in LinkList.h]
int ListLength_L( LinkList L ) 
	{     
  		LinkList  p;
		int k=0;
		p=L->next;                             // p指向链表中的第一个结点
 		 while(p) 
  		 { k++;  p=p->next; }              // k计非空结点数
         return k;
	}// ListLength_L
```
------------------
### 单链表的查找操作
在L所指的单链表中查找第一个值和e 相等的结点，若存在，则返回其指针；
```C++
[in LinkList.h]
LNode *LocateElem_L( LinkList L,ElemType e) 
	{  
 		 LinkList  p;                           
 		 p=L->next;                               // p指向链表中的第一个结点
  		 while (p&&p->data!=e ) p=p->next;
  		 return p;
	}// LocateElem_L
```
------------------
### 单链表插入元素操作
 在带有头结点的单链表L中的第i个结点之前插入元素e
 ```C++
[in LinkList.h]
bool ListInsert_L( LinkList &L, int i, ElemType e) 
	{   
		LinkList p,s;
  		int j;
  		p=L;  j=0;
  		while(p->next&&j<i-1)  { p=p->next; j++; }   // 寻找第i-1个结点,并让p指向此结点
  		if(j!=i-1)   return false;                   // i的位置不合理
  		if((s=(LNode *)malloc(sizeof(LNode)))==NULL) exit(1);  // 存储分配失败
  		s->data=e;  
  		s->next=p->next;  p->next=s;                  // 插入新结点
  		return true;
 	}// ListInsert_L
```
------------------
### 单链表删除元素操作
 ```C++
[in LinkList.h]
bool ListDelete_L( LinkList &L, int i, ElemType &e) 
	{    // 删除带有头结点的单链表L中的第i个结点，并让e返回其值
		LinkList p,q;
	    int j;
  		p=L;  j=0;
 		while(p->next->next&&j<i-1){ p=p->next; j++; } //寻找第i-1个结点,并让p指向此结点
  		if(j!=i-1)   return false;                     // i的位置不合理
  		q=p->next;                                     // q指向其后继
		p->next=q->next;                               // 删除q所指结点
		e=q->data;    free(q);
  		return true;
 	}// ListDelete_L
```

------------------
### 单链表取元素操作
 ```C++
[in LinkList.h]
取出单链表L中第i个元素，并用e返回其值
bool GetElem_L(LinkList L,int i, ElemType &e)
	{    // 取出单链表L中第i个元素，并用e返回其值
		LinkList p;
  		int j;
  		p=L;  j=0;
		while(p->next&&j<i){ p=p->next; j++; }  // 寻找第i个结点,并让p指向此结点
 		 if(j!=i)   return false;                      // i的位置不合理
  		 e=p->data;                                     // 被取元素的值赋给e
 		 return true;
    }// GetElem_L
```
------------------
### 创建单链表（尾插）
已知一维数组A[n]中存有线性表的数据元素，利用尾插法创建单链表L
 ```C++
[in LinkList.h]
void CreateList_L_Rear(LinkList &L,ElemType a[],int n ) 
	{   // 已知一维数组A[n]中存有线性表的数据元素，利用尾插法创建单链表L
   		LinkList p,q;   int i;
	  	L=(LinkList)malloc(sizeof(LNode));    // 创建立头结点
		q=L;                                // q始终指向尾结点，开始时尾结点也是头结点
		for(i=0;i<n;i++) 
    	{   p=(LinkList)malloc(sizeof(LNode));          // 创建新结点
            p->data=a[i];                               // 赋元素值
            q->next=p;                                  // 插入在尾结点之后
            q=p;                                         // q指向新的表尾
 	    }
   		q->next=NULL;                                    // 表尾结点next域置空
     }// CreateList_L_Rear
```
------------------
### 创建单链表（头插）
已知一维数组A[n]中存有线性表的数据元素，利用头插法创建单链表L
 ```C++
[in LinkList.h]
void CreateList_L_Front(LinkList &L,ElemType a[],int n ) 
	{    
   		LinkList p;   int i;
		L=(LinkList)malloc(sizeof(LNode));              //创建立头结点
		L->next=NULL;                               
		for(i=n-1;i>=0;i--)   
		{    p=(LinkList)malloc(sizeof(LNode));           //创建新结点
		     p->data=a[i];                                // 赋元素值
        	 p->next=L->next;                          // 插入在头结点和第一个结点之间
       	     L->next=p;                                         
        }
	}// CreateList_L_Front
 ```
------------------
### 遍历输出单链表各元素数据
 ```C++
[in LinkList.h]
 void ListTraverse_L(LinkList L)
	{
		 LinkList p=L->next;
 		 while(p)
  	  {  cout<< setw(6)<<p->data;
         p=p->next;
      }
		cout<<endl;
	}// ListTraverse_L
------------------
```
### 删除单链表
 ```C++
[in LinkList.h]
void DestroyList_L(LinkList &L )
	{
  		LinkList p,p1;
 		 p=L;
  		while(p) 
  		{   p1=p;
    		p=p->next;
    		free(p1);
        }
  			 L=NULL;
    }// DestroyList_L
```
------------------

## [源文件下载](\Chapter_02_List\sourcecode)