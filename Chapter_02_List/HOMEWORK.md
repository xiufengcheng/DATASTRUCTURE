
## 第二章程序设计题
抢答要求，参考[如何使用git](https://github.com/xiufengcheng/DATASTRUCTURE/tree/master/tools_download/GitHub%20%E6%95%99%E7%A8%8B),提交pull request. 老师择机合并你的答案。

## 算法设计题2.1

```c++
bool ListInsert_Sq_2_1(SqList &L, ElemType e)
{  
    int i,j;
    if(L.length>=L.listsize)  
    {                  
	L.elem=(ElemType *)realloc(L.elem,(L.listsize+L.incrementsize)*sizeof(ElemType));
	if(!L.elem) exit(1);                  
	L.listsize+=L.incrementsize;           
    }
    i=0;
    while(i<L.length&&L.elem[i]<e)          
	i++;
    for(j=L.length;j>i;j--)               
	L.elem[j]=L.elem[j-1];
    L.elem[i]=e;                           
    L.length++;                           
    return true;   
}
```

提交者:张孜铭

----------------


## 算法设计题2.2

```c++
void ListReverse(SqList &L)
 {
     int i,temp;
     for (i=0; i<L.length/2; ++i)
     {
         temp=L.elem[i];
         L.elem[i]=L.elem[L.length-i-1];
         L.elem[L.length-i-1]=L.elem[i];
     }
}
```

提交者:张孜铭

----------------



## 算法设计题2.3

```c++
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
    Converse2_Sq(a,0,m+n-1);
    Converse2_Sq(a,0,n-1);
    Converse2_Sq(a,n,n+m-1);
 }
```

提交者:

----------------



## 算法设计题2.4
```c++
void Delete_Sq(SqList &L,ElemType s,ElemType t)
{
   int i,k;
   for(i=0;i<L.length;i++)
    if(L.elem[i]>=s&&L.elem[i]<=t)
      L.elem[i]=0;
   for(i=L.length-1;i>=0;i--)
    if(L.elem[i]==0)
    {
      for(k=i;k<=(L.length-2);k++)
         L.elem[k]= L.elem[k+1];
      L.length--;
    }
 }

```

提交者:

----------------



## 算法设计题2.5

```c++
void ListReverse_L(LinkList &L)  
{   
    LNode* p,q;
    p=L->next->next;
    L->next->next=NULL;
    while(p)  
    {  
        q=p->next;  
        p->next=L->next;  
        L->next=p;  
        p=q;
    }  
}  
```

提交者:张孜铭

----------------



## 算法设计题2.6
```c++
void LinListSort(LinkList &head)
{
  LinkList curr,pre,p,q;
  p=head->next;
  head->next=NULL;
  
  while(p)
  {
    curr=head->next;
    pre=head;
    while(curr&& curr->data<=p->data)
    {
      pre=curr;
      curr=curr->next;
    }
    q=p;
    p=p->next;
    q->next=pre->next;
    pre->next=q;
    }
}
```
提交者:

----------------



## 算法设计题2.7

```c++
bool ListInsert_L_2_7(LinkList &L,int i,ElemType e)
 { 
     LinkList p,q;
     int j; 
     p=L;
     j=1;
     if(i<1) 
         return false;
     q=(LinkList)malloc(sizeof(LNode)); 
     q->data=e; 
     else if(i==1)
     { 
         q->next=L; 
         L=q; 
     }
     else
     { 
         while(p&&j<i-1) 
         { 
             j++; 
             p=p->next; 
         }
     if(!p) 
         return false; 
     q->next=p->next;
     p->next=q; 
   }
   return true; 
 }


 bool ListDelete_L_2_7(LinkList &L,int i,ElemType &e)
 { 
     LinkList p,q;
     int j; 
     p=L;
     j=1;
     if(!L) 
         return false; 
     else if(i==1) 
     { 
         L=p->next; 
         e=p->data; 
         free(p);
     }
     else
     { 
	while(p->next&&j<i-1) 
	{ 
		j++; 
		p=p->next; 
	}
	 if(!p->next||j>i-1) 
	     return false; 
	 q=p->next; 
	 p->next=q->next; 
	 e=q->data; 
	 free(q);
    }   
   return true; 
 }
 ```

提交者:张孜铭

----------------



## 算法设计题2.8
```c++
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
  while(p->next!=L&&j<i)
    { p=p->next; j++; }
// 寻找第i个结点,并让p指向此结点
   if(j!=i)   return false;                  // i的位置不合理
   e=p->data;                                // 被取元素的值赋给e
  return true;
 }
```
提交者:

----------------


## 算法设计题2.9
```c++
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
```

提交者:

----------------

## 算法设计题2.10

```c++
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
```
提交者:

----------------



## 算法设计题2.11
```c++
void Interaction(LinkList ha,LinkList hb,LinkList &hc)
 {
   LinkList pa,pb,pc;
   LinListSort(ha);
   LinListSort(hb);    //调用第6题的排序函数
   pa=ha->next;
   pb=hb->next;
   hc=(LinkList)malloc(sizeof(LNode));
   hc->next=NULL;
   while(pa && pb)
    if(pa->data<pb->data)
      pa=pa->next;
    else  if(pa->data>pb->data)
            pb=pb->next;
          else
		     {
            pc=(LinkList)malloc(sizeof(LNode));
            pc->data=pa->data;
            pc->next=hc->next;
            hc->next=pc;
            pa=pa->next;
            pb=pb->next;
          }
}
```
提交者:

----------------



## 算法设计题2.12
```c++
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
```
提交者:

----------------



## 算法设计题2.13
```c++
void Delete_L(LinkList L)
{  // 删除带头结点的单链表L中值相同的多余结点
  LinkList p,q,s;
  p=L->next;
  while(p->next&&p->next->next)
   {
     q=p;
     while(q->next)
      if(p->data==q->next->data)
      {
        s=q->next;
        q->next=s->next;
        free(s);
      }
      else  q=q->next;
      p=p->next;
     }
}
```
提交者:

----------------

## 算法设计题2.14
```c++
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
```
提交者:

----------------



## 算法设计题2.15
```c++
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
```
提交者:

----------------
