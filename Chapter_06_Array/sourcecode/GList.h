enum ElemTag{ATOM,LIST};            // ATOM==0：原子,LIST==1：子表
typedef struct GLNode { 
ElemTag tag;                     // 公共部分，用于区分原子结点和表结点
   union                            // 原子结点和表结点的联合部分
   { ElemType data;                 // data是原子结点的值域，dataType由用户定义
     struct
     { struct GLNode *hp,  *tp ;  }ptr; 
// ptr是表结点的指针域，prt.hp和ptr.tp分别指向表头和表尾(表头之外的其余元素)
   };
 }*GList;                       // 广义表类型

void InitGList(GList &GL)
 { // 创建空的广义表GL
   GL=NULL;
 }// InitGList

void sever(DSqString &str,DSqString &hstr)  
 { // 将脱去外层括号的非空串str分割成两部分：hstr为第一个','之前的子串，
    //str为之后的子串
   int n,k=0,i=-1;                   // k记尚未配对的左括号个数
   char ch;
   n=StrLength_Sq(str);               // n为串str的长度
   DSqString sub,temp;
   StrAssign_Sq(sub,"");               // 初始化sub
   StrAssign_Sq(temp,"");               // 初始化temp
   do                                   // 搜索最外层(k=0时)的第1个逗号
   { i++;
	 SubString_Sq(str,sub,i,1); 
     ch=sub.str[0];                     // ch为串str的第i+1个字符 
     if(ch=='(')       ++k;             // 尚未配对的左括号个数+1
     else if(ch==')')    --k;           // 尚未配对的左括号个数-1
   }while(i<n&&ch!=','||k!=0);          // i小于串长且ch不是最外层的','
   if(i<n)                               // 串str中存在最外层的','，它是第i个字符
   { SubString_Sq(str,hstr,0,i);         // hstr返回串str','前的字符
     SubString_Sq(str,temp,i+1,n-i-1);   // str返回串str','后的字符
     StrCopy_Sq(str,temp);
   }
   else                                  // 串str中不存在','
   { StrCopy_Sq(hstr,str);               // 串hstr就是串str
     DestroyString_Sq(str);              // ','后面是空串
   }
 }// sever

void CreateGList(GList &GL,DSqString S) 
 { // 采用头尾链表存储结构，由广义表的书写形式串S创建广义表GL。设emp="()"
   DSqString sub,hsub,emp;
   GList p,q;
   StrAssign_Sq(sub,"");                      // 初始化sub
   StrAssign_Sq(hsub,"");                     // 初始化hsub
   StrAssign_Sq(emp,"()");                    // 空串emp="()"
   if(!StrCompare_Sq(S,emp)) // S="()"
	   GL=NULL;                               // 创建空表
   else                                       // S不是空串
   { if(!(GL=(GList)malloc(sizeof(GLNode))))  // 建表结点
       exit(1);
     if(StrLength_Sq(S)==1) // S为单原子，这种情况只会出现在递归调用中
     { GL->tag=ATOM;                          // 创建单原子广义表
       GL->data=S.str[0];                     // 单原子的值为字符型
     }
     else                                     // S为表
     { GL->tag=LIST;                          // GL是子表
       p=GL;                                  // p也指向子表
       SubString_Sq(S,sub,1,StrLength_Sq(S)-2);
       // 脱外层括号(去掉第1个字符(左括号)和最后1个字符(右括号))给串sub
       do                                     // 重复建n个子表
       { sever(sub,hsub); // 从sub中分离出表头串给hsub，其余部分(表尾)给sub
         CreateGList(p->ptr.hp,hsub);          // 递归创建表头串表示的子表
         q=p;                                  // q指向p所指结点
         if(sub.length)                        // 表尾不空
         { if(!(p=(GLNode*)malloc(sizeof(GLNode)))) // 由p创建表结点
             exit(1);
           p->tag=LIST;                             // p是子表
           q->ptr.tp=p; // p所指结点接在q所指结点之后，形成q的下一个结点
         }
       }while(sub.length);                         // 当表尾不空
       q->ptr.tp=NULL;                              // 设置最后一个表尾指针为空
     }
   }
 }// CreateGList

void CopyGList(GList &T,GList GL)
 {      // 采用头尾链表存储结构，由广义表GL复制得到广义表T
   if(!GL)                                       // 复制空表
     T=NULL;
   else                                          // 广义表GL不空
   { T=(GList)malloc(sizeof(GLNode));            // 建表结点
     if(!T)
       exit(1);
     T->tag=GL->tag;                             // 复制标志域
     if(GL->tag==ATOM)                           // 单原子
       T->data=GL->data;                         // 复制单原子
     else // 子表
     { CopyGList(T->ptr.hp,GL->ptr.hp);          // 递归复制表头子表
       CopyGList(T->ptr.tp,GL->ptr.tp); // 递归复制表尾(除表头之外的部分)子表
     }
   }
 }// CopyGList

int GListLength(GList GL)
 {     // 返回广义表GL的长度，即元素个数
   int len=0;                            // 设置广义表长度的初值为0
   while(GL)                             // 未到表尾
   { GL=GL->ptr.tp;                      // GL指向广义表最外层的下一个元素
     len++;                              // 表长+1
   }
   return len;
 }// GlistLength

int GListDepth(GList GL)
 { // 采用头尾链表存储结构，求广义表GL的深度，并返回其值
   int dep,max=0;
   GList pp;
   if(!GL)                                         // 广义表GL为空
     return 1;                      // 空表深度为1
   if(GL->tag==ATOM)                // 是原子结点
     return 0;                      // 原子深度为0，只会出现在递归调用中
   for(pp=GL;pp;pp=pp->ptr.tp)      // 从本层的第1个元素到最后一个元素
   { dep=GListDepth(pp->ptr.hp);    // 递归求以pp->ptr.hp为头指针的子表深度
     if(dep>max)
       max=dep;                     // max存本层子表深度的最大值
   }
   return max+1;                    // 非空表的深度是各元素的深度的最大值加1
 }// GlistDepth

bool GListEmpty(GList GL)
 { // 判定广义表是否为空
   if(!GL)
     return true;
   else
     return false;
 }// GlistEmpty

GList GetHead(GList GL)
 { // 生成广义表GL的表头元素，返回指向这个元素的指针
   GList h;
   if(!GL)                                // 空表无表头
     return NULL;
   CopyGList(h,GL->ptr.hp);               // 将GL的表头元素复制给h
   return h;
 }// GetHead

GList GetTail(GList GL)
 { // 将广义表GL的表尾(除表头之外的部分)生成为广义表，返回指向这个新广义表的指针
   GList t;
   if(!GL)                                     // 空表无表尾
     return NULL;
   CopyGList(t,GL->ptr.tp);                     // 将L的表尾元素复制给t
   return t;
 }// GetTail

void InsertFirst_GL(GList &GL,GList e)
 { // 将元素e(也可能是子表)作为广义表GL的第1个元素(表头)插入
   GList p=(GList)malloc(sizeof(GLNode));        // 生成新的表头结点
   if(!p)
     exit(1);
   p->tag=LIST;                                  // 广义表GL的类型是表
   p->ptr.hp=e;                                  // GL的表头指针指向e
   p->ptr.tp=GL;                                 // GL的表尾指针指向原表GL
   GL=p;                                         // GL指向新的表头结点
 }// InsertFirst_GL

void DeleteFirst_GL(GList &GL,GList &e)
 { // 删除广义表GL的第1个元素(表头)，并用e返回其值
   GList p=GL;                           // p指向第1个表结点
   e=GL->ptr.hp;                         // e指向GL的表头元素
   GL=GL->ptr.tp;                        // GL指向原GL的表尾(除表头之外的部分)
   free(p);                              // 释放p所指的表结点
 }// DeleteFirst_GL

void Traverse_GL( GList GL) 
{   // 利用递归算法遍历广义表GL
   GList p;   
if(!GL)cout<<"()";                         // 输出空表
   else{
       if(GL->tag==ATOM)cout<<GL->data;       // 输出原子
       else{
            cout<<'(';                       // 输出广义表的左括弧
            p=GL;  
            while(p){
              Traverse_GL(p->ptr.hp);         // 输出第i项数据元素  
              p=p->ptr.tp; 
              if(p)cout<<',';                // 表尾不空时输出逗号
             }
         cout<<')';                           // 输出广义表的右括弧
     }
}
}// Traverse_GL

void DestroyGList(GList &GL)
 { // 撤销广义表GL
   GList q1,q2;
   if(GL)                               // 广义表GL不空
   { if(GL->tag==LIST)                  // 要删除的是表结点
     { q1=GL->ptr.hp;                   // q1指向表头
       q2=GL->ptr.tp;                   // q2指向表尾(除表头之外的其余部分)
       DestroyGList(q1);                // 递归销毁表头
       DestroyGList(q2);                // 递归销毁表尾
     }
     free(GL);               // 释放GL所指的存储空间(无论GL是表结点还是原子结点)
     GL=NULL;                  // GL置空
   }
 }// DestroyGList
