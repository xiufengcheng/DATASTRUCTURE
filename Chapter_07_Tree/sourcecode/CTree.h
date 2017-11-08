typedef struct CTNode {
TElemType data;                     // 结点的值
  struct CTNode *child[MAX_SON_SIZE]; // 结点的指针域,指向孩子结点
}CTNode,*CTree;                       // 结点的类型

# define MS 10                        // 栈空间的大小

void InitTree(CTree &T)
{ 
	T=NULL;
}// InitTree

void CreateTree(CTree &T,char *S)
{ // 根据广义表字符串S所给出的MAX_SON_SIZE度树建立对应的存储结构,T指向树根
    CTree stack[MS],p;        // stack数组作为存储树中结点指针的栈使用 
	int i=0,d[MS];            // d数组作为存储孩子结点链接到双亲结点
	int top=-1;               // top作为两个栈的栈顶指针
	T=NULL;                   // 给树根指针置空
	while(S[i])
	{ switch(S[i])
	  { case ' ':break;         // 对空格不做任何处理
		case '(': top++;stack[top]=p; d[top]=0;break;
			                    // P指针进stack栈，O进d栈，表明待扫描的孩子结点
                                  // 将链接到stack栈顶元素所指结点的第一个指针域
		case ')': top--;break;     // stack和d退栈
		case ',':d[top]++;         // 待读入的孩子结点将链接到stack栈顶元素
                                   // 所指结点的下一个指针域
			    break;
		default:
			if(!(p=(CTree)malloc(sizeof(CTNode)))) // 建树结点
            exit(1);
			p->data=S[i];
			for(int i=0;i<MAX_SON_SIZE;i++)
			 p->child[i]=NULL; // 使p结点成为树根结点或链接到双亲结点对应的指针域
			if(!T) T=p;
			else stack[top]->child[d[top]]=p;
		}
		i++;                       // 准备处理下一个字符
	}
}// CreateTree

void PreOrderTree(CTree T,void Visit(TElemType))
{  // 先序遍历由T指针所指向的树
	if(T) {
		Visit(T->data);                         // 访问根结点
		for(int i=0;i<MAX_SON_SIZE;i++)
			  PreOrderTree(T->child[i],Visit);  // 递归遍历每一个子树
	}	
}// PreOrderTree

void PostOrderTree(CTree T,void Visit(TElemType))
{  // 后序遍历由T指针所指向的树
	if(T) 
	 {     for(int i=0;i<MAX_SON_SIZE;i++)
			  PostOrderTree(T->child[i],Visit);  // 递归遍历每一个子树
			Visit(T->data);   // 访问根结点
	}
}// PostOrderTree

typedef CTree ElemType;            // 定义队列中元素类型ElemType为CTree
# include "SqQueue.h"               //包含循环队列数据对象的描述及相关操作
void LevelOrderTree(CTree T,void Visit(TElemType))
{     // 按层遍历由T指针所指向的树
	SqQueue Q;                           // 定义一个队列Q，其元素类型为CTree 
	CTree p;
    InitQueue_Sq(Q,MAX_TREE_SIZE,10);         // 初始化循环队列
	if(T) EnQueue_Sq(Q,T);                    // 非空的根指针进队
	while(!QueueEmpty_Sq(Q))                  // 当队列非空时执行循环
	{	DeQueue_Sq(Q,p);                      // 从队列中删除一个结点指针
	    Visit(p->data);                       // 输出结点的值
		for(int i=0;i<MAX_SON_SIZE;i++)       // 非空的孩子结点指针依次进队
			if(p->child[i])
		     EnQueue_Sq(Q,p->child[i]);
	}
}// LevelOrderTree

bool SearchTree(CTree T,TElemType &e)
{    // 在由T指针所指向的树中查找元素e，查找成功，返回true；否则返回false
	if(!T) return false;                   // 树空返回false
	else {
		if(T->data==e) {
			e=T->data;return true;          // 带回结点值并返回true
		}
		for(int i=0;i<MAX_SON_SIZE;i++)     // 向每棵子树继续查找
			if(SearchTree(T->child[i],e)) return true;
			return false;                   // 查找不成功返回false
	}
}// SearchTree   

void PrintTree(CTree T)
{  // 以广义表形式输出按孩子链表存储的树
	int i;
	if(T) {
		cout<<T->data<<' ';                      // 输出根结点的值
		for(i=0;i<MAX_SON_SIZE;i++)              // 判T结点是否有子树
			if(T->child[i]) break;
			if(i<MAX_SON_SIZE)                  // 有子树时向下递归
			{	cout<<'(';                       // 输出表的左括号
				PrintTree(T->child[0]);          // 输出第一棵子树
	        for(i=1;i<MAX_SON_SIZE;i++)          // 输出其余各棵子树
			{	if(T->child[i]) cout<<',';
				PrintTree(T->child[i]);
			}
			cout<<')';                          // 输出表最后的右括号
		}
	}
}// PrintTree

int TreeDepth(CTree T)
{  // 求由指针T所指向的树的深度
	if(!T) return 0;                    // 空树的深度为0
	else {
		int max=0;                      // 用来保存子树中的最大深度,初值为0
		for(int i=0;i<MAX_SON_SIZE;i++) // 计算出一棵子树的深度并赋给变量k
		{	int k=TreeDepth(T->child[i]);
			if(k>max) max=k;              // 把当前深度最大者的值赋给 max
		}
		return max+1;                    // 返回树的深度，它等于子树的最大深度加1
	}
}// TreeDepth

void DestroyTree(CTree &T)
{
	if(T){
		for(int i=0;i<MAX_SON_SIZE;i++)       // 撤销根结点的所有子树
			DestroyTree(T->child[i]);
		free(T);                              // 撤销根结点
		T=NULL;                               // T置空
	}
}// DestroyTree

