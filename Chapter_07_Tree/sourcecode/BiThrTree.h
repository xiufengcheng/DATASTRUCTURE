typedef struct BiThrNode {
 TElemType data;                                // 结点的值  
   BiThrNode *lchild,*rchild;                     // 左右孩子指针
   unsigned short LTag:1;                         // 左标志，占1 bit
   unsigned short RTag:1;                         // 右标志，占1 bit
 }BiThrNode, *BiThrTree;

void CreateBiThrTree(BiThrTree &BT)
 {    // 按先序输入二叉树中结点的值，构造线索二叉树BT
   TElemType a;
   cin>>a;                                   // 输入结点的值
   if(a==Nil)                                // 结点的值为空
     BT=NULL;
   else                                      // 结点的值不为空
   { BT=(BiThrTree)malloc(sizeof(BiThrNode)); // 生成根结点(先序)
     if(!BT)
       exit(1);
     BT->data=a;                             // 将值赋给T所指结点
     CreateBiThrTree(BT->lchild);            // 递归构造左子树
     if(BT->lchild)                          // 有左孩子
       BT->LTag=0;                           // 给左标志赋值(指针)
else BT->LTag=1;                        // 给左标志赋值(线索)
     CreateBiThrTree(BT->rchild);            // 递归构造右子树
     if(BT->rchild)                          // 有右孩子
       BT->RTag=0;                           // 给右标志赋值(指针)
else BT->RTag=1;                        // 给右标志赋值(线索)
   }
 }// CreateBiThrTree

BiThrTree pre;       // 全局变量，始终指向刚刚访问过的结点
void InThreading(BiThrTree p)
{ // 对以P为根结点的二叉树进行中序线索化，线索化之后pre指向最后一个结点
   if(p)                                   // 线索二叉树不空
   { InThreading(p->lchild);               // 递归左子树线索化
     if(!p->lchild)                       // 没有左孩子
     { p->LTag=1;                         // 左标志为线索(前驱)
       p->lchild=pre;                     // 左孩子指针指向前驱
     }
     if(!pre->rchild)                     // 前驱没有右孩子
     { pre->RTag=1;                       // 前驱的右标志为线索(后继)
       pre->rchild=p;                     // 前驱右孩子指针指向其后继(当前结点p)
     }
     pre=p;                               // 保持pre指向p的前驱
     InThreading(p->rchild);              // 递归右子树线索化
   }
 }// InThreading

void InThreading_head(BiThrTree &head,BiThrTree BT)
 { // 对以BT为根结点的二叉树进行中序线索化，并增加一个头结点head
   if(!(head=(BiThrTree)malloc(sizeof(BiThrNode))))  // 生成头结点不成功
     exit(1);
   head->LTag=0;                                 // 建头结点，左标志为指针
   head->RTag=1;                                 // 右标志为线索
   head->rchild=head;                            // 右孩子指针回指
   if(!BT)                                       // 若二叉树T空，则左孩子指针回指
     head->lchild=head;
   else // 二叉树T非空
   { head->lchild=BT;                             // 头结点的左孩子指针指向根结点
     pre=head;                                     // pre(前驱)的初值指向头结点
     InThreading(BT);                     // 对以BT为根对点的二叉树进行中序线索化
// pre指向中序遍历的最后一个结点
     pre->rchild=head;                    // 最后一个结点的右孩子指针指向头结点
     pre->RTag=1;                         // 最后一个结点的右标志为线索
     head->rchild=pre;                    // 头结点的右孩子指针指向最后一个结点
   }
 }// InThreading_head

BiThrTree FirstNode(BiThrTree head)
{  // 在中序线索二叉树中查找中序序列的第一个结点
    BiThrTree p=head->lchild;
while(p->LTag==0)                // 由p所指结点一直找到二叉树的最左边结点
      p=p->lchild;                   // p指向其左孩子
return p;
}// FirstNode

BiThrTree LastNode(BiThrTree head)
{    // 在中序线索二叉树中查找中序序列的最后一个结点
return head->rchild;
}// LastNode

BiThrTree PreNode(BiThrTree p)
{   // 在中序线索二叉树中查找p的中序前驱
BiThrTree pre;
pre=p->lchild;                         // 把p的左指针域赋给pre
if(p->LTag==0)                         // 左标志为孩子
while(pre->RTag==0)                 // 由pre所指结点一直找到最右边结点
pre=pre->rchild;                 // pre指向基其右孩子
return pre;
}// PreNode

BiThrTree PostNode(BiThrTree p)
{   // 在中序线索二叉树中查找p的中序后继
BiThrTree post;
post=p->rchild;                        // 把p的右指针域赋给post
if(p->RTag==0)                         // 右标志为孩子
while(post->LTag==0)                // 由post所指结点一直找到最左边结点
post=post->lchild;                // pre指向基其右孩子
return post;
}// PostNode

void InOrderTraverse_Thr(BiThrTree head,void Visit(TElemType))
 { // 中序遍历线索二叉树head(头结点)
   BiThrTree p;
   p=FirstNode(head);                    // 查找中序序列的第一个结点
   while(p!=head)                        // 未遍历完
   {   Visit(p->data);                    // 访问p所指结点
    p=PostNode(p);                     // p指向其中序后继
   }
}// InOrderTraverse_Thr

void InOrderTraverse_Thr_Reverse(BiThrTree head,void Visit(TElemType))
 {   // 逆中序遍历线索二叉树head(头结点)
   BiThrTree p;
   p=LastNode(head);                     // 查找中序序列的最后一个结点
   while(p!=head)                        // 未遍历完
   {   Visit(p->data);                    // 访问p所指结点
      p=PreNode(p);                     // p指向其中序前驱
   }
}// InOrderTraverse_Thr_Reverse

void PrintBiThrTree(BiThrTree BT)
{    // 以广义表的形式输出一棵线索二叉树BT，BT为二叉树的根结点
		cout<<BT->data;                      // 输出根结点的值
		if(BT->LTag==0||BT->RTag==0)         // 左孩子或右孩子存在
		{  cout<<'(';   
		   if(BT->LTag==0)                   // 左子树存在
			  PrintBiThrTree(BT->lchild);    // 递归输出左子树
		if(BT->RTag==0)                      // 右子树存在
		{   cout<<',';
			PrintBiThrTree(BT->rchild);      // 递归输出右子树
		}
		cout<<')';
		}
}// PrintBiThrTree

void DestroyBiTree(BiThrTree &BT)
 {  // 撤销以BT为根结点的线索二叉树
   if(BT)                                       // 非空树
   { if(BT->LTag==0)                            // 有左子树
       DestroyBiTree(BT->lchild);               // 销毁左子树
     if(BT->RTag==0)                            // 有右子树
       DestroyBiTree(BT->rchild);               // 销毁右子树
     free(BT);                                  // 释放根结点
     BT=NULL;                                   // BT置空
   }
 }// DestroyBiTree

void DestroyBiThrTree(BiThrTree &head)
 {    // 撤销带头结点head的线索二叉树
   if(head)                                  // 头结点存在
   { if(head->lchild)                        // 根结点存在
       DestroyBiTree(head->lchild);          // 递归销毁头结点lchild所指二叉树
     free(head);                             // 释放头结点
     head=NULL;                              // head置空
   }
 }// DestroyBiThrTree
