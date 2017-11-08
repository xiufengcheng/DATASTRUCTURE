typedef char TElemType;      // 定义树中元素类型TElemType为字符型
 # include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
 # include "iostream.h"     // 该文件包含标准输入输出流cout和cin
 # define MAX_TREE_SIZE  100         // 树中结点的最大个数
 # define MAX_SON_SIZE  3            // 树的度
 # include "CTree.h"                 // 该文件包含树数据对象的描述及相关操作
 	
 void Visit(TElemType e)             // 访问函数定义为输出操作
 {
   cout<<e<<' ';
 }

void main()
{
	CTree T;
	InitTree(T);                 
	char str[50];                          // 存放用广义表字符表示的树
	cout<<"输入一棵"<<MAX_SON_SIZE<<"度树的广义表字符串：";
	cin>>str;
	CreateTree(T,str);                    // 创建树
	cout<<"先序遍历结果："; 
	PreOrderTree(T,Visit); 
	cout<<endl<<"后序遍历结果：";
	PostOrderTree(T,Visit);
	cout<<endl<<"层序遍历结果：";
	LevelOrderTree(T,Visit); 
	cout<<endl<<"按广义表形式输出的"<<MAX_SON_SIZE<<"度树为：";
	PrintTree(T);
	cout<<endl;
	cout<<"树的深度："<<TreeDepth(T)<<endl;
	cout<<"输入待查找的一个字符：";
	char ch;
	cin>>ch;
	if(SearchTree(T,ch))  cout<<"查找成功！"<<endl;
	else cout<<"查找失败！"<<endl;
	DestroyTree(T);
}
