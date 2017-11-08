typedef char TElemType;       // 定义树中元素类型TElemType为字符型
TElemType Nil='#';            // 用'#'表示空
# include "stdlib.h"          // 该文件包含malloc()、realloc()和free()等函数
# include "iomanip.h"         // 该文件包含控制符setw()
# define MAX_BITREE_SIZE 100  // 二叉树中的最大结点数
# include "BiThrTree.h"       // 该文件包含线索二叉树数据对象的描述及相关操作
	
void Visit(TElemType e)       // 访问函数定义为输出操作
 {
   cout<<e<<' ';
 }

void main()
 {
   int i;
   BiThrTree head,BT,p,c;
   cout<<"请按先序输入二叉树(用'#'表示子树为空)："<<endl;
   CreateBiThrTree(BT);                    // 建立二叉树BT
   InThreading_head(head,BT);              // 中序线索化二叉树BT,head指向头结点
   cout<<"中序遍历中序线索二叉树：";
   InOrderTraverse_Thr(head,Visit);         // 中序遍历中序线索二叉树
   cout<<endl<<"逆中序遍历中序线索二叉树：";
   InOrderTraverse_Thr_Reverse(head,Visit); // 逆中序遍历中序线索二叉树
   cout<<endl<<"以广义表的形式输出中序线索二叉树：";
  if(head->lchild!=head)                     // 线索二叉树非空
    PrintBiThrTree(head->lchild);            // 以广义表的形式输出中序线索二叉树
   DestroyBiThrTree(head);                   // 撤销中序线索二叉树
  }	
