typedef int ElemType;
typedef struct DuNode  {
 ElemType data;
struct  DuNode *prior;
struct  DuNode *next;
}DuLNode,*DuLinkList;

void InitList_DuL(DuLinkList &L)
{  
L=(DuLNode *)malloc(sizeof(DuLNode));  // 申请存放一个结点数据所需要的内在空间
if(!L)   exit(1);                        // 存储分配失败
L->next=NULL;                            // 表头结点的后继指针域置空
L->prior=NULL;                           // 表头结点的前驱指针域置空
}

int ListLength_Dul(DuLinkList L ) 
{     
  		DuLinkList  p;
		int k=0;
		p=L->next;                           
 		 while(p)             //当p所指向的结点还有值
  		 { k++;  p=p->next; }            
         return k;
}// ListLength_Dul


bool ListInsert_DuL(DuLinkList &L,int i,ElemType e) 
    {
       // 在带头结点的双向链表L中第i个结点之前插入元素e
  DuLinkList p,s,q;
   int j;
   q=L;  j=0;
   while(q->next&&j<i-1)  { q=q->next; j++; }   // 寻找第i-1个结点,并让q指向此结点
   if(j!=i-1)   return false;                   // i的位置不合理
   s=(DuLNode *)malloc(sizeof(DuLNode));
   if(!s)   exit(1);                            // 存储分配失败
   s->data=e;  
   if(q->next)                                   // 插入的位置不是表尾
   { 
	p=q->next;                                  // p指向待插入的位置
	s->prior=p->prior;                          // 修改指针
    p->prior->next=s;      
    s->next=p;
    p->prior=s; 
   }
   else                                     // 插入的位置是表尾
   { 
     q->next=s;
	 s->prior=q;
	 s->next=NULL;
   }
return true;
}

bool ListDelete_DuL(DuLinkList &L, int i, ElemType &e)
{
           // 删除带有头结点的双向链表L中的第i个结点，并让e返回其值
DuLinkList p;
  int j;
  p=L;  j=0;
 while(p->next&&j<i){ p=p->next; j++; }      // 寻找第i个结点,并让p指向此结点
   if(j!=i)   return false;                 // i的位置不合理
   if(p->next)                              // 待删除的不是表尾结点
     p->next->prior=p->prior;               // 结点p的前驱作为结点p的后继的前驱
     p->prior->next=p->next;                // 结点p的后继作为结点p的前驱的后继                              
     e=p->data;                     
     free(p);                                    
  return true;
 }
