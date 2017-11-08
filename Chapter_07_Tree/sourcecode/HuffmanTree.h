typedef struct {
 int weight;            
 int parent,lchild,rchild;
}HTNode,*HuffmanTree;                // 动态分配数组存储哈夫曼树;

typedef struct {
   int weight;                         // 结点的权值
   char bit[MAXBIT];                    // 存放编码序列的数组
   int start;                           // 编码的起始下标
}HTCode,*HuffmanCode;                  // 动态分配数组存储哈夫曼编码

void select(HuffmanTree HT,int i,int &x1,int &x2)
 {  // 返回哈夫曼树HT的前i个结点中权值最小和权值次小的树的根结点序号
// x1为其中序号(权值)较小的, x2为其中序号(权值)次小的
    int m1,m2;
	 m1=m2=MAXVALUE;                       // 初值为权值最大值
     x1=x2=0;
     for(int j=0;j<i;j++)
     { if(HT[j].weight<m1&&HT[j].parent==-1)    
       {  m2=m1;
          x2=x1;
          m1=HT[j].weight;
          x1=j;
        }
       else if(HT[j].weight<m2&&HT[j].parent==-1)
       {   m2=HT[j].weight;
           x2=j;
        }
     }
}// select

void HuffmanTreeing(HuffmanTree &HT,int *w,int n)
{   // w中存放n个权值,构造n个叶子结点的哈夫曼树HT
  int i,s1,s2;
  HT=(HuffmanTree)malloc((2*n-1)*sizeof(HTNode)); // 分配哈夫曼树的存储空间
  for(i=0;i<2*n-1;i++)                      // 数组初始化
   { if(i<n)HT[i].weight=w[i];               // 赋权值
     else  HT[i].weight=0;
     HT[i].parent=-1;                         // 双亲域为空
     HT[i].lchild=-1;                         // 左孩子域为空
     HT[i].rchild=-1;                         // 右孩子域为空
   }
  for(i=n;i<2*n-1;i++)                         // 构造哈夫曼树的n-1个非叶子结点
  {  select(HT,i,s1,s2);            // 选择两根结点权值最小和次小的两棵二叉树
            // 新二叉树存放在数组的第i个分量中,其权值是s1和s2的权值之和
HT[i].weight=HT[s1].weight+HT[s2].weight;  
      HT[i].lchild=s1;                 //新二叉树的左右孩子分别是s1和s2
      HT[i].rchild=s2;
      HT[s1].parent=HT[s2].parent=i;      // 数组的第i个分量是s1和s2的双亲
   }
}// HuffmanTreeing


void HuffmanCoding(HuffmanTree &HT,HuffmanCode &HC,int n)
 {    // 求n个字符(叶子结点)的哈夫曼编码HC
	 int i,j;
	 int child,parent;
	 HTCode cd;                                // 临时存放编码
	 HC=(HuffmanCode)malloc(n*sizeof(HTCode)); // 分配保存n个字符的编码空间
	 for(i=0;i<n;i++)                          // 求n个叶子的哈夫曼编码
	 { cd.start=MAXBIT-1;                      // 不等长编码的最后一位为MAXBIT-1
	   cd.weight=HT[i].weight;                 // 取得编码对应的权值
       child=i;                                // 从第i个叶结点开始
       parent=HT[child].parent;                // parent指向child双亲结点
       while(parent!=-1)              
       {    if(HT[parent].lchild==child)       // child是其双亲的左孩子
		    cd.bit[cd.start]='0';              // 其分枝赋值为'0'
       else                                    // child是其双亲的右孩子
		   cd.bit[cd.start]='1';               // 其分枝赋值为'1'
       cd.start--;                             // 起始位置向前进一位
       child=parent;                           // child指向其双亲
       parent=HT[child].parent;                // parent指向child双亲结点
      }
      for(j=cd.start+1;j<MAXBIT;j++)
		  HC[i].bit[j]=cd.bit[j];             // 保存每个叶子的编码
        HC[i].start=cd.start+1;               // 保存叶结点编码的起始位
        HC[i].weight=cd.weight;               // 保存编码对应的权值
    }
}// HuffmanCoding


