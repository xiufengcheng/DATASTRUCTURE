typedef char ElemType;         // 定义广义表元素类型ElemType为字符型
# include "stdlib.h"           // 该文件包含malloc()、realloc()和free()等函数
# include "iostream.h"         // 该文件包含标准输入输出流cout和cin
# include "DSqString.h"        // 该文件包含DSqString类型的基本操作
# include "GList.h"            // 该文件中包含广义表数据对象的描述及相关操作

void main()
 {
   char p[80];
   DSqString t,hsub;
   GList n,m;
   InitGList(n);                        // 初始化广义表n，n为空表
   cout<<"空广义表n的深度="<<GListDepth(n)<<"，n是否空？";
cout<<GListEmpty(n)<<"(1:是 0:否)"<<endl;
   cout<<"请输入广义表n(书写形式：空表：()，单原子：(a)，其他：(a,(b),c))："<<endl;
   cin>>p;                                // 将描述广义表n的字符串赋给p
   StrAssign_Sq(t,p);                     // 将p转换为DSqString类型的t
   StrAssign_Sq(hsub,"");
   CreateGList(n,t);                      // 根据t创建广义表n
   cout<<"广义表n的长度="<<GListLength(n);
   cout<<"，深度="<<GListDepth(n)<<"，n是否空？"<<GListEmpty(n);
cout<<"(1:是 0:否)"<<endl;
   cout<<"遍历广义表n：";
   Traverse_GL(n);                          // 遍历广义表n
   CopyGList(m,n);                          // 复制广义表m=n
   cout<<endl<<"复制广义表m=n，m的长度="<<GListLength(m);
   cout<<"，m的深度="<<GListDepth(m)<<endl;
   cout<<"遍历广义表m：";
   Traverse_GL(m);                          // 遍历广义表m
   DestroyGList(m);                         // 撤销广义表m，释放存储空间
   m=GetHead(n);                            // 生成广义表n的表头元素，并由m指向
   cout<<endl<<"m是n的表头元素，遍历m：";
   Traverse_GL(m);                          // 遍历广义表m
   DestroyGList(m);                         // 撤销广义表m，释放存储空间
   m=GetTail(n);                   // 将广义表n的表尾生成为广义表，并由m指向
   cout<<endl<<"m是由n的表尾形成的广义表，遍历广义表m：";
   Traverse_GL(m);                          // 遍历广义表m
   InsertFirst_GL(m,n);  // 将广义表n插到广义表m中，并作为m的第1个元素(表头)
   cout<<endl;
   cout<<"插入广义表n为m的表头，遍历广义表m：";
   Traverse_GL(m);                           // 遍历广义表m
   DeleteFirst_GL(m,n);                // 删除广义表m的表头，并由n指向删除的表头
   cout<<endl<<"删除m的表头，并由n指向m的表头，遍历广义表m：";
   Traverse_GL(m);                        // 遍历广义表m
   cout<<endl<<"遍历广义表n(广义表m的原表头)：";
   Traverse_GL(n);                          // 遍历广义表n
   cout<<endl;
   DestroyGList(m);                         // 撤销广义表m、n，并释放存储空间
   DestroyGList(n);  
 }
