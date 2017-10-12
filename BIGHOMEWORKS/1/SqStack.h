# define STACK_INIT_SIZE  100      // 顺序栈 (默认的)的初始分配最大容量
# define STACKINCREMENT  10        // (默认的)增补空间量
 
typedef struct {
  ElemType  *stack;                  // 存储数据元素的一维数组
  int top;                         // 栈顶指针
  int stacksize;                   // 当前分配的数组容量（以ElemType为单位）
  int incrementsize;	           // 增补空间量（以ElemType为单位）
}SqStack;

void InitStack_Sq(SqStack &S, int maxsize=STACK_INIT_SIZE,
                                 int incresize=STACKINCREMENT ) 
{
     S.stack=(ElemType *)malloc(maxsize*sizeof(ElemType)); // 为顺序栈分配初始存储空间
     if(!S.stack)  exit(1);                                // 存储空间分配失败
      S.top=-1;                                            // 置栈空
      S.stacksize=maxsize;                                 // 顺序栈的当前容量
      S.incrementsize=incresize;                           // 增补空间
}// InitStack_Sq

int StackLength_Sq(SqStack S)
{
	return S.top+1;
}// StackLength_Sq

bool Push_Sq(SqStack &S,ElemType e)
{  //在顺序栈的栈顶插入元素e
  if(S.top==S.stacksize-1)  {               
S.stack =(ElemType *)realloc(S.stack,(S.stacksize+S.
incrementsize)*sizeof(ElemType)); // 栈满，给顺序栈增补空间
  if(!S.stack)     return false;                // 分配存储空间失败
  S.stacksize+=S.incrementsize; 
 }
 S.stack[++S.top]=e;                             // 栈顶指针上移，元素e进栈
  return true;   
}// Push_Sq

bool Pop_Sq(SqStack &S,ElemType &e)
{   // 删除顺序栈栈顶元素，并让e返回其值
  if(S.top==-1)  return false; 
  e=S.stack[S.top--];  
       return true;    
}// Pop_Sq

bool GetTop_Sq(SqStack S, ElemType &e)
{   //取顺序栈栈顶元素，并让e返回其值
if(S.top==-1)  return false;    
  e=S.stack[S.top];      
  return true;    
}// GetTop_Sq

bool StackEmpty_Sq(SqStack S)
{ if(S.top==-1)  return true;
   else return false;
}// StackEmpty_Sq


void DestroyStack_Sq(SqStack &S )
{
   free(S.stack);
   S.stack=NULL;
   S.stacksize=0;
   S.top=-1;
}// DestroyStack_Sq

