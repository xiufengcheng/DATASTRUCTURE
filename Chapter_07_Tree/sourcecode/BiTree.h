typedef struct BiTNode {
  TElemType data;                            // 结点的值
  struct BiTNode *lchild;                    // 左孩子指针
  struct BiTNode *rchild;                    // 右孩子指针
}BiTNode,*BiTree;

void PreOrderBiTree(BiTree BT,void Visit(TElemType))
 {     // 先序递归遍历二叉树BT
   if(BT)                                        // BT不空
   { Visit(BT->data);                            // 先访问根结点
     PreOrderBiTree(BT->lchild,Visit);           // 再先序遍历左子树
     PreOrderBiTree(BT->rchild,Visit);           // 最后先序遍历右子树
   }
 }// PreOrderBiTree 
typedef BiTree ElemType;                // 定义栈和队列元素为二叉树的指针类型
# include "SqStack.h"                   // 包含顺序栈数据对象的描述及相关操作

void NRPreOrderBiTree(BiTree BT,void Visit(TElemType))
 {      // 先序非递归遍历二叉树BT(利用栈)
   SqStack S;
   InitStack_Sq(S,MAX_BITREE_SIZE,10);      // 初始化栈S
   while(BT||!StackEmpty_Sq(S))             // 当BT不空或者栈不空
   { if(BT)                                 // BT不空
     { Visit(BT->data);                     // 访问根结点
       Push_Sq(S,BT);                       //根指针进栈
       BT=BT->lchild;                       // BT指向其左孩子
     }
     else                                   // 根指针退栈，访问根结点，遍历右子树
     { Pop_Sq(S,BT);                        //根指针出栈
       BT=BT->rchild;                        // BT指向其右孩子
     }
   }
 }// NRPreOrderBiTree

void InOrderBiTree(BiTree BT,void Visit(TElemType))
 {    // 中序递归遍历二叉树BT
   if(BT)                                  // BT不空
   { InOrderBiTree(BT->lchild,Visit);      // 先中序遍历左子树
     Visit(BT->data);                      // 再访问根结点
     InOrderBiTree(BT->rchild,Visit);      // 最后中序遍历右子树
   }
 }// InOrderBiTree

void NRInOrderBiTree(BiTree BT,void Visit(TElemType))
 {  // 中序非递归遍历二叉树BT(利用栈)
  SqStack S;
  InitStack_Sq(S,MAX_BITREE_SIZE,10);        // 初始化栈S
   while(BT||!StackEmpty_Sq(S))              // 当BT不空或者栈不空
   { if(BT)                                  // BT不空
     {                                       // 根指针进栈，遍历左子树
       Push_Sq(S,BT);                        // 根指针进栈
       BT=BT->lchild;                        // BT指向其左孩子
     }
     else                                    // 根指针退栈，访问根结点，遍历右子树
     { Pop_Sq(S,BT);                         //根指针出栈
       Visit(BT->data);                      // 访问根结点
       BT=BT->rchild;                        // BT指向其右孩子
     }
   }
 }// NRInOrderBiTree 

void PostOrderBiTree(BiTree BT,void Visit(TElemType))
 {            // 后序递归遍历二叉树BT
   if(BT)                                       // BT不空
   { PostOrderBiTree(BT->lchild,Visit);         // 先后序遍历左子树
     PostOrderBiTree(BT->rchild,Visit);         // 再后序遍历右子树
     Visit(BT->data); // 最后访问根结点
   }
 }// PostOrderBiTree

void NRPostOrderBiTree(BiTree BT,void Visit(TElemType))
{   // 后序非递归遍历二叉树BT(利用栈)
   SqStack S;
   InitStack_Sq(S,MAX_BITREE_SIZE,10);            // 初始化栈S
   BiTree p,q;
   int flag;
   if (!BT)   return;
   p=BT;
   do
    { while(p)                                      // 为非空二叉树,向左走到尽头
      {  Push_Sq(S,p);                              // p进栈
         p=p->lchild;                               // p指向其左孩子
     }
     q=NULL; flag=1;
     while (!StackEmpty_Sq(S)&&flag)
     { GetTop_Sq(S,p);                          // 取栈顶元素
       if (p->rchild==q)                        // 其右孩子不存在或已访问 
       { Pop_Sq(S,p);                           //栈顶元素出栈
		 Visit(p->data);                        // 访问p所指结点
         q=p;                                   // q指向刚刚访问的结点
      }
     else
      { p=p->rchild;                            // p指向其右孩子
        flag=0;
      }
     }
    } while (!StackEmpty_Sq(S));
   }// NRPostOrderBiTree

# include "SqQueue.h"              // 包含循环队列数据对象的描述及相关操作
void LevelOrderBiTree(BiTree BT,void Visit(TElemType))
 { // 层序递归遍历BT(利用队列)
   SqQueue Q;
   BiTree p;
   if(BT) // BT不空
   { InitQueue_Sq(Q,MAX_BITREE_SIZE,10);  // 初始化队列Q
     EnQueue_Sq(Q,BT); // 根指针入队
     while(!QueueEmpty_Sq(Q)) // 队列不空
     { DeQueue_Sq(Q,p); // 出队元素(指针)，赋给p
       Visit(p->data); // 访问p所指结点
       if(p->lchild!=NULL) // p有左孩子
         EnQueue_Sq(Q,p->lchild); // 入队p的左孩子
       if(p->rchild!=NULL) // p有右孩子
         EnQueue_Sq(Q,p->rchild); // 入队p的右孩子
     }
   }
 }// LevelOrderBiTree

void InitBiTree(BiTree &BT)
 {          
   BT=NULL;
 }// InitBiTree 

void CreateBiTree(BiTree &BT)
{  // 按先序次序输入二叉树中结点的值，构造二叉树BT。变量Nil表示空(子)树。
TElemType a;
cin>>a;                                         // 输入结点的值
   if(a==Nil)                                        // 结点的值为空
	   BT=NULL;
   else                                              // 结点的值不为空
   { BT=(BiTree)malloc(sizeof(BiTNode));             // 生成根结点
     if(!BT)
       exit(1);
     BT->data=a;                                     // 将值赋给T所指结点
     CreateBiTree(BT->lchild);                       // 递归构造左子树
     CreateBiTree(BT->rchild);                       // 递归构造右子树
   }
}// CreateBiTree

bool BiTreeEmpty(BiTree BT)
 { 
   if(BT)
     return false;
   else
     return true;
 }// BiTreeEmpty

int BiTreeDepth(BiTree BT)
 { // 求二叉树BT的深度,并返回其值
   int Lh,Rh;
   if(!BT)
     return 0;                 // 空树深度为0
   Lh=BiTreeDepth(BT->lchild); // Lh为左子树的深度，如左子树为空，则Lh为0
   Rh=BiTreeDepth(BT->rchild); // Rh为右子树的深度，如右子树为空，则Rh为0
   return Lh>Rh?Lh+1:Rh+1;     // BT的深度为其左右子树的深度中的大者+1
 }// BiTreeDepth

BiTree SearchBiTree(BiTree BT,TElemType e)
 { // 查找二叉树BT中元素值为e的结点，查找成功返回其指针，否则返回空指针
   BiTree p;
   if(!BT)     return NULL;              // 空树,返回"空"
   if(BT->data==e) return BT;            // 查找成功，返回其指针
   if(BT->lchild)                        // 左子树非空
   {   p=SearchBiTree(BT->lchild,e);     // 递归查找左子树
       if(p) return p;                   // 查找成功，返回p
   }
   if(BT->rchild)                        // 右子树非空
   {   p=SearchBiTree(BT->rchild,e);      // 递归查找右子树
       if(p)  return p;                   // 查找成功，返回p
   }
   return NULL;                           //查找失败，返回NULL
}// SearchBiTree

BiTree Parent(BiTree BT,TElemType e)
 { // 若e是BT的非根结点，则返回它的双亲，否则返回"空"
   SqQueue Q;
   BiTree p;
   if(BT)                                               // 非空树
   { InitQueue_Sq(Q,MAX_BITREE_SIZE,10);                // 初始化队列Q
     EnQueue_Sq(Q,BT);                                  // 树根指针入队
     while(!QueueEmpty_Sq(Q))                           // 队不空
     { DeQueue_Sq(Q,p);                                 // 出队，队列元素赋p
       if(p->lchild&&p->lchild->data==e||p->rchild&&p->rchild->data==e)
                                                        // 找到e(是其左或右孩子)
         return p;                                      // 返回e的双亲
       else                                             // 未找到e
       { if(p->lchild)                                  // p有左孩子
           EnQueue_Sq(Q,p->lchild);                     //左孩子指针入队
         if(p->rchild)                                  // p有右孩子
           EnQueue_Sq(Q,p->rchild);                     //右孩子指针入队
       }
     }
   }
   return NULL;                                     // 树空或未找到e
 }// Parent

BiTree LeftChild(BiTree BT,TElemType e)
 { // 若e是BT中某个结点,则返回e的左孩子。若e无左孩子，则返回"空"
   BiTree p;
   if(BT)                                       // 非空树
   { p=SearchBiTree(BT,e);                      // p是指向结点e的指针
     if(p)                                      // BT中存在结点e
       return p->lchild;                        // 返回e的左孩子
   }
   return NULL;                                 // 其余情况返回"空"
 }// LeftChild

BiTree RightChild(BiTree BT,TElemType e)
 { // 若e是BT中某个结点,则返回e的右孩子。若e无右孩子，则返回"空"
   BiTree p;
   if(BT)                                       // 非空树
   { p=SearchBiTree(BT,e);                      // p是指向结点e的指针
     if(p)                                      // BT中存在结点e
       return p->rchild;                        // 返回e的右孩子的值
   }
   return NULL;                                 // 其余情况返回空
 }// RightChild

BiTree LeftSibling(BiTree BT,TElemType e)
 { // 若e是BT中某个结点，则返回e的左兄弟。若e是BT的左孩子或无左兄弟，则返回"空"
   BiTree p;
   if(BT)                                            // 非空树
   { p=Parent(BT,e);                                 // p为e的双亲
     if(p)                                           // 找到e的双亲
       if(p->lchild&&p->rchild&&p->rchild->data==e)  // p存在左右孩子且右孩子是e
         return p->lchild;                           // 返回p的左孩子(e的左兄弟)
   }
   return NULL;                                      // 其余情况返回空
 }// LeftSibling

BiTree RightSibling(BiTree BT,TElemType e)
 { // 若e是BT中某个结点，则返回e的右兄弟。若e是T的右孩子或无右兄弟，则返回"空"
   BiTree p;
   if(BT)                                            // 非空树
   { p=Parent(BT,e);                                 // p为e的双亲
     if(p)                                           // 找到e的双亲
       if(p->lchild&&p->rchild&&p->lchild->data==e)  // p存在左右孩子且左孩子是e
         return p->rchild;                           // 返回p的右孩子(e的右兄弟)
   }
   return NULL;                                      // 其余情况返回空
 }// RightSibling

bool InsertChild(BiTree p,int LR,BiTree c)  
 { // 若二叉树BT存在，p指向BT中某个结点，根据LR的值插入子树c作为p的孩子
   if(p)                               // p不空
   { if(LR==0)                         // 把二叉树c插为p所指结点的左子树
     { c->rchild=p->lchild;            // p所指结点的原有左子树成为c的右子树
       p->lchild=c;                    // 二叉树c成为p的左子树
     }
     else                              // LR==1，把二叉树c插为p所指结点的右子树
     { c->rchild=p->rchild;            // p所指结点的原有右子树成为c的右子树
       p->rchild=c;                    // 二叉树c成为p的右子树
     }
     return true;
   }
   return false;                       // p空
 }// InsertChild

void PrintBiTree(BiTree BT,int n)
 {  // 采用凹入表形式输出二叉树,n为缩进层数,初值为1
 int i;
 if(!BT)return;
PrintBiTree(BT->rchild,n+1);                  // 在第n+1层递归打印右子树
 for(i=2;i<n;++i)                              // 打印空格
	 cout<<"      ";            
 if(n>1)cout<<"  - - -";                       // 打印连线
 cout<<BT->data<<endl;                         // 打印根结点的值
 PrintBiTree(BT->lchild,n+1);                  // 在第n+1层递归打印左子树
}// PrintBiTree

void DestroyBiTree(BiTree &BT)
 { // 撤销二叉树BT
   if(BT)                       // 非空树
   { DestroyBiTree(BT->lchild); // 递归撤销左子树，如无左子树，则不执行任何操作
     DestroyBiTree(BT->rchild); // 递归撤销右子树，如无右子树，则不执行任何操作
     free(BT);                  // 释放根结点
     BT=NULL;                   // BT置空
   }
 }// DestroyBiTree

bool DeleteChild(BiTree p,int LR) 
 { // 若二叉树BT存在，p指向BT中某个结点，根据LR的值删除p的子树c
      if(p)                                   // p不空
      { if(LR==0)                             // 删除左子树
           DestroyBiTree(p->lchild);          // 清空p所指结点的左子树
         else                                  // 删除右子树
           DestroyBiTree(p->rchild);           // 清空p所指结点的右子树
         return true;
      }
      return false;                             // p空
 }// DeleteChild
