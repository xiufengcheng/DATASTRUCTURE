typedef int ElemType;      // 顺序表中元素类型为int
#include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
#include "iomanip.h"      // 该文件包含标准输入输出流cout和cin及控制符setw()
#include "LinkList.h"       // 该文件中包含链表数据对象的描述及相关操作
#include "SqList.h"       // 该文件中包含链表数据对象的描述及相关操作


//已知非空单链表第一个结点由head指出，请写一算法，交换p所指结点与其下一个结点在链表中的位置
void Reverse(LinkList &L, LinkList p)
{
 LinkList q,r;
 q = L;
 r = p->next;
 while(q->next!=NULL&&q->next->data!=p->data)
 q = q->next;    //这样q指向了p之前的一个节点
  
 if(r)
	{
	  q->next = p->next;
	  p->next = r->next;
	  r->next = p;
	     
	} 
 
}

//习题2.1
//顺序表L有序递增，将数据元素x插入到L的某位置，以保持有序性 
void SLOrderInsert(SqList &L, ElemType e)
{   
    int i;
    L.length = ListLength_Sq(L);
	if(e<L.elem[0]) {ListInsert_Sq(L,0,e);}
	else
	{
		for(i=0; i<=L.length-1; i++)
    	{	 
    		 if(e <=L.elem[i])
    		 {
			 ListInsert_Sq(L,i,e);
    		 break;
			 }
    	}
	}
  	
}

//习题2.2
//顺序表的逆置 
void Converse_Sq(SqList &L)
{
   int mid, i;
   ElemType x;
   mid=L.length/2;
   for(i=0;i<mid;i++)
   {
      x=L.elem[i];
      L.elem[i]=L.elem[L.length-1-i];
      L.elem[L.length-1-i]=x;
   }
}


//习题2.3
//数组前后两段互换 
void Converse2_Sq(ElemType a[],int low, int high)
 { 
   int n,i;
   ElemType x;
   n=(high-low+1)/2;
   for(i=0;i<n;i++)
   {
     x=a[low+i];
     a[low+i]=a[high-i];
     a[high-i]=x;
    }
  }

void Exchange_Sq(ElemType a[],int m,int n)
 {
    Converse2_Sq(a,0,m+n-1); //先逆置a整体 
    Converse2_Sq(a,0,n-1);   //再逆置a前段 
    Converse2_Sq(a,n,n+m-1); //再逆置a后段 
 }


 
//习题2.4
//删除顺序表值在(s,t)范围内的所有元素 
void Delete_Section(SqList &L,ElemType s,ElemType t)
{
   ElemType e;
   int i,k;
   for(i=0;i<L.length;i++)
    if(L.elem[i]>=s&&L.elem[i]<=t)
      ListDelete_Sq(L,i,e);
 }


//习题2.5
//单链表的逆置 
void Inverse_L(LinkList &L)
 { 
   LinkList p, q;
   p=L->next;    
   L->next=NULL;//将头砍断 
 
   while(p)    //当p有值 
   {
     q=p;
     p=p->next;
     q->next=L->next;
	 L->next=q;
   }
 }
 
 
 void Inverse_L2(LinkList &L)
 {
    LinkList p, q, k;
    p = L->next;
    L->next=NULL;   //将头砍断 
    k = p->next;
    p->next = NULL; //设置尾节点

    while (k)  //k相当于始终领先p一步  
	{          
 	  q = p;
 	  p = k;
 	  k = k->next;
      p->next = q;//将每个箭头逆置  
	}
	L->next = p;
 }


//习题2.6
//单链表的递增排序 
 void LinkListSort(LinkList &L)
{
  LinkList curr,pre,p,q;
  p=L->next;
  L->next=NULL;
  
  while(p)
  {
    curr=L->next;
    pre=L;
    while(curr&&curr->data<=p->data)
    {//快速排序 
      pre=curr;
      curr=curr->next;
    }
    q=p;
    p=p->next;
    q->next=pre->next;
    pre->next=q;
  }
}

// 算法2.7
// 不带头结点链表插入和删除
bool NListInsert_L( LinkList &L, int i, ElemType e) 
{    //在不带有头结点的单链表L中的第i个结点之前插入元素e
  LinkList p,newElem;
  int j=0;
  p=L;  
  while(p->next&&j<i-1)  { p=p->next; j++; }  // 寻找第i-1个结点,并让p指向此结点
  if(j!=i-1&&i!=1)   return false;         // i的位置不合理
  if((newElem=(LNode *)malloc(sizeof(LNode)))==NULL) exit(1); // 存储分配失败
  newElem->data=e;  
  if(i==1)                                 // 插入在表头
  {
    newElem->next=L;
    L=newElem;
  }
  else
  {  newElem->next=p->next;  p->next=newElem;   }     // 插入新结点
    return true;
 }


bool NListDelete_L( LinkList &L, int i) 
{    // 删除不带有头结点的单链表L中的第i个结点，并让e返回其值
  ElemType e;
  LinkList p,q;
  int j;
  p=L;  j=0;
  while(p->next&&p->next->next&&j<i-1){ p=p->next; j++; }  
  // 寻找第i-1个结点,并让p指向此结点
  if(j!=i-1&&i!=1)   return false;         // i的位置不合理
  if(i==1)                                 // 删除表头结点
   {
     q=p;
     L=L->next;
   }
   else
   {
    q=p->next;                            // q指向其后继
    p->next=q->next;                      // 删除q所指结点
    e=q->data;    free(q);
   }
   return true;
 }

//算法2.8
//双向链表的求数据元素操作和取数据元素操作

typedef struct DuNode  {
 ElemType data;
struct  DuNode *prior;
struct  DuNode *next;
}DuLNode,*DuLinkList;
int ListLength_DuL(DuLinkList &L)
{   // 统计带头结点的双向循环链表L
  DuLinkList p=L->next;
  int num=0;
  while(p!=L)
  {
	  num++;
	  p=p->next;
  }
  return num;
}

bool ListGet_DuL(DuLinkList &L, int i, ElemType &e)
{   // 在带有头结点的双向循环链表L中的取第i个结点，并让e返回其值
  DuLinkList p;
  int j;
  p=L->next;  j=1;
  while(p->next!=L&&j<i){ p=p->next; j++; }
// 寻找第i个结点,并让p指向此结点
   if(j!=i)   return false;                  // i的位置不合理
   e=p->data;                                // 被取元素的值赋给e
  return true;
 }

 
//算法2.9
//判断单链表Lb是否包含La 
 bool IsSubSet(LinkList La, LinkList Lb)
{
  bool  ok1,ok2;
  LinkList p1,p2;
  ok1=true;
  p1=La->next;
  while(ok1&&p1)
  {
    ok2=false;
    p2=Lb->next;
    while(!ok2&& p2)
	   {
      if(p2->data==p1->data)   ok2=true;
      else  p2=p2->next;
    }
    ok1=ok2;
    p1=p1->next;
    }
    return   ok1;
}

//算法2.10
//La,Lb有序递增，合并La,Lb成Lc，Lc递减有序，相同的值只保留一个 
void merge_L(LinkList La, LinkList Lb,  LinkList &Lc)
{
  LinkList pa,qa,pb,qb;
  Lc=La; pa=La->next; Lc->next=NULL;
  pb=Lb->next; free(Lb);
  while(pa&&pb)
  {
    if(pa->data<pb->data)
    {
      qa=pa;
      pa=pa->next;
	      qa->next=Lc->next;
      Lc->next=qa;
}
    else 
	   if(pa->data>pb->data)
	   {
        qb=pb;
        pb=pb->next;
        qb->next=Lc->next;
        Lc->next=qb;
	   }
	   else 
	   {
       qa=pa;
	      qb=pb;
       pa=pa->next;
	      pb=pb->next;
	      qa->next=Lc->next;
       Lc->next=qa;
	      free(qb);
	   }
   }
   while(pa)
   {
     qa=pa;
     pa=pa->next;
     qa->next=Lc->next;
     Lc->next=qa;
   }
   while(pb)
   {
     qb=pb;
     pb=pb->next;
     qb->next=Lc->next;
     Lc->next=qb;
   }
}
 
//算法2.11
//求两个单链表的交集
void Interaction(LinkList La,LinkList Lb,LinkList &Lc)
 {
   LinkList pa,pb,pc;
   LinkListSort(La);
   LinkListSort(Lb);    //调用第6题的排序函数
   pa=La->next;
   pb=Lb->next;
   Lc=(LinkList)malloc(sizeof(LNode));
   Lc->next=NULL;
   while(pa && pb)
    if(pa->data < pb->data)
      pa = pa->next;
    else  if(pa->data>pb->data)
            pb=pb->next;
          else
          {
            pc=(LinkList)malloc(sizeof(LNode));
            pc->data=pa->data;
            pc->next=Lc->next;
            Lc->next=pc;
            pa=pa->next;
            pb=pb->next;
          }
}

void Interaction2(LinkList La,LinkList Lb,LinkList &Lc)
{//初始化结果链表为空，遍历链表1，在链表2中查找它的每一元素
 //如果链表2中也有这个元素，则将该元素插入到结果链表中。
  LinkList pa,pb,pc1,pc2;
  pa=La->next;
  pb=Lb->next;
  pc2 = Lc; //pc2始终指向尾节点，用尾插法 
  while(pa->data)  
    {  
        while(pb->data)
		{
		  if(pa->data == pb->data)//如果找到相同元素 
		  pc1=(LinkList)malloc(sizeof(LNode));//分配一个pc1 
		  pc1->data = pa->data; 
		  pc2->next= pc1; 
		  pc2 = pc1;
		  pb = pb->next;
		}    
        pa = pa->next;  
    }  
}
//算法2.12
//L单链表不带头结点，每个节点存储一个字符（英文、数字或中文）
//生成三个单链表分别表示每种字符
void  Decompose(LinkList L,LinkList &ha,LinkList &hb,LinkList &hc)
 {
   LinkList p,q;
   p=L;
   ha=(LNode *)malloc(sizeof(LNode));
   hb=(LNode *)malloc(sizeof(LNode));
   hc=(LNode *)malloc(sizeof(LNode));
   ha->next=ha;
   hb->next=hb;
   hc->next=hc;
   while(p)
   {
     if('A'<=p->data && p->data<='Z'||'a'<=p->data && p->data<='z')
     {
       q=p; p=p->next;
       q->next=ha->next;
       ha->next=q;
     }
     else if('0'<=p->data && p->data<='9')
     {
       q=p; p=p->next;
       q->next=hb->next;
       hb->next=q;
     }
     else
     {
       q=p; p=p->next;
       q->next=hc->next;
       hc->next=q;
     }
    }
 }

//算法2.13
//删除带头结点单链表L中值相同的多余节点(trim) 
//遍历链表，对每一个链表中的元素，看其后面的所有元素是否与其相等
//如果相等，则删除该元素。 
 void Trim_L(LinkList L)
{  
  LinkList p,q,s;
  p=L->next;
  while(p->next&&p->next->next)  
   {
     q=p;
     while(q->next)
      { 
	     if(p->data==q->next->data)
           { //删除节点 
             s=q->next;
             q->next=s->next;
             free(s);
           }
         else  q=q->next; //让p加一 
      } 
	  p=p->next;
   }
}

//算法2.14
//统计带头结点单链表中相同节点个数
int CountNode(LinkList head,ElemType x)
{
  int sum=0;
  LinkList p=head->next;
  while(p)
  {  
    if(p->data==x) 
    sum++;
    p=p->next;
  }
  return sum;
}


//算法2.15
//带头结点单链表L拆成俩(La和Lb)，分别装奇数和偶数 
void RetNode(LinkList L, LinkList &La, LinkList &Lb)
{
   LinkList p,pa,pb;
   p=L->next;
   pa=La=(LNode *)malloc(sizeof(LNode));
   pb=Lb=(LNode *)malloc(sizeof(LNode));
   while(p)
   {
     if(p->data%2) 
     {
       pa->next=p; p=p->next;
       pa=pa->next;
     }
     else 
    {
       pb->next=p; p=p->next;
       pb=pb->next;
     }
    }
    pa->next=NULL;
	pb->next=NULL;
}

 
int main()
 {
 	ElemType la[] = {2,3,1,9,3,6};
    ElemType lb[] = {2,4,5,6,8};
    int m,n;
    //顺序表的创建 
    SqList sqlistA, sqlistB;
    InitList_Sq(sqlistA,100,50);   
    for(m=0;m<5;m++)
  	ListInsert_Sq(sqlistA, m, la[m]);
    
	InitList_Sq(sqlistB,100,50);   
    for(n=0;n<5;n++)
  	ListInsert_Sq(sqlistB, n, la[n]);
   
    //cout<<"操作前的sqlistA为：";
    //ListTraverse_Sq(sqlistA); 

    
    //链表的创建 
    LinkList linklistA, linklistB,linklistC;
    InitList_L(linklistA);
    InitList_L(linklistB);
    CreateList_L_Rear(linklistA, la, 6);
    CreateList_L_Rear(linklistB, lb, 5);
    
    cout<<"操作前的linklistA为：";
    ListTraverse_L(linklistA); 
    cout<<"操作前的linklistB为：";
    ListTraverse_L(linklistB); 
 

    /*****************************/
    //SLOrderInsert(Lista,4);      		//习题2.1测试
    //Converse_Sq(Lista);         		 //习题2.2测试
    //Exchange_Sq(la,5,5); for(int i=0;i<10;i++) cout<<setw(6)<<la[i];//习题2.3测试 
    //Delete_Section(Lista,2,5);  		 //习题2.4测试 
    //Inverse_L(linklistA);        		//习题2.5测试
	//Inverse_L2(linklistA);      		 //习题2.5第二种算法
    //LinkListSort(linklistA);    		 //习题2.6测试
	//NListInsert_L(linklistA,3, 15); 		//习题2.7测试
	//NListDelete_L(linklistA,4); 		//习题2.7测试
	//NListDelete_L(linklistA,4); 		//习题2.7测试
	//Interaction(linklistA,linklistB,linklistC);//习题2.11测试
	//Interaction2(linklistA,linklistB,linklistC);//习题2.11第二种算法 
	//Trim_L(linklistA);//习题2.13测试

	/****************************/
    cout<<"操作后的linklistA表为："<<endl;
    //ListTraverse_L(linklistA); 
    ListTraverse_L(linklistA); 
	return 0;
}
