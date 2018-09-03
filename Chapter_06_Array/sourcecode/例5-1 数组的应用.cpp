typedef int ElemType;     // 定义数组元素类型ElemType为整型
# include "stdarg.h"      // 该文件包含va_start()、va_arg()、va_end()等函数
# include "stdlib.h"      // 该文件包含malloc()、realloc()和free()等函数
# include "iostream.h"    // 该文件包含标准输入输出流cout和cin
# include "string.h"      // 该文件包含C++串的定义及相关操作
 # include "Array.h"       // 该文件中包含数组数据对象的描述及相关操作
 # define  M 20           // 串的最大长度
 # define  N 10           // 串的最大长度
 int len1,len2;           // 串的实际长度
void SubString(char  *sub,char *str,int s,int len)
{
	char *p;
	int k;
	p=str+s;k=len;
	while(k)
	{*sub++=*p++;  k--;
	}
	*sub='\0';    // 添加串结束符
	sub=sub-len;   //  指针复位
}// SubString

void diagscan(Array mat,int &maxlen,int &jpos,int i,int j)
{   // 求该对角线上各段连续1的最长长度maxlen和起始位置jpos
	int eq=0,len=0,sj;            // 在一次扫描开始对eq和len初始化
	ElemType e;
	while(i<len2&&j<len1)
	{	Value(e,mat,i,j);            // 将mat[i][j]的值赋给e
	    if(e==1)
		{	len++;
			if(!eq)                 // 出现的第一个1，记下起始位置，改变状态
			{ sj=j;eq=1;  } 
		}
		else if(eq)                  // 求得一个公共子串      
		{	if(len>maxlen)           // 是到目前为止求得的最长公共子串
			{ maxlen=len;jpos=sj; }
			eq=0;len=0;              // 重新开始求新的一段连续出现的1
		}
		i++;j++;                      // 继续考察该对角线上当前的下一元素
}
}// diagscan

void diagmax1(Array mat,int &maxlen,int &jpos)
{	// 求数组mat中所有对角线上连续出现的1的最长长度maxlen和起始位置jpos
int i,j,k,istart;
	istart=0;                          // 第一条对角线起始元素行下标
	for(k=-(len1-1);k<=len2-1;k++)  // 当前对角线特征量为k,其上元素mat[i][j]满足i-j=k
	{ i=istart;          // 主对角线及与之平行的右上方对角线起始行坐标istart都为0
	  j=i-k;                                 // 由特征量关系求出对应的列坐标
	  diagscan(mat,maxlen,jpos,i,j);         // 求该对角线上各段连续1的长度
	  if(k>=0) istart++;  // 与主对角线平行的左下方对角线起始行坐标istart为1,2,…
}
    DestroyArray(mat);
}// diagmax1

int maxsamesubstring(char *string1, char *string2, char *sub)
{  // 本算法返回串string1和string2的最长公共子串sub及其长度
   ElemType e;
   char *p1,*p2;;
   int maxlen,jpos;
   Array mat;                         // 定义数组
   int i,j;
   len1=strlen(string1);
   len2=strlen(string2);
   InitArray(mat,2,len2,len1);       // 构造M×N的二维数组mat
   p1=string2;  p2=string1;
   for( i=0; i<len2; i++ )            //求出两个串的对应矩阵mat[ ][ ]
    for( j=0; j<len1; j++ )
 if(*(p1+i)==*(p2+j))
          Assign(mat,1,i,j);          // 将1 赋给mat[i][j]
       else  Assign(mat,0,i,j);       // 将0 赋给mat[i][j]      
    diagmax1(mat,maxlen,jpos);
                                 // 求得string1和string2的最长公共子串的长度maxlen
                                 // 以及它在string1中的起始位置jpos
    if (maxlen==0) *sub='\0';
    else SubString(sub,string1,jpos,maxlen);  // 求得最长公共子串
    return maxlen;
}// maxsamesubstring

void main()
 {
	 char str1[M],str2[N],sub[N];
	 int length;
	 cout<<"请输入第一个串：";
	 cin>>str1;
	 cout<<"请输入第二个串：";
	 cin>>str2;
	 length=maxsamesubstring(str1,str2,sub);
	 cout<<"最长公共子串为："<<sub<<"，长度为："<<length<<endl;
}
