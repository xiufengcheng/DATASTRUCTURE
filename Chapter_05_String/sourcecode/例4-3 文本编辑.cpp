# define MAX_LINE 1000           // 允许的最大行数
# define Number 80                // 可由用户定义的块大小
# include "stdlib.h"          // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"         // 该文件包含标准输入输出流cout和cin及控制符setw()

typedef struct Chunk {
  char str[Number];               // 一个结点存放80个字符 
  struct Chunk *next;
}Chunk;  

typedef struct
{
   int num;
   int len;
   Chunk *next;
}headtype;

headtype Head[MAX_LINE];

void InitiHead()
{   // 头结点数组初始化
    int i;
    for(i=0;i<MAX_LINE;i++)
    {
       Head[i].len=0;     // 串长置0
    }
}// InitiHead

int MenuSelect(void)
{  // 选择菜单
 int i;
 i=0; 
 cout<<endl<<"   主菜单";
 cout<<endl<<"1.输入字符串";
 cout<<endl<<"2.删除字符串";
 cout<<endl<<"3.显示字符串";
 cout<<endl<<"4.退出主菜单"<<endl;
 while(i<=0||i>4)
  {
    cout<<endl<<"请选择主菜单：";
    cin>>i;
 }
 return(i);
}// MenuSelect

void EnterData()
{   // 数据输入
    Chunk *p;
    int i,j,m,LineNumber,k;
    char StrBuffer[100];
	InitiHead();       // 初始化头结点数组
    while(1)
    {
      cout<<"请输入行号，退出输入操作请按0：";
      cin>>LineNumber;
      if(LineNumber==0)break;
      if(LineNumber<0||LineNumber>=MAX_LINE)return;
      i=LineNumber;
      Head[i].num=LineNumber;
      Head[i].next=(Chunk *)malloc(sizeof(Chunk));   // 创建一个新行
      p=Head[i].next;
      m=1;                                          // 统计结点个数
      j=-1;                                         // 统计串中字符的个数
      StrBuffer[0]=0;
      k=0;
      do
      {
       j++;
       if(!StrBuffer[k]) 
         {
           cout<<"请输入第"<<LineNumber<<"行字符串，输入@结束：";
           cin>>StrBuffer;
           k=0;
         }
       if(j>=Number*m)   // 字符个数是结点大小的整数倍，产生串中的一个新结点
         {
           m++;             // 结点数增1
           p->next=(Chunk *)malloc(sizeof(Chunk));   
           p=p->next;
         }
         p->str[j%Number]=StrBuffer[k++];   // 将当前字符挎贝到新产生的结点中
      }while(p->str[j%Number]!='@');
      Head[i].len=j;
     }
}// EnterData

void DeleteLine()
{   // 删除行操作
    Chunk *p,*q;
    int i,j,m,LineNumber;
    while(1)
    {
      cout<<"请输入要删除的行号，退出删除操作请按0：";
      cin>>LineNumber;
      if(LineNumber==0)break;
      if(LineNumber<0||LineNumber>=MAX_LINE)  return;
      i=LineNumber;
      p=Head[i].next;          // p指向第i行
      m=0;
      if(Head[i].len>0)
       m=(Head[i].len-1)/Number+1;    // 统计该行结点个数
      for(j=0;j<m;j++)
      {
       q=p->next;
       free(p);
       p=q;
      }
      Head[i].len=0;
      Head[i].num=0;
    }
}// DeleteLine

void List()
{  // 显示操作
     Chunk *p;
     int i,j,m,n;
     for(i=0;i<MAX_LINE;i++)
     {
        if(Head[i].len>0)
        {
          cout<<endl<<Head[i].num<<"  ";
          n=Head[i].len;
          m=1;
          p=Head[i].next;
          for(j=0;j<n;j++)
          if(j>=Number*m)            // j为结点的整数倍
          {
           p=p->next;
           m++;
          }
          else   cout<<p->str[j%Number];
        }
     }
     cout<<endl;
}// List

int main()
 {
   int  choice;
   while(1)
    {
      choice=MenuSelect();
      switch(choice)
         {
          case 1: EnterData();
          break;
          case 2: DeleteLine();
          break;
          case 3: List();
          break;
          case 4: cout<<"成功退出！"<<endl;exit(0);
         }
      }
      return 0;
}
