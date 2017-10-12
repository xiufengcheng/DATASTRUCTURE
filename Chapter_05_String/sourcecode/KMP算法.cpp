# include "stdlib.h"         // 该文件包含malloc()、realloc()和free()等函数
# include "iostream.h"       // 该文件包含标准输入输出流cout和cin
# include "DSqString.h"      // 该文件中包含动态顺序串的相关定义及操作

void get_next(DSqString T,int next[])
{
	int  j=1,k=0;
	next[0]=-1; 
	next[1]=0;
	while(j<T.length)
	{
		if(T.str[j]==T.str[k])
		{
			next[j+1]=k+1;
			j++;  k++;
		}
		else if(k==0)
		{
			next[j+1]=0;
			j++;
		}
		else k=next[k];
	}
}// get_next

bool Index_KMP(DSqString S,DSqString T,int next[],int &pos)
{    // 利用模式串T的next函数求T在主串S中的位置
   int i=0,j=0;                       // i和j分别扫描主串S和子串T
   while(i<S.length&&j<T.length)      
   {  if(j==-1||S.str[i]==T.str[j])   // 继续比较下一个字符
      {  i++;  
  j++;
      }
      else  j=next[j];                 // 模式串向右移动
   }
   if(j==T.length)  { pos=i-T.length; return true;  }
   else return false;
}// Index_KMP

void main()
 {
	int next[10],pos;
	DSqString S1,S2,S3;
	StrAssign_Sq(S1,"aild");                       // 串S1赋初值
	StrAssign_Sq(S2,"children");                    // 串S2赋初值
    get_next(S1,next);
	if(Index_KMP(S2,S1,next,pos))
	cout<<"匹配成功！pos="<<pos<<endl;
	else cout<<"匹配失败！"<<endl;
    StrAssign_Sq(S3,"ild");                         // 串S3赋初值
	get_next(S3,next);
	if(Index_KMP(S2,S3,next,pos))
	cout<<"匹配成功！pos="<<pos<<endl;
	else cout<<"匹配失败！"<<endl;
}
