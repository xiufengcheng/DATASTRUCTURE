## 第二章程序设计题
抢答要求，参考[如何使用git](https://github.com/xiufengcheng/DATASTRUCTURE/tree/master/tools_download/GitHub%20%E6%95%99%E7%A8%8B),提交pull request. 老师择机合并你的答案。

### 2.1
```C
bool ListInsert_Sq_2_1(SqList &L, ElemType e)
{  
    int i,j;
    if(L.length>=L.listsize)  
    {                  
	L.elem=(ElemType *)realloc(L.elem,(L.listsize+L.incrementsize)*sizeof(ElemType));
	if(!L.elem) exit(1);                  
	L.listsize+=L.incrementsize;           
    }
    i = 0;
    while(L.elem[i]<e)          
	i++;
    for(i=0;i<L.length&&e>L.elem[i];i++); 
    for(j=L.length;j>i;j--)               
	L.elem[j]=L.elem[j-1];
    L.elem[i]=e;                           
    L.length++;                           
    return true;   
}
```
### 2.2 
```C
void ListReverse(SqList &L)
 {
     int i=0;
     for (i=0; i<L.length/2; ++i)
     {
         L.elem[i] = L.elem[i] + L.elem[L.length-i-1];
         L.elem[L.length-i-1] = L.elem[i] - L.elem[L.length-i-1];
         L.elem[i] = L.elem[i] - L.elem[L.length-i-1];
     }
}
```
### 2.3


### 2.4


### 2.5
```C
void ListReverse_L(LinkList &L)  
{   
    LNode* p=L->next->next;
    L->next->next=NULL;
    while(p)  
    {  
        LNode* q=p->next;  
        p->next=L->next;  
        L->next=p;  
        p=q;
    }  
}  
```
### 2.6


### 2.7
```C
bool ListInsert_L_2_7(LinkList &L,int i,ElemType e)
 { 
     int j=1; 
     LinkList s,p=L; 
     if(i<1) 
         return false;
     s=(LinkList)malloc(sizeof(LNode)); 
     s->data=e; 
     if(i==1)
     { 
         s->next=L; 
         L=s; 
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
     s->next=p->next;
     p->next=s; 
   }
   return true; 
 }

bool ListDelete_L_2_7(LinkList &L,int i,ElemType &e)
 { 
     int j=1; 
     LinkList q,p=L; 
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
### 2.8


### 2.9


### 2.10


### 2.11
