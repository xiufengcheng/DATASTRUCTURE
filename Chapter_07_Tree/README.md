## 第六章（树）目录
>* <font size = 8 color = blue>[森林](#森林)</font>
>>* <font size = 8 color = blue>[树](#树)</font>
>>>* <font size = 8 color = blue>[二叉树](#二叉树)</font>
>>>>* <font size = 8 color = blue>[线索二叉树](#矩阵的压缩存储)</font>
>>>* <font size = 8 color = blue>[哈夫曼树](#哈夫曼树)</font>

-----------------------------

## 树(tree)
树是一种非线性结构，树与线性表的逻辑关系不同。
### 定义
- **树**：是n(n≥0)个结点（元素）构成的有限集合。当n=0时，称这棵树为空树。在一棵非空树T中：
    - 有且只有一个特殊的结点称为树的根结点，根结点没有前驱结点；
    - 当n＞1，除根结点之外的其余数据元素被分成m(m>0)个互不相交的集合T1,T2,…,Tm，其中每一个集合Ti(1≤i≤m)本身又是一棵树。树T1,T2,…,Tm 称为这个根结点的子树
- **结点**：是数据元素的别名。
- **集合**：**线性表**对应的是**序列**，**树**对应的是**集合**。
- **结点的度**：树中结点所拥有的子树的个数。
- **树的度**：树中各结点度的最大值。
    - 二叉树的度为2。
- **叶子结点**（终端结点）：度为0的结点。
- **分枝结点**（非终端结点）：度不为0的结点。
- **孩子**：树中一个结点的子树的根结点。
- **双亲**：树中一个孩子结点的上层结点（唯一）。
- **兄弟**：具有同一个双亲的孩子结点互成为兄弟。
- **子孙**：一个结点的所有子树中的结点称之为该结点的子孙节点。
- **祖先**：从根结点到该结点所经分支上的所有结点。
- **层数**：根结点的层数规定为1，其余结点的层数等于它的双亲结点的层数+1。
- **深度**：所有结点的最大层次。
- **堂兄弟**：双亲在同一层，且双亲不同的结点互为堂兄弟。
- **有序树**：如果一棵树中结点的各子树从左到右是有次序的，即若交换了某结点各子树的相对位置则构成不同的树，称这棵树为有序树；反之，则称为无序树。
- **森林**：m(m≥0)棵不相交的树的集合称为森林。自然界中树和森林是不同的概念，但在数据结构中，树和森林只有很小的差别，任何一棵树，删去根结点就变成了森林。

 <img width="600"  src="/Chapter_07_Tree/img/1.png"/>

- 注意事项：
    - 递归方法是树结构算法的基本特点
    - 树的根节点唯一
    - n>0：子树的个数从定义上没有限制，可以很大。
    - **子集互不相交**：
        - 某结点不能同时属于两个子集
        - 两个子集的结点之间不能有关系。 

### **树的逻辑表示**
- 直观表示法
    - 圆圈+数字(字母)+连线(无向)
    - 根节点在上，子树画下面(一颗倒长的树)
- 形式化表示法 
    - T=(D,R)
        - D:D为树T中结点的集合
        - R:树中结点之间关系的集合
    - 当树为空树时，D=φ 
    - 当树T不为空树时，D={Root}∪D<sub>f</sub>
        - Root为树T的根结点
        - D<sub>f</sub>为树T的根Root的子树集合。
        - D<sub>f</sub>=D<sub>1</sub>∪D<sub>2</sub>∪…∪D<sub>m</sub>且D<sub>i</sub>∩D<sub>j</sub>=φ,(i≠j,1≤i≤m,1≤j≤m)
    - 当树T中结点个数n≤1时，R=φ
    - 当树T中结点个数n>1时有：R={<Root,r<sub>i</sub>>,i=1,2, …,m}
        - Root为树T的根结点
        - r<sub>i</sub>是树T的根结点Root的子树Ti的根结点。
- 凹入表示法
     <img width="300"  src="/Chapter_07_Tree/img/2.png"/>
- 文氏图表示法 
     <img width="600"  src="/Chapter_07_Tree/img/3.png"/>
- 广义表表示法
        - (A(B(E(J),F),C(G(K,L)),D(H,I)))

### 树的基本性质
#### 性质1 树中的结点数等于所有结点的度数加1。
证明：每个结点与指向它的一个分支一一对应，所以除根结点之外的结点数等于所有结点的分支数（即度数），从而可得树中的结点数等于所有结点的度数加1。
#### 性质2 度为d的树中第i层上至多有d<sup>i-1</sup>个结点（i≥1）。 
证明：用数学归纳法证明。
#### 性质3 为k的d叉树至多有d<sup>k</sup>/d-1个结点。 
证明：满d叉树
#### 性质4 具有n个结点的d叉树的最小深度为[log<sub>d</sub>(n(d-1)+1)]
证明：根据性质3得来
-------------

### 树的ADT
```C++
ADT Tree{
  Data：
         树是由一个根结点和若干棵子树构成。
         树中结点具有相同数据类型及层次关系。
  Operation：
         InitTree(&T)
         操作结果：构造一棵空树T。
         CreateTree(&T,S)
         初始条件：串S是以广义表形式表示的树。
         操作结果：按S构造一棵树T。
         OrderTree(T,Visit( ))     
         初始条件：树T存在，Visit是对结点操作的应用函数。
         操作结果：按某种次序对T的每个结点调用函数Visit()一次且至多一次。一旦visit()失败，则操作失败。
         SearchTree(T,&e)
         初始条件：树T存在。
         操作结果：在树T中查找元素e，若查找成功，返回true；否则返回false。
         PrintTree(T)
         初始条件：树T存在。
         操作结果：以某种形式输出树T。
         TreeDepth(T)
         初始条件：树T存在。
         操作结果：求树T的深度。
         DestroyTree(&T)    
         初始条件：树T存在。
         操作结果：撤销树T。
} ADT Tree 

```
-------------

### 树的应用
#### 例1：Internet域名管理
 <img width="500"  src="/Chapter_07_Tree/img/4.png"/>
 <img width="500"  src="/Chapter_07_Tree/img/5.png"/>
#### 例2：网络信息组织
 <img width="600"  src="/Chapter_07_Tree/img/7.jpg"/>
<img width="600"  src="/Chapter_07_Tree/img/6.jpg"/>
#### 例3：中文信息处理
 <img width="600"  src="/Chapter_07_Tree/img/8.png"/>

### 树的存储结构
- 不仅要存储各节点的数据信息，还要存储结点之间的关系（父子关系）

#### 为什么采用链式存储一颗树？

- 答：树中各节点的度不一致，无论按何种顺序将树种所有结点存储到数组中，都比较难直接反映数据元素的逻辑关系（满树和完全树除外），所以，树的存储结构一般采用链式存储。又可分为数组表示法和链表表示法
-------------
### 双亲表示法
树的双亲表示法就是用指针表示出每个结点的双亲在存储空间的位置信息。这种表示法的优点是容易寻找双亲结点，因而对于实现Parent(T,e)操作和Root(T)等操作很方便，其缺点是不容易找孩子结点，也不能反映各兄弟间的关系，因而对实现LeftChild(T,e)和RightSibling(T,e)等操作则比较困难。 

#### 双亲数组法
- **双亲数组法**就是用一维结构体数组依次存储树中的各结点，数组中的一个元素表示树中的一个结点，数组元素中包括**结点本身的信息**和**结点的双亲结点在数组中的下标**。

 <img width="700"  src="/Chapter_07_Tree/img/9.png"/>
```c++
#define MAX_TREE_SIZE  100            
typedef struct {
  TElemType data; 
  int parent;                       
}PTreeNode;                        
PTreeNode PTree[MAX_TREE_SIZE];
```

#### 双亲链表法
- **双亲链表法**就是用一组任意的存储单元存储树中各结点，结点中包括结点本身的信息和指向该结点的双亲的指针。

### 孩子表示法
树的孩子表示法就是用指针表示出每个结点的孩子在存储空间的位置信息。这种表示法的优点是容易寻找孩子结点，因而对于实现LeftChild(T,e)和RightSibling(T,e)等操作很方便，其缺点是不容易找双亲结点，因而对实现Parent(T,e)操作和Root(T)等操作则比较困难。
#### 孩子数组法
- **孩子数组法**用一维结构体数组依次存储树中的各结点，数组中的一个元素表示树中的一个结点，数组元素中包括**结点本身的信息**和**结点的孩子结点在数组中的下标**。结点中指针（相对指针，下标）的个数等于树的度，若某结点无孩子，其相应的指针域为空（用-1表示）。
```c++
typedef struct {
  TElemType data;                      
  int child[MAX_SON_SIZE];             
}CTreeNode;                           
CTreeNode CTree[MAX_TREE_SIZE];
```
 <img width="700"  src="/Chapter_07_Tree/img/10.png"/>

 #### **孩子链表法**（源代码所用）
 - **孩子链表法**就是用一组任意的存储单元存储树中各结点，结点中包括结点本身的信息和指向该结点的所有孩子的指针，结点中指针域的个数等于树的度数。
- 特点：同**孩子数组法**
```c++
typedef struct CTNode {
  TElemType data;                     
  struct CTNode *child[MAX_SON_SIZE]; 
}CTNode,*CTree;                       
```
 <img width="700"  src="/Chapter_07_Tree/img/11.png"/>

### 双亲孩子表示法
- 如果在操作中既要方便寻找双亲，又要方便寻找孩子，则可将上述两种存储结构进行结合，即既存储双亲在存储空间中的位置，又存储孩子在存储空间中的位置，这就是双亲孩子表示法。这种方法的优点是寻找双亲和孩子都比较方便，因而能够较方便地实现树的各种基本操作，但它是以牺牲空间为代价而换取时间的。  

#### 双亲孩子数组法
- **双亲孩子数组法**就是用一维数组存储树中各结点，数组元素中包括结点本身的信息以及双亲结点和所有孩子结点在数组中的下标。
```c++
typedef struct {
  TElemType data;                         
  int parent;                             
  int child[MAX_SON_SIZE];                
}PCTreeNode;                             
PCTreeNode PCTree[MAX_TREE_SIZE];
```
 <img width="700"  src="/Chapter_07_Tree/img/12.png"/>

 #### 双亲孩子链表法
 - **双亲孩子链表法**就是把某个结点的所有孩子排列起来，并用单链表作为它的存储表示。n个结点的树，用n个这样的单链表组成，每个单链表设立一个表头结点，它有3个域：数据域data表示树的一个结点的数据信息，指针域（下标）parent为该结点的双亲在数组中的下标，指针域link指向该结点的孩子单链表的第一个结点。n个这样的表头结点用一维数组表示。
 <img width="700"  src="/Chapter_07_Tree/img/13.png"/>

 #### 双亲数组孩子链表法
 - 是将双亲数组表示法和孩子链表表示法有机地结合，即把某个结点的所有孩子排列起来，并用单链表作为它的存储表示。n个结点的树，用n个这样的单链表组成，每个单链表设立一个表头结点，它有3个域：数据域data表示树的一个结点的数据信息，指针域（下标）parent为该结点的双亲在数组中的下标，指针域link指向该结点的孩子单链表的第一个结点。n个这样的表头结点用一维数组表示。

 <img width="700"  src="/Chapter_07_Tree/img/14.png"/>

## 树的基本操作
### 初始化

```c++
void InitTree(CTree &T)
{ 
	T=NULL;
}// InitTree 
```
### 创建树 
生成树的镜像
```c++
# define MS 10                // 栈空间的大小
void CreateTree(CTree &T,char *S)
{ 
  CTree stack[MS],p;   
  int i=0,d[MS],top=-1;       
  T=NULL;               
  while(S[i])
  { switch(S[i])
    {  case ' ':break;   
       case '(': top++;stack[top]=p; d[top]=0;break;
       case ')': top--;break;  
       case ',':d[top]++;break;
       default: if(!(p=(CTree)malloc(sizeof(CTNode)))) exit(1);
	       p->data=S[i];
	       for(int i=0;i<MAX_SON_SIZE;i++)
		p->child[i]=NULL; 
	       if(!T) T=p;
	       else stack[top]->child[d[top]]=p;
     }
     i++;     
   }
}// CreateTree
```
### 遍历（递归思想）
#### 先序
```c++
void PreOrderTree(CTree T,void Visit(TElemType))
{  
   if(T) 
   {
       Visit(T->data);                         
        for(int i=0;i<MAX_SON_SIZE;i++)
	PreOrderTree(T->child[i],Visit);  
    }	
}// PreOrderTree
```

#### 后序
```c++
void PostOrderTree(CTree T,void Visit(TElemType)) 
{  
     if(T)   
     {     
          for(int i=0;i<MAX_SON_SIZE;i++)
	 PostOrderTree(T->child[i],Visit);  
          Visit(T->data);   
     }
}// PostOrderTree
```

#### 层序
```c++
typedef CTree ElemType;            
void LevelOrderTree(CTree T,void Visit(TElemType))
{     
     SqQueue Q;                           
     CTree p;
     InitQueue_Sq(Q,MAX_TREE_SIZE,10);   
     if(T) EnQueue_Sq(Q,T);              
     while(!QueueEmpty_Sq(Q))               
     {   DeQueue_Sq(Q,p);                
          Visit(p->data);                   
          for(int i=0;i<MAX_SON_SIZE;i++) 
	if(p->child[i])   EnQueue_Sq(Q,p->child[i]);
     }  
}// LevelOrderTree
```

### 查找
```c++
bool SearchTree(CTree T,TElemType &e)
{   
    if(!T) return false;                 
    else {
	  if(T->data==e) 
            {  e=T->data; return true;  }
	  for(int i=0;i<MAX_SON_SIZE;i++)  
	     if(SearchTree(T->child[i],e)) return true;
	  return false;                
	 }
}// SearchTree 
```

### 输出(为广义表)
```c++
void PrintTree(CTree T)
{  // 以广义表形式输出按孩子链表存储的树
    int i;
    if(T) {
	cout<<T->data<<' ';               
	for(i=0;i<MAX_SON_SIZE;i++)       
                   if(T->child[i]) break;
                if(i<MAX_SON_SIZE)            
                {   cout<<'(';                
	     PrintTree(T->child[0]);   
	     for(i=1;i<MAX_SON_SIZE;i++)   
	     {   if(T->child[i]) cout<<',';
	         PrintTree(T->child[i]);
                     }
	     cout<<')';                    
	 }
            }
}// PrintTree
```

### 求深度
```c++
int TreeDepth(CTree T)
{  
    if(!T) return 0;                    
    else {
  	  int max=0;                      
	  for(int i=0;i<MAX_SON_SIZE;i++) 
	  {  int k=TreeDepth(T->child[i]);
	     if(k>max) max=k;    
	   }
	   return max+1;          
	}
}// TreeDepth
```
### 撤销
```c++
void DestroyTree(CTree &T)
{
    if(T)
    {
      for(int i=0;i<MAX_SON_SIZE;i++)  
	DestroyTree(T->child[i]);
      free(T);                         
      T=NULL;                          
    }
}// DestroyTree
```

## [源代码下载](/Chapter_07_Tree/sourcecode)

