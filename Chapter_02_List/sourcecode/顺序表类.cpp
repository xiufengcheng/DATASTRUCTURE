
typedef int ElemType;             // 顺序表中数据元素为int
# include "stdlib.h"              // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"      // 该文件包含标准输入输出流cout和cin及控制符setw()
class  SeqList {                                   // 顺序表类
    private:
       ElemType  *list;                            // 存储数据的指针
       int maxsize;                                // 顺序表的最大容量
       int length;                                 // 当前元素的个数
     public:
       SeqList(int max=0);                          // 构造函数,用于初始化顺序表
       ~ SeqList(void);                             // 析构函数,用于释放分配的空间
	   bool ListEmpty(void);                        // 判断顺序表是否为空
       int ListLength(void) ;                       // 求表长
	   void ListTraverse(void);                     // 输出线性表
	   int LocateElem(int i,ElemType e);            // 查找元素
       void  ListInsert(ElemType &item,int i);      // 插入元素
       ElemType  ListDelete(int i);                 // 删除元素
       ElemType  GetElem(int i);                    // 取表中某个元素值
     };

  SeqList::SeqList(int max)
   {
      maxsize=max;
      length=0;
      list=new  ElemType[maxsize];
    }
  
  SeqList:: ~SeqList(void)
    {
       delete []list;
    }

 bool SeqList::ListEmpty(void)
 {
	if(length==0)return true;
	else return false;
 }

 int SeqList::ListLength(void)
 {
	 return length;
 }

 void SeqList::ListTraverse(void)
 {
	 if(!ListEmpty()) 
	 for(int i=0;i<length;i++)
  	    cout<<setw(4)<<list[i];
	cout<<endl;
 }

 void SeqList::ListInsert(ElemType &item,int i)
 {
 if(length==maxsize)
  {
    cout<<"顺序表已满无法插入！"<<endl;
   exit(0);
  }
 if(i<0||i>length)
  { 
   cout<<" 参数i越界出错！"<<endl;
   exit(0);
  }
 for(int j=length;j>i;j--)  
  list[j]=list[j-1];
  list[i]=item;
  length++;
}

ElemType SeqList::ListDelete(int i)
 {
 if(length==0)
  {
    cout<<"顺序表已空无法删除！"<<endl;
   exit(0);
  }
 if(i<0||i>length-1)
 { 
  cout<<" 参数i越界出错！"<<endl;
  exit(0);
 }
ElemType x=list[i];
for(int j=i;j<length-1;j++)  
  list[j]=list[j+1];
length--;
return x; 
}

ElemType SeqList::GetElem(int i)
{
  if(i<0||i>length-1)
 { 
  cout<<" 参数i越界出错！"<<endl;
  exit(0);
 }
return list[i];
}

void main()
 {
  SeqList mylist(100);
  int i,a[]={6,8,16,2,34,56,7,10,22,45};
  for(i=0;i<10;i++)
   mylist.ListInsert(a[i],i);          // 插入10个元素
  cout<<"删除前的顺序表：";
  mylist.ListTraverse();               // 输出顺序表
  mylist.ListDelete(4);                // 删除第 5个元素
  cout<<"删除后的顺序表：";
  mylist.ListTraverse();               // 输出顺序表
}
   
