typedef int ElemType;      // 顺序表中元素类型为int
#include "stdlib.h"       // 该文件包含malloc()、realloc()和free()等函数
#include "iomanip.h"      // 该文件包含标准输入输出流cout和cin及控制符setw()
#include "SqList.h"       // 该文件中包含顺序表数据对象的描述及相关操作


   
//算法2.1:合并两个顺序表，B接在A后面，消除重复元素 

void Union(SqList &lista, SqList listb)
	{  
	   ElemType e;
	   lista.length = ListLength_Sq(lista);
	    //cout<<"a线性表的长度为"<<lista.length<<endl;
   	    //cout<<"a线性表的大小为"<<lista.listsize<<endl;
   	    //cout<<"b线性表的长度为"<<listb.length<<endl;
   	    //cout<<"b线性表的大小为"<<listb.listsize<<endl;
	   while(!ListEmpty_Sq(listb))
	   {
	   	 ListDelete_Sq(listb,0,e);
	   	 //ListTraverse_Sq(listb);  
	   	 if(LocateElem_Sq(lista,e)==-1){
	   	 ListInsert_Sq(lista,lista.length, e);
			}
	   }
	   DestroyList_Sq(listb);
   	}


//算法2.1的另一个实现 
void Union2(SqList &lista, SqList listb)
	{  ElemType e;
	   lista.length = ListLength_Sq(lista);
	   listb.length = ListLength_Sq(listb);
	   for(int i=0;i <= listb.length;i++)
	   {
	   	    GetElem_Sq(listb, i, e);
	   	    if(LocateElem_Sq(lista, e)== -1)
	   	       ListInsert_Sq(lista,  lista.length, e);
	   }
	    DestroyList_Sq(listb);
   } //union
 

//算法2.2：Purge,消除相同元素 
void Purge(SqList &La, SqList Lb)//构造线性表La，使得其只包含Lb中所有值不相同的 
	{  ElemType e;
	   InitList_Sq(La,100,50); 
	  while(!ListEmpty_Sq(Lb))
	   {
	   	 ListDelete_Sq(Lb,0,e);
	   	 if(LocateElem_Sq(La,e)==-1)
	   	 ListInsert_Sq(La,La.length,e);
	   }
	 
	    DestroyList_Sq(Lb);
   } 
 
 //算法2.3 ：判断两个集合A,B是否相等
 bool isequal(SqList &La, SqList Lb) 
 {
 	//若线性表La和Lb不仅长度相等，且所含数据元素也相同，则返回true
    //否则返回false 
    SqList Lc;
    ElemType e;
    bool found;
    La.length = ListLength_Sq(La);
    Lb.length = ListLength_Sq(Lb);
    if(La.length!=Lb.length)return false;
    else
    {
    	InitList_Sq(Lc);
    	for(int j=0;j<=La.length-1;j++)
    	{
    		 GetElem_Sq(La,j,e);
    		 ListInsert_Sq(Lc,j,e);
    	}
    	
		found = true;
    	//ListTraverse_Sq(Lc); 
		for(int k=0;k<=Lb.length-1;k++)
    	{    int i=-1;
    		 GetElem_Sq(Lb,k,e);
    		 i = LocateElem_Sq(Lc,e);
    		 if(i==-1) found = false;
    		 else ListDelete_Sq(Lc,i,e);
    	}
    	ListTraverse_Sq(Lc); 
    	if(found&&ListEmpty_Sq(Lc))return true;
    	else return false;
    	DestroyList_Sq(Lc);
    }
 }
 
//已知线性表La和Lb中的数据元素按值非递减排列（有序表）
//归并La和Lb得到新的线性表Lc,Lc的数据元素也按值非递减排列
void MergeList(SqList La, SqList Lb, SqList &Lc)
{
   InitList_Sq(Lc);
   int i=1; int j=1; int k=0;
   int ai,bj;
   La.length = ListLength_Sq(La);
   Lb.length = ListLength_Sq(Lb);
   while((i<=La.length)&&(j<=Lb.length))//La,Lb均非空
   {
   	 GetElem_Sq(La,i,ai);GetElem_Sq(Lb,j,bj);
	 if(ai<=bj) {ListInsert_Sq(Lc, ++k, ai);++i;}
	 else{ListInsert_Sq(Lc, ++k, bj); ++j;}
   }     

   while(i<=La.length)//b空a不空 
   {
   	  GetElem_Sq(La,i++,ai); ListInsert_Sq(Lc, ++k, ai);
   }
   
   while(j<=Lb.length)//a空b不空 
   {
      GetElem_Sq(Lb,j++,bj);ListInsert_Sq(Lc, ++k, bj);	
   }
}
   

int main()
 {
 	//从顺序表中删除第i个元素的例子 
 	/*
 	SqList mylist;
  	int i,x,a[]={6,8,16,2,34,56,7,10,22,45};
  	InitList_Sq(mylist, 50,10);           // 初始化顺序表mylist
  	for(i=0;i<10;i++)
  	if(!ListInsert_Sq(mylist, i, a[i]))  // 将a[i]插入到顺序表中第i+1个元素之前
     { 
	 	cout<<"插入失败！"<<endl;
        return 0;
     }
	cout<<"删除前的顺序表为：";
  	ListTraverse_Sq(mylist);           // 调用遍历函数显示mylist
	if(!ListDelete_Sq(mylist,4, x))     // 删除顺序表中第5个元素
    {  cout<<"删除失败！"<<endl;
       return 0;
     }
	cout<<"被删除元素是："<<x<<endl;
	cout<<"删除后的顺序表为：";
   ListTraverse_Sq(mylist);           // 调用遍历函数显示mylist
   DestroyList_Sq(mylist);            // 调用撤销函数撤销mylist以释放空间
   return 0;
   
  */
  
  
  
  
    //算法的使用: 
    SqList Lista, Listb;
    int m,n;
    
    ElemType la[] = {1,2,3,5,6};
   // ElemType lb[] = {7,0,4,9,6};
    ElemType lb[] = {4,1,2,3,6};
    InitList_Sq(Lista,100,50);   
    InitList_Sq(Listb,100,50);  
    for(m=0;m<5;m++)
  	if(!ListInsert_Sq(Lista, m, la[m]))  // 将la[i]依次插入顺序表Lista 
     { 
	 	cout<<"插入失败！"<<endl;
        return 0;
     }
          
	for(n=0;n<5;n++)
	if(!ListInsert_Sq(Listb, n, lb[n]))// 将lb[i]依次插入顺序表Listb
     { 
	 	cout<<"插入失败！"<<endl;
        return 0;
     }
     
    cout<<"操作前的SqLista表为：";
    ListTraverse_Sq(Lista); 
    cout<<"操作前的SqListb表为：";
    ListTraverse_Sq(Listb);  
     
    /*****************************/
    //Union(Lista,Listb);//算法2.1 
    //Union2(Lista,Listb);//算法2.1+ 
    //Purge(Lista,Listb);//算法2.2 
    //bool a = isequal(Lista,Listb);//算法2.3
	/****************************/
    
    cout<<"操作后的SqLista表为：";

	ListTraverse_Sq(Lista);  
    DestroyList_Sq(Lista);   
    
	return 0;
}
   
   


