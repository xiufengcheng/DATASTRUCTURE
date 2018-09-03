 enum ElemTag{ATOM,LIST};
 // ATOM==0：原子,LIST==1：子表
 typedef struct GLNode
 { ElemTag tag; // 公共部分，用于区分原子结点和表结点
   union // 原子结点和表结点的联合部分
   { ElemType data; // data是原子结点的值域，dataType由用户定义
     struct
     { GLNode *hp,*tp;
     }ptr; // ptr是表结点的指针域，prt.hp和ptr.tp分别指向表头和表尾(表头之外的其余元素)
   };
 }*GList,GLNode; // 广义表类型

 void sever(DSqString &str,DSqString &hstr)  
 { // 将脱去外层括号的非空串str分割成两部分：hstr为第一个','之前的子串，str为之后的子串
   int n,k=0,i=-1; // k记尚未配对的左括号个数
  char ch;
   n=StrLength_Sq(str); // n为串str的长度
   DSqString sub,temp;
   StrAssign_Sq(sub,"");   // 初始化sub
   StrAssign_Sq(temp,"");   // 初始化temp
   do // 搜索最外层(k=0时)的第1个逗号
   { 
     i++;
	 SubString_Sq(str,sub,i,1); 
     ch=sub.str[0];           // ch为串str的第i+1个字符 
     if(ch=='(')       ++k; // 尚未配对的左括号个数+1
     else if(ch==')')    --k; // 尚未配对的左括号个数-1
   }while(i<n&&ch!=','||k!=0); // i小于串长且ch不是最外层的','
   if(i<n) // 串str中存在最外层的','，它是第i个字符
   { SubString_Sq(str,hstr,0,i); // hstr返回串str','前的字符
     SubString_Sq(str,temp,i+1,n-i-1); // str返回串str','后的字符
     StrCopy_Sq(str,temp);
   }
   else // 串str中不存在','
   { StrCopy_Sq(hstr,str); // 串hstr就是串str
     DestroyString_Sq(str); // ','后面是空串
   }
 }

 void InitGList(GList &L)
 { // 创建空的广义表L
   L=NULL;
 }

 void CreateGList(GList &L,DSqString S) 
 { // 采用头尾链表存储结构，由广义表的书写形式串S创建广义表L。设emp="()"
   DSqString sub,hsub,emp;
   GList p,q;
   StrAssign_Sq(sub,"");   // 初始化sub
   StrAssign_Sq(hsub,"");   // 初始化hsub
   StrAssign_Sq(emp,"()"); // 空串emp="()"
   if(!StrCompare_Sq(S,emp)) // S="()"
	   L=NULL; // 创建空表
   else // S不是空串
   { if(!(L=(GList)malloc(sizeof(GLNode)))) // 建表结点
       exit(1);
     if(StrLength_Sq(S)==1) // S为单原子，这种情况只会出现在递归调用中
     { L->tag=ATOM; // 创建单原子广义表
       L->data=S.str[0]; // 单原子的值为字符型
     }
     else // S为表
     { L->tag=LIST; // L是子表
       p=L; // p也指向子表
       SubString_Sq(S,sub,1,StrLength_Sq(S)-2);
       // 脱外层括号(去掉第1个字符(左括号)和最后1个字符(右括号))给串sub
       do // 重复建n个子表
       { 
		 sever(sub,hsub); // 从sub中分离出表头串给hsub，其余部分(表尾)给sub
         CreateGList(p->ptr.hp,hsub); // 递归创建表头串表示的子表
         q=p; // q指向p所指结点
         if(sub.length) // 表尾不空
         { if(!(p=(GLNode*)malloc(sizeof(GLNode)))) // 由p创建表结点
             exit(1);
           p->tag=LIST; // p是子表
           q->ptr.tp=p; // p所指结点接在q所指结点之后，形成q的下一个结点
         }
       }while(sub.length); // 当表尾不空
       q->ptr.tp=NULL; // 设置最后一个表尾指针为空
     }
   }
   
 }

  void CopyGList(GList &T,GList L)
 { // 采用头尾链表存储结构，由广义表L复制得到广义表T
   if(!L) // 复制空表
     T=NULL;
   else // 广义表L不空
   { T=(GList)malloc(sizeof(GLNode)); // 建表结点
     if(!T)
       exit(1);
     T->tag=L->tag; // 复制标志域
     if(L->tag==ATOM) // 单原子
       T->data=L->data; // 复制单原子
     else // 子表
     { CopyGList(T->ptr.hp,L->ptr.hp); // 递归复制表头子表
       CopyGList(T->ptr.tp,L->ptr.tp); // 递归复制表尾(除表头之外的部分)子表
     }
   }
 }

 int GListLength(GList L)
 { // 返回广义表的长度，即元素个数
   int len=0; // 设置广义表长度的初值为0
   while(L) // 未到表尾
   { L=L->ptr.tp; // L指向广义表最外层的下一个元素
     len++; // 表长+1
   }
   return len;
 }

 int GListDepth(GList L)
 { // 采用头尾链表存储结构，求广义表L的深度
   int dep,max=0;
   GList pp;
   if(!L) // 广义表L为空
     return 1; // 空表深度为1
   if(L->tag==ATOM) // 是原子结点
     return 0; // 原子深度为0，只会出现在递归调用中
   for(pp=L;pp;pp=pp->ptr.tp) // 从本层的第1个元素到最后一个元素
   { dep=GListDepth(pp->ptr.hp); // 递归求以pp->ptr.hp为头指针的子表深度
     if(dep>max)
       max=dep; // max存本层子表深度的最大值
   }
   return max+1; // 非空表的深度是各元素的深度的最大值加1
 }

 bool GListEmpty(GList L)
 { // 判定广义表是否为空
   if(!L)
     return true;
   else
     return false;
 }

 GList GetHead(GList L)
 { // 生成广义表L的表头元素，返回指向这个元素的指针
   GList h;
   if(!L) // 空表无表头
     return NULL;
   CopyGList(h,L->ptr.hp); // 将L的表头元素复制给h
   return h;
 }

 GList GetTail(GList L)
 { // 将广义表L的表尾(除表头之外的部分)生成为广义表，返回指向这个新广义表的指针
   GList t;
   if(!L) // 空表无表尾
     return NULL;
   CopyGList(t,L->ptr.tp); // 将L的表尾元素复制给t
   return t;
 }

 void InsertFirst_GL(GList &L,GList e)
 { // 初始条件：广义表L存在。操作结果：插入元素e(也可能是子表)作为广义表L的第1个元素(表头)
   GList p=(GList)malloc(sizeof(GLNode)); // 生成新的表头结点
   if(!p)
     exit(1);
   p->tag=LIST; // 广义表L的类型是表
   p->ptr.hp=e; // L的表头指针指向e
   p->ptr.tp=L; // L的表尾指针指向原表L
   L=p; // L指向新的表头结点
 }

 void DeleteFirst_GL(GList &L,GList &e)
 { // 初始条件：广义表L存在。操作结果：删除广义表L的第1个元素(表头)，并用e返回其值
   GList p=L; // p指向第1个表结点
   e=L->ptr.hp; // e指向L的表头元素
   L=L->ptr.tp; // L指向原L的表尾(除表头之外的部分)
   free(p); // 释放p所指的表结点
 }

void Traverse_GL( GList LS) 
{ // 利用递归算法遍历广义表L
    GList p;   
	if(!LS)cout<<"()";                        // 输出空表
       else{
	     if(LS->tag==ATOM)cout<<LS->data;    // 输出原子
	     else{
	            cout<<'(';                   // 输出广义表的左括弧
                    p=LS;	  
         	    while(p){
	                 Traverse_GL(p->ptr.hp); // 输出第i项数据元素  
	                 p=p->ptr.tp; 
	                 if(p)cout<<',';         // 表尾不空时输出逗号
	             }
	            cout<<')';                   // 输出广义表的右括弧
		  }
	}
}// Traverse_GL

void Traverse_GL1(GList L)
 { // 利用递归算法遍历广义表L
   if(L) // L不空
     if(L->tag==ATOM) // L为单原子
       cout<<L->data;
     else // L为广义表
     { Traverse_GL1(L->ptr.hp); // 递归遍历L的表头
       Traverse_GL1(L->ptr.tp); // 递归遍历L的表尾
     }
 }

 void DestroyGList(GList &L)
 { // 销毁广义表L
   GList q1,q2;
   if(L) // 广义表L不空
   { if(L->tag==LIST) // 要删除的是表结点
     { q1=L->ptr.hp; // q1指向表头
       q2=L->ptr.tp; // q2指向表尾(除表头之外的其余部分)
       DestroyGList(q1); // 递归销毁表头
       DestroyGList(q2); // 递归销毁表尾
     }
     free(L); // 释放L所指的存储空间(无论L是表结点还是原子结点)
     L=NULL; // L不指向任何存储单元
   }
 }