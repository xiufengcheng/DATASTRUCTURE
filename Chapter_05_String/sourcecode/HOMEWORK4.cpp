typedef int ElemType;     
# include "stdlib.h"     
# include "iomanip.h"    
# include "DSqString"   
# include "SLinkString"



//习题4.1将顺序串S1中的所有值为ch1的字符换成ch2的字符（ch1和ch2均为字符型） 

void Trans_Sq(DSqString &S,char ch1,char ch2)
{
  int i;
  for(i=0;i<S.length;i++)
    if(S.str[i]==ch1)
    S.str[i]=ch2;
}

//习题4.2对顺串删除其值为ch的所有字符
void Delall_Sq(DSqString &S,char ch)
{
  int i=0,j=0,k;
  k=S.length;
  while(i<k)
  {
    if(S.str[i]==ch) 
         for(j=i;j<k;j++)
           {
                  S.str[j]=S.str[j++];
            }
    i++;
  }
  S.length=j;
}

或

void Delall_Sq(DSqString &S,char ch)
{
  int i=0,j=0,k;
  k=S.length;
  while(i<k)
  {
    if(S.str[i]!=ch) 
         S.str[j++]=S.str[i];
    i++;
  }
  S.length=j;
}
 
 
//习题4.3对链串进行同样操作
void Delall_L(SLinkString &S,char ch)
{
  SLinkString p,q;
  p=S;
  while(p->next)
  {
    if(p->next->str==ch)
	{
		 q=p->next;
	     p->next=q->next;
	     free(q);
	    }
	    else p=p->next;
  }
}
 

//习题4.4求串S中一个长度最大的等值子串 （子串中各个字符均相同且长度大于1） 

bool Equalsubstr(DSqString S,DSqString &sub)
{
   int i=0,j,k,head,max,count;
   head=0;                   //head指向当前发现的最长等值子串的串头
   max=1;                    //max记录子串的长度
   for(i=0,j=1; i<S.length&&j<S.length; i=j, j++)
   {
	    count=1;
	    while(S.str[i]==S.str[j]) // 统计当前等值子串的长度
	    {
		   j++;
		   count++;
	    }
	    if(count>max)              //发现新的最长等值子串，更新head和max
	    {
		   head=i;
		   max=count;
	    }
   }
   if(max>1)         //将求得的最长子串存入sub
   {
	   if(!(sub.str=(char *)malloc(i*sizeof(char))))  // 给串sub申请空间 
			return false;                
	   for(k=0;k<max;k++)
		   sub.str[k]=S.str[k+head];
	   sub.length=max;
	   return true;
   }
   else return false;
}



//习题4.5 顺串中第i个字符到第j个字符之间的字符用顺串T代替 

bool Replacestr_Sq(DSqString &S,int i,int j,DSqString T)
{
   int k,disc;  //disk表示从i到j的长度
   
   if(i<0||i>S.length||j<0||j>S.length||i==j)  return false;
   
   disc=j-i-1;
   if(T.length<disc)//如果T短于disc
     {
         for(k=j;k<S.length;k++)
	   S.str[k-disc+T.length] = S.str[k]; //j后面的元素整体前移
      }
   else  if(T.length>disc)//如果T长于disc
	      {
    if(!(S.str=(char )realloc(S.str,(S.length+T.length-disc)*sizeof(char))))
			    return false;       
             for(k=S.length-1;k>=j;k--)
	          S.str[k+T.length-disc]=S.str[k]; //k后面的元素整体后移
		  }

    for(k=0;k<T.length;k++)
	   S.str[i+k+1]=T.str[k];//T插入。
	S.length=S.length+T.length-disc;
    return true;
}


//习题4.6 单链串做上题。

bool Replacestr_L(SLinkString &S,int i,int j,SLinkString T)
{
   int k;
   SLinkString p,q,r,h;
   if(i<0||j<0||i==j)  return false;
   q=p=S;
   k=0;                        
   while(p->next&&k<i)          // 寻找第i个结点 
   { 
   p=p->next; 
	    k++; 
   }   
   if(k!=i)   return false;  
   k=0;
   while(q->next&&k<j)         // 寻找第j个结点 
   { 
	    q=q->next; 
	    k++; 
   }  
   if(k!=j)   return false;  
  
   r=T->next;
   while(r->next)             // r指向串T的表尾
     r=r->next;
   h=p->next;
   p->next=T->next;           // 删除第i到第j个结点,并插入串T 
   free(T);
   r->next=q;
   while(h!=q&&h->next!=q)    // 释放空间
   {
	     r=h;
      h=h->next;
      free(r);  
   }
   return true;
}



//4.7通配符？ 顺串
bool pattern_index(DSqString S,DSqString T,int &pos)
{  
   int i=0,j=0;                       // i和j分别扫描主串S和子串T
   while(i<S.length&&j<T.length)      
   { 

if(S.str[i]==T.str[j]||T.str[j]=='?')// 对应字符相同，继续比较下一个字符
    { i++;    j++;}

    else                           // 主串指针回溯重新开始下一次匹配
    { i=i-j+1;
      j=0;
    }
   }
   if(j==T.length)  { pos=i-T.length; return true;  }
   else return false;
}// Index_Sq

4.14 顺串，从串S中删除

//4.13
void Creat(LinkList &head )
{
  SqQueue Q[10];
  LinkList p,q;
  int i,j,n,a,x;
  for(i=0;i<10;i++)
	 InitQueue_Sq(Q[i]);
  cout<<"请输入数据的个数：";
  cin>>n;
  cout<<"请输入"<<n<<"个10以内的整数：";
  for(i=0;i<n;i++)
  {
	  cin>>a;
    for(j=0;j<10;j++)
	  if(a==j) EnQueue_Sq(Q[j],a);
  }
  head=(LinkList)malloc(sizeof(LNode));    
  q=head;   
  for(i=0;i<10;i++)
    while(!QueueEmpty_Sq(Q[i]))
	   {
       DeQueue_Sq(Q[i],x);
       p=(LinkList)malloc(sizeof(LNode)); 
       p->data=x;  
       q->next=p;  
       q=p;     
} 
  q->next=NULL; 
}

void Print(LinkList head)
{
 LinkList p=head->next;
 while(p)
  {  cout<<setw(6)<<p->data;
     p=p->next;
  }
cout<<endl;
}



void main()
{ int num,dec;              // num存放十进制数，dec存放进制
  cout<<"输入一个十进制数：";
  cin>>num;
  cout<<"输入要转换的进制：";
cin>>dec;  
cout<<"转换后的"<<dec<<"进制数为："; 
  TransFrom(num,dec);                 // 调用数制转换函数
}	