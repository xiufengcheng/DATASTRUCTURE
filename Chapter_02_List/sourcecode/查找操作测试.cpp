
# include "stdio.h"
 # define LIST_INIT_SIZE  100
 typedef int ElemType;
typedef struct
{ ElemType  elem [LIST_INIT_SIZE];            //存储数据元素的一维数组
  int length;                                   //线性表的当前长度
} SqList;

int LocateElem_Sq( SqList L, ElemType e)
{  int i;
   for(i=0;i<L.length;i++)
    if(L.elem[i]==e)  return i;   // 找到满足判定的数据元素为第 i 个元素
      return -1;                  // 该线性表中不存在满足判定的数据元素
 }

 void main()
 {   int i;
   SqList L={{7,6,8 ,9,12,34,9,5},8} ;
   i=LocateElem_Sq( L,4);
  printf("i=%d",i);
  getchar();
  }
