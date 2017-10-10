typedef struct {
  char  *str;                // 存放非空串的首地址
  int length;               // 存放串的当前长度
}DSqString;               // 动态顺序串类型

bool StrAssign_Sq(DSqString &S,char *chars)
  {  // 将字符串chars赋值给顺序串S
    int i,j;
	char *c;
   	for(i=0,c=chars;*c;i++,c++);           // 求chars的长度
	if(!i) { S.str=NULL;  S.length=0; }    // S置为空串
	else {
		if(!(S.str=(char *)malloc(i*sizeof(char))))  // 给串S申请空间 
			return false;                
		for(j=0;j<i;j++)                  // 将数组中的字符复制到串S中
		S.str[j]=chars[j];
		S.length=i;                       // 串S的串长为i
	}
	return true;
}// StrAssign_Sq

bool StrCopy_Sq(DSqString &S,DSqString T)
{   // 将顺序串T复制到另一个顺序串S中，并返回复制后的顺序串S
	int i;
	if(S.str) free(S.str);                       // 释放S原有空间
	if(!T.length) { S.str=NULL;  S.length=0;  }   // S置为空串
	else {
		if(!(S.str=(char *)malloc(T.length*sizeof(char)))) // 给串S申请空间 
			return false;                 
		for(i=0;i<T.length;i++)                  // 将串T中的字符复制到串S中
		S.str[i]=T.str[i];
		S.length=T.length;                       // 串S的串长为T.length
	} 
	return true;
}// StrCopy_Sq

int StrLength_Sq(DSqString S)
{
	return(S.length);
}// StrLength_Sq

int StrCompare_Sq(DSqString S,DSqString T)
{     // 比较顺序串S和顺序串T的大小
	int i=0;
	while(i<S.length&&i<T.length)            // 串S和串T对应字符进行比较
	{
		if(S.str[i]>T.str[i]) return 1;
		else if(S.str[i]<T.str[i]) return -1;
		i++;
	}
	if(i<S.length) return 1;
	else if(i<T.length) return -1;
	return 0;
}// StrCompare_Sq
	
bool StrConcat_Sq(DSqString &S,DSqString T)
{
   int i;
   if(T.length) {
	if(!(S.str=(char *)realloc(S.str,(S.length+T.length)*sizeof(char))))  // 给串增补空间
			return false;
		for(i=0;i<T.length;i++)           // 将串T中的字符连接在串S的后面
		 S.str[S.length+i]=T.str[i];
		S.length+=T.length;                // 串S的串长增加T.length
     }
	return true;
}// StrConcat_Sq

bool SubString_Sq(DSqString S,DSqString &Sub,int pos,int len)
{    // 在顺序串S中从第pos个位置开始，取长度为len的子串Sub，并返回Sub的值
	int i;
	if(pos<0||pos>S.length-1||len<0||len>S.length-pos)  
		return false;                  // 取子串的位置或子串的长度不合理
	if(Sub.str)   free(Sub.str);         // 释放Sub原有空间
	if(!len) { Sub.str=NULL; Sub.length=0; }   // 置Sub为空子串
	else {
		if(!(Sub.str=(char *)malloc(len*sizeof(char))))
			return false;
		for(i=0;i<len;i++)            // 将串S中的len个字符复制到Sub中
			Sub.str[i]=S.str[pos+i];
		Sub.length=len;                // 子串Sub的串长为len
	}
	return true; 
}// SubString_Sq

bool Index_Sq(DSqString S,DSqString T,int i,int &pos)
{  // 在主串S中查找是否存在子串T，若存在，则由pos返回其位置
   int j=0;                       // i和j分别扫描主串S和子串T
   while(i<S.length&&j<T.length)      
   { if(S.str[i]==T.str[j])          // 对应字符相同，继续比较下一个字符
      { i++;    j++;
      }
      else                           // 主串指针回溯重新开始下一次匹配
      { i=i-j+1;
        j=0;
      }
   }
   if(j==T.length)  { pos=i-T.length; return true;  }
   else return false;
}// Index_Sq

bool StrInsert_Sq(DSqString &S,int pos,DSqString T)
    {   // 在顺序串S的第pos个字符之前插入子串T，并返回插入后的顺序串S
     int i;
     if(pos<0||pos>S.length)  return false;    // pos不合理
     if(T.str) {
	   if(!(S.str=(char *)realloc(S.str,(S.length+T.length)*sizeof(char))))  
// 给串S增补空间 
			return false;                 
       for(i=S.length-1;i>=pos;i--)            // 为插入串T而腾出位置
        S.str[i+T.length]=S.str[i];
       for(i=0;i<T.length;i++)                  // 插入串T
        S.str[pos+i]=T.str[i];
       S.length=S.length+T.length;             // 串S长度增加T.length
      }
    return true;
}// StrInsert_Sq

bool StrDelete_Sq(DSqString &S,int pos,int len)
    {  // 从顺序串S的第pos个字符字符开始删除长度为len的子串，并返回删除后的串S
      int i;
      if(pos<0||pos>S.length-1||len<0||pos+len>S.length)  return false;  // pos和len不合理
      for(i=pos+len;i<S.length;i++)           // 元素前移，删除子串
        S.str[i-len]=S.str[i];
      S.str=(char *)realloc(S.str,(S.length-len)*sizeof(char)); // 串S空间减少len
      S.length=S.length-len;                  // 串S长度减少len
      return true;
}// StrDelete_Sq

void StrReplace_Sq(DSqString &S, DSqString T,DSqString V)
{  // 用串V置换主串S中出现的所有与T相等的不重叠子串，并返回置换后的串S
      int  i=0,pos;
      while(Index_Sq(S,T,i,pos))                    // 判断T是否是S的子串
      { StrDelete_Sq(S,pos,T.length);             // 删除子串T
	    StrInsert_Sq(S,pos,V);                    // 插入子串V
		i=i+StrLength_Sq(V);
      }
}// StrReplace_Sq

void StrTraveres_Sq(DSqString S)
{
	int i;
	for(i=0;i<S.length;i++)
	 cout<<S.str[i];
	cout<<endl;
}// StrTraveres_Sq

void DestroyString_Sq(DSqString &S)
{
	free(S.str);
	S.str=NULL;        // S.str置空
   S.length=0;
}// DestroyString_Sq
