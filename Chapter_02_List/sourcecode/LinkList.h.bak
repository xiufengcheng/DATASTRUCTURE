typedef struct Node {
   ElemType data;
   struct  Node  *next;
}LNode,*LinkList;                 // LinkList为结构体指针类型

void InitList_L(LinkList &L)
    {  
		L=(LNode *)malloc(sizeof(LNode));  // 申请存放一个结点数据所需要的内在空间
		if(!L)   exit(1);                        // 存储分配失败
        L->next=NULL;                            // 表头结点的指针域置空
	}// InitList_L

int ListLength_L( LinkList L ) 
	{     // L为带头结点的链表的头指针，本函数返回L所指链表的长度
  		LinkList  p;
		int k=0;
		p=L->next;                             // p指向链表中的第一个结点
 		 while(p) 
  		 { k++;  p=p->next; }              // k计非空结点数
         return k;
	}// ListLength_L

LNode *LocateElem_L( LinkList L,ElemType e) 
	{  // 在L所指的单链表中查找第一个值和e 相等的结点，若存在，则返回其指针；
		// 否则返回空指针
 		 LinkList  p;                           
 		 p=L->next;                               // p指向链表中的第一个结点
  		 while (p&&p->data!=e ) p=p->next;
  		 return p;
	}// LocateElem_L

int LocateElem_L_2( LinkList L,ElemType e) 
	{  // 在L所指的单链表中查找第一个值和e相等的结点，若存在，则返回元素顺序(返回值+2为真实顺序)，否则返回-1
 		 int i=-1;
         LinkList  p;                           
 		 p=L->next;                               // p指向链表中的第一个结点
  		 while (p&&p->data!=e) {p=p->next;i++;} 
  		 return i;
	}// LocateElem_L_2
	

bool ListInsert_L( LinkList &L, int i, ElemType e) 
	{    //在带有头结点的单链表L中的第i个结点之前插入元素e
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

void CreateList_L_Front(LinkList &L,ElemType a[],int n ) 
	{    // 已知一维数组A[n]中存有线性表的数据元素，利用头插法创建单链表L
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

void ListTraverse_L(LinkList L)
	{
		 LinkList p=L->next;
 		 while(p)
  	  {  cout<< setw(6)<<p->data;
         p=p->next;
      }
		cout<<endl;
	}// ListTraverse_L

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

void ListVisualization_L(LinkList L, char* filename)
{   int temp=0;
    LinkList p=L;
	FILE *stream;  
    if( NULL == (stream = fopen(filename, "w")) )  
    {  printf("open file error");  cout<<"error!";  }  
    else if(p&&!(p->next))
    {
		fprintf(stream, " digraph g {\n rankdir=LR;\n node [shape = \"record\" width = 0.5];\nnode0  [label = \"<data> //// | <next>  ^\"];\n\n");
	}
	else if(p&&(p->next))
    {   fprintf(stream, "digraph g {\n rankdir=LR;\n node [shape = \"record\" width = 0.5];\nnode0  [label = \"<data> //// | <next>  \"];\n\n");
       
	   while(p->next)
	   {
	     fprintf(stream, 
		 "node%d [label =\"<data> %d| <next>\"]\n  node%d:next -> node%d:data;\n\n",temp+1, p->next->data,temp,temp+1);
		 p=p->next;
		 temp++;
	   }
    }
	fprintf(stream, "\n}"); 
	fclose(stream);  
	system("dot -Tpng showlinklist.dot -o showlinklist.png");
	system("showlinklist.png");
}