
## 第二章程序设计题
抢答要求，参考[如何使用git](https://github.com/xiufengcheng/DATASTRUCTURE/tree/master/tools_download/GitHub%20%E6%95%99%E7%A8%8B),提交pull request. 老师择机合并你的答案。

## 算法设计题2.1

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

提交者:张孜铭

----------------


## 算法设计题2.2

```C
void ListReverse(SqList &L)
 {
     int i，temp;
     for (i=0; i<L.length/2; ++i)
     {
         temp = L.elem[i];
         L.elem[i] = L.elem[L.length-i-1];
         L.elem[L.length-i-1] = L.elem[i];
     }
}
```

提交者:张孜铭

----------------



## 算法设计题2.3

提交者:

----------------



## 算法设计题2.4

提交者:

----------------



## 算法设计题2.5

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

提交者:张孜铭

----------------



## 算法设计题2.6

提交者:

----------------



## 算法设计题2.7

```C
bool ListInsert_L_2_7(LinkList &L,int i,ElemType e)
 { 
     LinkList p,s;
     int j; 
     p=L;
     j=1;
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

提交者:

----------------


## 算法设计题2.9

提交者:

----------------


## 算法设计题2.10

提交者:

----------------



## 算法设计题2.11

提交者:

----------------



## 算法设计题2.12

提交者:

----------------



## 算法设计题2.13

提交者:

----------------



## 算法设计题2.14

提交者:

----------------



## 算法设计题2.15

提交者:

----------------
