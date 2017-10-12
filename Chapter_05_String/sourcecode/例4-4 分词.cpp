# include "stdlib.h"          // 该文件包含malloc()、realloc()和free()等函数
# include "iostream.h"        // 该文件包含标准输入输出流cout和cin
# include "DSqString.h"           // 该文件包含动态顺序串的相关定义及操作
# define  MaxDictionaryLen   10   // 分词词典的最大长度
# define MaxWordLen 12            // 汉语词的最大长度

typedef struct 
{
	DSqString word;
	int num;
}WORD;        

int Segmentation(DSqString D[],int n,DSqString Str,WORD Result[])
{  // 对汉字串Str进行分词,分词结果存放在数组Result中,并返回不同汉语词的个数,
// 其中D为分词词典
	int len,i,j,k=0,flag;                  // k统计不同汉语词的个数
	DSqString Sub;
	for(i=0;i<n;i++)                       // 对结果数组进行初始化
	{
		StrAssign_Sq(Result[i].word,"");
		Result[i].num=0;
	}
 StrAssign_Sq(Sub,""); 
	for(i=0;i<Str.length;)                 // 从下标为0处开始取词
	{
   for(len=MaxWordLen,flag=1;len>2&&flag;) // 当前分词长度为len
	   {
		if(i+len<Str.length)                    // 剩余长度大于等于len
    SubString_Sq(Str,Sub,i,len);          // 取长度为len子串
	    else                                    // 剩余长度小于len
      SubString_Sq(Str,Sub,i,Str.length-i); // 将剩余的字符作为子串
		for(j=0;j<n;j++)                 // 将取出的子串与分词词典进行匹配
		  if(!StrCompare_Sq(Sub,D[j]))      // 分词词典中有此字符串
		  {
         for(int m=0;m<k;m++)
		     if(!StrCompare_Sq(Sub,Result[m].word))// 结果数组中有此字符串(即汉语词)
	         { Result[m].num++; break;  }         // 该汉语的频率加1
		     if(m==k)                            // 结果数组中无此字符串(即汉语词)
	         { StrCopy_Sq(Result[k].word,Sub);   // 将取出的汉语词存放到结果数组中
         Result[k].num=1;                  // 新词的频率为1
         k++;                              // 新词数加1
	         }
	         i=i+len;flag=0; break;               // 取词成功,准备取下一个汉语词
	       }
		if(j==n) len=len-2;                // 分词词典中无此字符串,去掉最后一个汉字
	   }
	   if(len==2) i=i+len;	                // 只剩余一个汉字,从下一个汉字开始取词
	}
   return k;     
}// Segmentation




void main()
{
DSqString D[9]={{"促进",4},{"学生",4},{"创新素质发展",12},{"钢琴教学模式",12},{"研究与实验",10},{"很好",4},{"创新",4},{"素质",4},{"发展",4}};
DSqString Str={"创新素质发展研究与实验促进学生创新学生素质发展的很好钢琴教学模式研究与实验促进学生",82};
		WORD Result[MaxDictionaryLen];
		int k;
		k=Segmentation(D,9,Str,Result);
		for(int i=0;i<k;i++)                           // 输出分词结果
		{
			for(int j=0;j<Result[i].word.length;j++)
			cout<<Result[i].word.str[j];
			cout<<"，该词出现频率为："<<Result[i].num<<endl;
		}
	}
