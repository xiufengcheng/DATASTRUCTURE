# include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
# include "iostream.h"     // 该文件包含标准输入输出流cout和cin
# define MAXVALUE  10000       // 叶结点的权值最大值
# define MAXBIT  10           // 最大编码位数
# include "HuffmanTree.h"      // 该文件包含构造哈夫曼树和哈夫曼编码的操作
void main()
{
   int i,j,*w,n;
   HuffmanTree HT;
   HuffmanCode HC;
   cout<<"请输入权值的个数：";
   cin>>n;
   w=(int*)malloc(n*sizeof(int));         // 动态生成存放n个权值的空间
   cout<<"请依次输入"<<n<<"个权值(整型)：";
   for(i=0;i<=n-1;i++)
     cin>>w[i];                            // 依次输入权值
   HuffmanTreeing(HT,w,n);                 // 根据w所存的n个权值构造赫夫曼树HT
   HuffmanCoding(HT,HC,n);                 // n个赫夫曼编码存于HC
   for(i=0;i<n;i++)                        // 依次输出赫夫曼编码
   {   cout<<"Weight="<<HT[i].weight<<"  Code="; 
       for(j=HC[i].start;j<MAXBIT;j++)
		     cout<<HC[i].bit[j];
	   cout<<endl;
 }
}
